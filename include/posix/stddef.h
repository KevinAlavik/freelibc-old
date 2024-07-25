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

#ifndef __FREELIBC_POSIX_STDDEF_H
#define __FREELIBC_POSIX_STDDEF_H

#ifdef __FREELIBC_POSIX_DEF_STDDEF

#define __FREELIBC_POSIX_DEF_STDINT
#include <posix/stdint.h>

// Define size_t and ptrdiff_t
#if defined(__LP64__) || defined(_WIN64) || defined(__X86_64__) // 64-bit platform
typedef uint64_t size_t;
typedef int64_t ptrdiff_t;
#else // Assume 32-bit platform
typedef uint32_t size_t;
typedef int32_t ptrdiff_t;
#endif

// Define NULL pointer constant
#ifndef NULL
#define NULL ((void *)0)
#endif

// Define maximum values for size_t and ptrdiff_t
#define SIZE_MAX ((size_t) - 1)
#define PTRDIFF_MIN (-((ptrdiff_t)SIZE_MAX + 1))
#define PTRDIFF_MAX ((ptrdiff_t)SIZE_MAX)

// Define the offsetof macro
#define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

// Define wchar_t
#if defined(__SIZEOF_WCHAR_T__)
typedef unsigned short wchar_t;
#else
typedef unsigned int wchar_t; // Adjust if needed for your platform
#endif

// Define restrict keyword (C99)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define restrict __restrict
#else
#define restrict
#endif

// Define alignment macros
#define alignof(type) __alignof__(type)

#endif // __FREELIBC_POSIX_DEF_STDDEF

#endif // __FREELIBC_POSIX_STDDEF_H
