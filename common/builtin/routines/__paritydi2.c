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

int __paritydi2(unsigned long a)
{
#ifdef __X86_64__
    int parity;
    __asm__ volatile(
        "popcnt %1, %0\n" // Count number of set bits
        "testl $1, %0\n"  // Check if odd or even
        "setz %0"         // Set parity result (0 or 1)
        : "=r"(parity)    // Output operand: parity
        : "r"(a)          // Input operand: a
        : "cc"            // Clobbered registers: condition codes
    );
    return parity;
#else
    int count = 0;
    while (a)
    {
        count ^= (a & 1);
        a >>= 1;
    }
    return count;
#endif
}
