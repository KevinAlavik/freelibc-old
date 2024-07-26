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

int64_t __bswapdi2(int64_t a)
{
#ifdef __x86_64__
    // Using built-in GCC intrinsic for byte swapping
    return __builtin_bswap64(a);
#else
    return ((a & 0xFF00000000000000LL) >> 56) |
           ((a & 0x00FF000000000000LL) >> 40) |
           ((a & 0x0000FF0000000000LL) >> 24) |
           ((a & 0x000000FF00000000LL) >> 8) |
           ((a & 0x00000000FF000000LL) << 8) |
           ((a & 0x0000000000FF0000LL) << 24) |
           ((a & 0x000000000000FF00LL) << 40) |
           ((a & 0x00000000000000FFLL) << 56);
#endif
}
