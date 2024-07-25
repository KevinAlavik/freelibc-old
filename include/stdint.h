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

#ifndef __FREELIBC_STDINT_H
#define __FREELIBC_STDINT_H

#define __FREELIBC_POSIX_DEF_STDINT
#include <stdint-posix.h>

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
#if defined(__FREELIBC64)
typedef int64_t i64;
typedef uint64_t u64;
#endif

#if defined(__FREELIBC_STDINT_128)
typedef int128_t i128;
typedef uint128_t u128;
#endif

#endif // __FRELIBC_STDINT_H