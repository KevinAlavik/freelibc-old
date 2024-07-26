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
 * __popcountsi2 - Count the number of set bits in a 32-bit unsigned integer.
 *
 * @param a: The integer whose set bits are to be counted.
 *
 * @return: The number of set bits.
 */
int __popcountsi2(unsigned int a)
{
#ifdef __X86_64__
    int count;
    __asm__ volatile(
        "popcnt %1, %0" // Count set bits
        : "=r"(count)   // Output operand: count
        : "r"(a)        // Input operand: a
        : "cc"          // Clobbered registers: condition codes
    );
    return count;
#else
    int count = 0;
    while (a)
    {
        count += (a & 1);
        a >>= 1;
    }
    return count;
#endif
}
