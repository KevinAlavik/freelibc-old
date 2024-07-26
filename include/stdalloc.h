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

#ifndef __FREELIBC_STDALLOC_H
#define __FREELIBC_STDALLOC_H

#include <stddef.h>
#include <stdint.h>

typedef struct Block
{
    struct Block *next;
    usize size;
} Block;

void alloc_init(void *buffer, usize size);
void *alloc(usize size);
void free(void *ptr);
void alloc_wipe(void);

#endif // __FREELIBC_STDALLOC_H