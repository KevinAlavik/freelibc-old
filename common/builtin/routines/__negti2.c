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

long long __negti2(long long a)
{
    long long result;
#ifdef __X86_64__
    __asm__ volatile(
        "movq %1, %%rax\n\t" // Move low part of value into RAX
        "negq %%rax\n\t"     // Perform negation
        "movq %%rax, %0"     // Move result from RAX
        : "=r"(result)       // Output operand: result
        : "r"(a)             // Input operand: a
        : "cc"               // Clobbered condition codes
    );
#else
    result = -a; // Fallback for non-x86_64 systems
#endif
    return result;
}
