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

#include <stdvector.h>
#include <stdalloc.h>
#include <stddef.h>
#include <string.h>

int vector_resize(Vector *vec, usize new_capacity)
{
    if (new_capacity <= vec->capacity)
        return 0;

    void *new_data = alloc(new_capacity * vec->element_size);
    if (new_data == NULL)
        return -1;

    memcpy(new_data, vec->data, vec->size * vec->element_size);
    free(vec->data);

    vec->data = new_data;
    vec->capacity = new_capacity;
    return 0;
}
