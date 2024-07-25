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
 * __cmpti2 - Perform signed comparison of two 128-bit integers.
 *
 * @param a: First integer.
 * @param b: Second integer.
 *
 * @return: 0 if a < b, 1 if a == b, 2 if a > b.
 */
int __cmpti2(long long a, long long b)
{
    int result;
#ifdef __X86_64__
    __asm__ volatile(
        "cmpq %1, %2\n\t"     // Compare a and b
        "setl %%al\n\t"       // Set AL to 1 if less
        "sete %%bl\n\t"       // Set BL to 1 if equal
        "sete %%al\n\t"       // Set AL to 1 if equal
        "subb %%bl, %%al\n\t" // AL = (AL - BL) which is 0 if equal
        "movzbl %%al, %0"     // Move AL to result
        : "=r"(result)        // Output
        : "r"(a), "r"(b)      // Inputs
        : "al", "bl", "cc"    // Clobbered registers
    );
#else
    if (a < b)
        result = 0;
    else if (a == b)
        result = 1;
    else
        result = 2;
#endif
    return result;
}
