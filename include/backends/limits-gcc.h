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

#ifndef __FREELIBC_LIMITS_GCC_H
#define __FREELIBC_LIMITS_GCC_H

#if defined(__FREELIBC_DEF_LIMITS_GCC)

#define CHAR_BIT 8

#define SCHAR_MIN (-127)
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#ifdef __CHAR_UNSIGNED__
#define CHAR_MIN 0
#define CHAR_MAX UCHAR_MAX
#else
#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX
#endif

#define MB_LEN_MAX 1

#define SHRT_MIN (-32767)
#define SHRT_MAX 32767
#define USHRT_MAX 65535

#define INT_MIN (-32767)
#define INT_MAX 32767
#define UINT_MAX 65535

#define LONG_MIN (-2147483647L)
#define LONG_MAX 2147483647L
#define ULONG_MAX 4294967295UL

#define LLONG_MIN (-9223372036854775807LL)
#define LLONG_MAX 9223372036854775807LL
#define ULLONG_MAX 18446744073709551615ULL

#endif // __FREELIBC_DEF_LIMITS_GCC

#endif // __FREELIBC_LIMITS_GCC_H
