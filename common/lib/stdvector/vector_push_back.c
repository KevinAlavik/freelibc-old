/*
Freelibc
Copyright (C) 2024 Kevin Alavik and contributors

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License (GPL) as published by
the Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

As an exception to the GPL-3.0, you may link or combine Freelibc with
other software that is not GPL-3.0 licensed, and distribute the combined
work under the terms of the license of the other software, provided that
Freelibc remains licensed under GPL-3.0.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see: <http://www.gnu.org/licenses/>
*/

#include <stdvector.h>
#include <string.h>

int vector_push_back(Vector *vec)
{
    if (vec->size >= vec->capacity)
    {
        if (vector_resize(vec, vec->capacity * 2) < 0)
        {
            return -1;
        }
    }

    void *default_element = (char *)vec->data + vec->size * vec->element_size;
    memset(default_element, 0, vec->element_size);
    vec->size++;
    return 0;
}
