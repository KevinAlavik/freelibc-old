/*
Freelibc
Copyright (C) 2024 Kevin Alavik and contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stddef.h>

#ifndef __LIBGCC_BITINT_LIMB_WIDTH__
#define __LIBGCC_BITINT_LIMB_WIDTH__ 64
#endif

typedef uint64_t UBILtype;

/**
 * __memset - Set a block of memory to a specific value.
 *
 * This function uses inline assembly to set a block of memory to a specific value byte-by-byte.
 *
 * @param ptr: Pointer to the starting address of the memory block.
 * @param value: The value to set each byte to.
 * @param size: The size of the memory block in bytes.
 */
static void __memset(void *ptr, uint8_t value, size_t size)
{
    __asm__ volatile(
        "mov %1, %%al\n\t"
        "mov %2, %%rcx\n\t"
        "mov %0, %%rdi\n\t"
        "rep stosb"
        :
        : "r"(ptr), "r"(value), "r"(size)
        : "rax", "rcx", "rdi", "memory");
}

/**
 * __memcpy - Copy a block of memory from source to destination.
 *
 * This function uses inline assembly to copy a block of memory from a source address to a destination address.
 *
 * @param dest: Pointer to the destination address where the memory will be copied to.
 * @param src: Pointer to the source address from where the memory will be copied.
 * @param size: The size of the memory block to be copied, in bytes.
 */
static void __memcpy(void *dest, const void *src, size_t size)
{
    __asm__ volatile(
        "mov %2, %%rcx\n\t"
        "mov %1, %%rsi\n\t"
        "mov %0, %%rdi\n\t"
        "rep movsb"
        :
        : "r"(dest), "r"(src), "r"(size)
        : "rcx", "rsi", "rdi", "memory");
}

/**
 * __mulbitint3 - Multiply bit-precise integer operands u and v.
 *
 * This function multiplies two large integers represented as arrays of limbs. The result is stored in the
 * `ret` array. It handles the multiplication of the operands and manages the carry to produce the final result.
 *
 * @param ret: Pointer to the result array of limbs.
 * @param retprec: Precision of the result in bits.
 * @param u: Pointer to the first operand array of limbs.
 * @param uprec: Precision of the first operand in bits.
 * @param v: Pointer to the second operand array of limbs.
 * @param vprec: Precision of the second operand in bits.
 */
void __mulbitint3(UBILtype *ret, int32_t retprec, const UBILtype *u, int32_t uprec, const UBILtype *v, int32_t vprec)
{
    int num_limbs_u = (uprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;
    int num_limbs_v = (vprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;
    int num_limbs_ret = (retprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;

    // Initialize the result array to zero
    if (ret)
    {
        __memset(ret, 0, sizeof(UBILtype) * num_limbs_ret);
    }

    UBILtype temp_ret[2 * __LIBGCC_BITINT_LIMB_WIDTH__ / 8] = {0};

    // Perform multiplication
    for (int i = 0; i < num_limbs_u; i++)
    {
        for (int j = 0; j < num_limbs_v; j++)
        {
            UBILtype mul_result_low = 0;
            UBILtype mul_result_high = 0;

            // Perform multiplication using inline assembly
            __asm__ volatile(
                "mov %2, %%rax\n\t"
                "mov %3, %%rbx\n\t"
                "mulq %%rbx\n\t"
                "mov %%rax, %0\n\t"
                "mov %%rdx, %1\n\t"
                : "=r"(mul_result_low), "=r"(mul_result_high)
                : "r"(u[i]), "r"(v[j])
                : "rax", "rbx", "rdx", "cc");

            // Add to the temporary result
            UBILtype carry = 0;
            for (int k = 0; k < num_limbs_ret; k++)
            {
                UBILtype sum = temp_ret[k] + mul_result_low + carry;
                carry = (sum < temp_ret[k]) || (carry && sum == temp_ret[k]);
                temp_ret[k] = sum;

                // If there's no more carry, break early
                if (!carry)
                    break;
            }
        }
    }

    // Store the result back into ret
    if (ret)
    {
        __memcpy(ret, temp_ret, sizeof(UBILtype) * num_limbs_ret);
    }
}