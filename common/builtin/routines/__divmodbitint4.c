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

#if !defined(__x86_64__) && !defined(_M_X64)
#error This file is intended for x86_64 architecture.
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
 * __divmodbitint4 - Divide and modulus bit-precise integer operands u by v.
 *
 * This function performs division and modulus operations on large integers represented as arrays of limbs.
 * It computes the quotient and remainder of the division of `u` by `v` and stores the results in `q` and `r` respectively.
 *
 * @param q: Pointer to the result array for the quotient of the division.
 * @param qprec: Precision of the quotient in bits.
 * @param r: Pointer to the result array for the remainder of the division.
 * @param rprec: Precision of the remainder in bits.
 * @param u: Pointer to the dividend array of limbs.
 * @param uprec: Precision of the dividend in bits.
 * @param v: Pointer to the divisor array of limbs.
 * @param vprec: Precision of the divisor in bits.
 */
void __divmodbitint4(UBILtype *q, int32_t qprec, UBILtype *r, int32_t rprec, const UBILtype *u, int32_t uprec, const UBILtype *v, int32_t vprec)
{
    int num_limbs_u = (uprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;
    int num_limbs_v = (vprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;
    int num_limbs_q = (qprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;
    int num_limbs_r = (rprec + __LIBGCC_BITINT_LIMB_WIDTH__ - 1) / __LIBGCC_BITINT_LIMB_WIDTH__;

    // Initialize the quotient and remainder arrays to zero
    if (q)
    {
        __memset(q, 0, num_limbs_q * sizeof(UBILtype));
    }
    if (r)
    {
        __memset(r, 0, num_limbs_r * sizeof(UBILtype));
    }

    // Temporary array to hold the remainder during the division process
    UBILtype temp_rem[2 * num_limbs_u];

    // Copy the dividend into the temporary remainder array
    __memcpy(temp_rem, u, num_limbs_u * sizeof(UBILtype));

    // Perform the division and modulus operations bit by bit
    for (int i = num_limbs_u - 1; i >= 0; i--)
    {
        for (int j = __LIBGCC_BITINT_LIMB_WIDTH__ - 1; j >= 0; j--)
        {
            UBILtype bit = (temp_rem[i] >> j) & 1;
            UBILtype divisor = (i < num_limbs_v) ? v[i] : 0;

            UBILtype q_bit, r_bit;
            // Perform division and get quotient and remainder bits
            __asm__ volatile(
                "mov %2, %%rax\n\t"
                "mov %3, %%rbx\n\t"
                "divq %%rbx\n\t"
                "mov %%rax, %0\n\t"
                "mov %%rdx, %1"
                : "=r"(q_bit), "=r"(r_bit)
                : "r"(bit), "r"(divisor)
                : "rax", "rbx", "rdx", "cc");

            // Store the quotient bit in the quotient array
            if (q && i < num_limbs_q)
            {
                q[i] |= (q_bit << j);
            }

            // Store the remainder bit in the remainder array
            if (r)
            {
                r[i] |= (r_bit << j);
            }
        }
    }
}
