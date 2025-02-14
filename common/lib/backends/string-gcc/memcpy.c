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

#define __FREELIBC_DEF_STRING_GCC
#include <backends/string-gcc.h>

void *memcpy(void *destination, const void *source, size_t num)
{
  char *dest = (char *)destination;
  const char *src = (const char *)source;

  __asm__ volatile(
      "cld\n"       // Clear direction flag for forward copying
      "rep movsb"   // Repeat move byte from source to destination
      : "+D"(dest), // Destination pointer in DI register
        "+S"(src),  // Source pointer in SI register
        "+c"(num)   // Byte count in CX register
      :             // No input operands
      : "memory"    // Memory may be modified
  );

  return destination;
}