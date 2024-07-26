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

int __ffsti2(unsigned long long a)
{
#ifdef __X86_64__
    int index;
    __asm__ volatile(
        "bsfq %1, %0" // Find first set bit
        : "=r"(index) // Output operand: index
        : "r"(a)      // Input operand: a
        : "cc"        // Clobbered registers: condition codes
    );
    return index + 1; // Return index starting from 1
#else
    if (a == 0)
        return 0;
    int index = 0;
    while ((a & 1) == 0)
    {
        index++;
        a >>= 1;
    }
    return index + 1; // Return index starting from 1
#endif
}
