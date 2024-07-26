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

#include "stdalloc.h"

#define ALIGNMENT 8

static Block *free_list = NULL;
static char *buffer_start = NULL;
static usize buffer_size = 0;

static void *align_pointer(void *ptr, usize alignment)
{
    uptr addr = (uptr)ptr;
    uptr aligned_addr = (addr + alignment - 1) & ~(alignment - 1);
    return (void *)aligned_addr;
}

void alloc_init(void *buffer, usize size)
{
    buffer_start = (char *)buffer;
    buffer_size = size;
    free_list = (Block *)align_pointer(buffer, ALIGNMENT);
    free_list->size = size;
    free_list->next = NULL;
}

void *alloc(usize size)
{
    if (size == 0)
        return NULL;

    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);

    Block *prev = NULL;
    Block *current = free_list;
    while (current)
    {
        if (current->size >= size)
        {
            if (current->size > size + sizeof(Block))
            {
                Block *next = (Block *)((char *)current + sizeof(Block) + size);
                next->size = current->size - sizeof(Block) - size;
                next->next = current->next;
                current->size = size;
                current->next = next;
            }

            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                free_list = current->next;
            }
            return (char *)current + sizeof(Block);
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}
