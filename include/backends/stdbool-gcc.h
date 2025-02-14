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

#ifndef __FREELIBC_STDBOOL_GCC_H
#define __FREELIBC_STDBOOL_GCC_H

#if defined(__FREELIBC_DEF_STDBOOL_GCC)

#define bool _Bool
#define true 1
#define false 0

#define __bool_true_false_are_defined 1

#endif // __FREELIBC_DEF_STDBOOL_GCC

#endif // __FREELIBC_STDBOOL_GCC_H
