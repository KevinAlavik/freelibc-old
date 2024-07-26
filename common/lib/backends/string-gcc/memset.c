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

#define __FREELIBC_DEF_STRING_GCC
#include <backends/string-gcc.h>

void *memset(void *ptr, int value, size_t num)
{
  char *dest = (char *)ptr;
  unsigned char val = (unsigned char)value;

  __asm__ volatile(
      "cld\n"       // Clear direction flag for forward setting
      "rep stosb"   // Repeat store byte value in destination
      : "+D"(dest), // Destination pointer in DI register
        "+c"(num)   // Byte count in CX register
      : "a"(val)    // Value to store in AL register
      : "memory"    // Memory may be modified
  );

  return ptr; // Return the original pointer
}
