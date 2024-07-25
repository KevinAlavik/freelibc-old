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
 * __ctzsi2 - Count the number of trailing zero bits in a 32-bit unsigned integer.
 *
 * @param a: The integer whose trailing zeroes are to be counted.
 *
 * @return: The number of trailing zero bits.
 */
int __ctzsi2(unsigned int a)
{
#ifdef __X86_64__
    int count;
    __asm__ volatile(
        "tzcnt %1, %0" // Count trailing zeros
        : "=r"(count)  // Output operand: count
        : "r"(a)       // Input operand: a
        : "cc"         // Clobbered registers: condition codes
    );
    return count;
#else
    if (a == 0)
        return 32;
    int count = 0;
    while ((a & 1) == 0)
    {
        count++;
        a >>= 1;
    }
    return count;
#endif
}