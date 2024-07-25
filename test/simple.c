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

#include <stdint.h>

void putc(char ch)
{
    asm volatile(
        "mov $1, %%rax;"
        "mov $1, %%rdi;"
        "mov %0, %%rsi;"
        "mov $1, %%rdx;"
        "syscall"
        :
        : "r"(&ch)
        : "%rax", "%rdi", "%rsi", "%rdx");
}

void puts(char *str)
{
    while (*str != '\0')
    {
        putc(*str);
        str++;
    }
}

int main()
{
    puts("Hello\n");
    return 0;
}
