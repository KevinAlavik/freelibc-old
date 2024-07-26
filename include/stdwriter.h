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

#ifndef __FREELIBC_STDWRITER_H
#define __FREELIBC_STDWRITER_H

#include <stdint.h>
#include <stdarg.h>

typedef enum
{
    WRITER_FMT_CPRINTF
} writer_fmt;

typedef void (*writer_callback_t)(u8);

typedef struct
{
    writer_callback_t callback;
    writer_fmt fmt;
} writer_t;

void writer_init(writer_t *writer, writer_fmt fmt, writer_callback_t callback);
int writer_write(writer_t *writer, const char *fmt, ...);
int _writer_vprintf(writer_t *writer, const char *fmt, va_list args);

#endif // __FREELIBC_STDWRITER_H