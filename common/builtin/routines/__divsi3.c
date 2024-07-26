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

int __divsi3(int a, int b)
{
    int result;
#ifdef __X86_64__
    __asm__ volatile(
        "cltd\n\t"               // Sign extend eax into edx:eax
        "idivl %2"               // Perform signed division
        : "=a"(result)           // Result is stored in eax
        : "a"(a), "d"(0), "r"(b) // Dividend in eax, edx:eax set by cltd, divisor in any register
        : "cc"                   // Clobbers condition codes
    );
#else
    result = a / b; // Fallback to standard C if not x86_64
#endif
    return result;
}
