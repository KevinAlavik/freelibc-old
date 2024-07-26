/*
Freelibc
Copyright (C) 2024 Kevin Alavik and contributors

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License (GPL) as published by
the Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

As an exception to the GPL-3.0, you may link or combine Freelibc with
other software that is not GPL-3.0 licensed, and distribute the combined
work under the terms of the license of the other software, provided that
Freelibc remains licensed under GPL-3.0.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see: <http://www.gnu.org/licenses/>
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
