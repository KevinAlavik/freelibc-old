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
 * __ffsti2 - Find the index of the least significant set bit in a 64-bit unsigned long long.
 *
 * @param a: The integer to be analyzed.
 *
 * @return: The index of the least significant set bit, or zero if a is zero.
 */
int __ffsti2(unsigned long long a)
{
#ifdef __X86_64__
    int index;
    __asm__ volatile(
        "bsfq %1, %0" // Find first set bit
        : "=r"(index) // Output operand: index
        : "r"(a)      // Input operand: a
        : "cc"        // Clobbered registers: condition codes
    );
    return index + 1; // Return index starting from 1
#else
    if (a == 0)
        return 0;
    int index = 0;
    while ((a & 1) == 0)
    {
        index++;
        a >>= 1;
    }
    return index + 1; // Return index starting from 1
#endif
}