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
 * __muldi3 - Perform signed multiplication of two 64-bit integers.
 *
 * @param a: The first operand.
 * @param b: The second operand.
 *
 * @return: The product of a and b.
 */
long __muldi3(long a, long b)
{
    long result;
#ifdef __X86_64__
    __asm__ volatile(
        "movq %1, %%rax\n\t"     // Move first operand into RAX
        "movq %2, %%rbx\n\t"     // Move second operand into RBX
        "imulq %%rbx, %%rax\n\t" // Perform signed multiplication
        "movq %%rax, %0"         // Move result from RAX
        : "=r"(result)           // Output operand: result
        : "r"(a), "r"(b)         // Operands
        : "cc", "rbx"            // Clobbered registers
    );
#else
    result = a * b; // Fallback for non-x86_64 systems
#endif
    return result;
}
