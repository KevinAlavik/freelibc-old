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
 * __ashrsi3 - Perform an arithmetic right shift on a 64-bit integer.
 *
 * @param a: The int value to be shifted.
 * @param b: The number of positions to shift `a` to the right.
 *
 * @return: The result of shifting `a` to the right by `b` positions.
 */
int __ashrsi3(int a, int b)
{
    int result;
#ifdef __X86_64__
    __asm__ volatile(
        "sall %%cl, %0"  // Shift right logical with variable shift count
        : "=r"(result)   // Output operand: result
        : "0"(a), "c"(b) // Input operands: a in the same register as result, b in %cl
        : "cc"           // Clobbered registers: condition codes
    );
#endif
    return result;
}