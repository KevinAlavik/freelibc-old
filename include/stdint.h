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

#define __FREELIBC_DEF_STDINT_GCC
#include "backends/stdint-gcc.h"

// Signed short typedefs
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef __int128_t __i128;

// Signed fast short typedefs
typedef int_fast8_t if8;
typedef int_fast16_t if16;
typedef int_fast32_t if32;
typedef int_fast64_t if64;
typedef int_fast128_t if128;

// Un-Signed short typedefs
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __uint128_t __u128;

// Un-Signed fast short typedefs
typedef uint_fast8_t uf8;
typedef uint_fast16_t uf16;
typedef uint_fast32_t uf32;
typedef uint_fast64_t uf64;
typedef uint_fast128_t uf128;

// Misc short typedefs
typedef uintptr_t uptr;
typedef intptr_t intptr;

#endif // __FREELIBC_STDINT_H
