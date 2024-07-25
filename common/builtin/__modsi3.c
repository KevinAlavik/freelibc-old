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
 * __modsi3 - Perform signed modulus of two 32-bit integers.
 *
 * @param a: The dividend.
 * @param b: The divisor.
 *
 * @return: The remainder of a divided by b.
 */
int __modsi3(int a, int b)
{
    int result;
#ifdef __X86_64__
    __asm__ volatile(
        "movl %1, %%eax\n\t"    // Move dividend into EAX
        "xorl %%edx, %%edx\n\t" // Clear EDX (high part of dividend)
        "idivl %2\n\t"          // Perform signed division
        "movl %%edx, %0"        // Remainder is in EDX
        : "=r"(result)          // Output operand: result
        : "r"(a), "r"(b)        // Dividend in EAX, divisor in any register
        : "cc", "edx"           // Clobbered registers
    );
#else
    result = a % b; // Fallback for non-x86_64 systems
#endif
    return result;
}
