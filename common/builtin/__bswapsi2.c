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

/**
 * __bswapsi2 - Byte swap a 32-bit integer.
 *
 * @param a: The 32-bit integer to be byte-swapped.
 *
 * @return: The byte-swapped integer.
 */
int32_t __bswapsi2(int32_t a)
{
#ifdef __x86_64__
    // Using built-in GCC intrinsic for byte swapping
    return __builtin_bswap32(a);
#else
    return ((a & 0xFF000000) >> 24) |
           ((a & 0x00FF0000) >> 8) |
           ((a & 0x0000FF00) << 8) |
           ((a & 0x000000FF) << 24);
#endif
}
