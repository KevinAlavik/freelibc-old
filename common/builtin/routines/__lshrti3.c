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

/**
 * __lshrti3 - Perform a logical right shift on a 128-bit integer.
 *
 * @param a: The value to be shifted.
 * @param b: The number of positions to shift `a` to the right.
 *
 * @return: The result of shifting `a` to the right by `b` positions.
 */
long long __lshrti3(long long a, int b)
{
    long long result;
#ifdef __X86_64__
    __asm__ volatile(
        "movq %1, %%rax\n\t"   // Move low part of value into RAX
        "movq %2, %%rdx\n\t"   // Move high part of value into RDX
        "shrq %%cl, %%rax\n\t" // Shift right logical with variable shift count
        "shrq %%cl, %%rdx\n\t" // Shift right logical with variable shift count
        : "=a"(result)         // Result in RAX
        : "r"(a), "r"(b)       // Value in RAX:RDX, shift count in %cl
        : "cc", "rdx"          // Clobbered registers
    );
#else
    result = (unsigned long long)a >> b; // Fallback for non-x86_64 systems
#endif
    return result;
}
