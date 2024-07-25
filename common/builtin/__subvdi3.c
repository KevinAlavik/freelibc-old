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
 * __subvdi3 - Subtract two 64-bit integers with overflow check.
 *
 * @param a: First integer.
 * @param b: Second integer.
 *
 * @return: The result of a - b.
 */
long __subvdi3(long a, long b)
{
    long result = a - b;
    // Check for overflow
    if (((a ^ result) & (~b ^ result)) < 0)
    {
        __builtin_abort(); // Overflow detected
    }
    return result;
}
