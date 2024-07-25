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

/**
 * __udivmodti4 - Perform unsigned division of two 128-bit integers
 * and return both quotient and remainder.
 *
 * @param a: The dividend.
 * @param b: The divisor.
 * @param c: Pointer to store the remainder.
 *
 * @return: The quotient of a divided by b.
 */
unsigned long long __udivmodti4(unsigned long long a, unsigned long long b, unsigned long long *c)
{
    unsigned long long quotient, remainder;
#ifdef __X86_64__
    __asm__ volatile(
        "movq %1, %%rax\n\t"              // Move low part of dividend into RAX
        "movq %2, %%rdx\n\t"              // Move high part of dividend into RDX
        "divq %3\n\t"                     // Divide RAX:RDX by divisor
        "movq %%rax, %0\n\t"              // Quotient is in RAX
        "movq %%rdx, %1"                  // Remainder is in RDX
        : "=r"(quotient), "=m"(remainder) // Outputs
        : "m"(a), "r"(b)                  // Inputs
        : "rax", "rdx", "cc"              // Clobbered registers
    );
#else
    quotient = a / b;
    remainder = a % b;
    if (c)
        *c = remainder;
#endif
    return quotient;
}
