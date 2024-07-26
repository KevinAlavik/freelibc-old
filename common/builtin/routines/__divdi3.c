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

long __divdi3(long a, long b)
{
    long result;
#ifdef __X86_64__
    __asm__ volatile(
        "movq %1, %%rax\n\t" // Move dividend into RAX
        "cqto\n\t"           // Sign extend RAX into RDX:RAX
        "idivq %2"           // Perform signed division
        : "=a"(result)       // Result stored in RAX
        : "r"(a), "r"(b)     // Dividend in RAX, divisor in any register
        : "cc", "rdx"        // Clobbered registers
    );
#else
    result = a / b; // Fallback for non-x86_64 systems
#endif
    return result;
}
