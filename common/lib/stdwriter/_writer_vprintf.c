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

#include <stdwriter.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#define WRITE_CHAR(writer, c, count) \
    do                               \
    {                                \
        writer->callback(c);         \
        (*count)++;                  \
    } while (0)

static void write_int(writer_t *writer, int num, int width, bool zero_padding, bool left_justify, bool force_sign, bool space_before_positive, int *count)
{
    char buffer[32];
    char *ptr = buffer + sizeof(buffer) - 1;
    bool negative = num < 0;

    if (num == 0)
        *ptr-- = '0';
    else
    {
        unsigned int abs_num = (num < 0) ? -num : num;
        while (abs_num != 0)
        {
            *ptr-- = '0' + (abs_num % 10);
            abs_num /= 10;
        }
    }

    if (negative)
        *ptr-- = '-';
    else if (force_sign)
        *ptr-- = '+';
    else if (space_before_positive)
        *ptr-- = ' ';

    int len = buffer + sizeof(buffer) - 1 - ptr;

    if (width > len && !left_justify)
    {
        char pad = zero_padding ? '0' : ' ';
        while (width-- > len)
        {
            WRITE_CHAR(writer, pad, count);
        }
    }

    while (*++ptr)
    {
        WRITE_CHAR(writer, *ptr, count);
    }

    while (width-- > len)
    {
        WRITE_CHAR(writer, ' ', count);
    }
}

static void write_uint(writer_t *writer, unsigned int num, int width, bool zero_padding, bool left_justify, bool alternative_form, int *count)
{
    char buffer[32];
    char *ptr = buffer + sizeof(buffer) - 1;

    if (num == 0)
        *ptr-- = '0';
    else
    {
        while (num != 0)
        {
            *ptr-- = '0' + (num % 10);
            num /= 10;
        }
    }

    if (alternative_form && buffer + sizeof(buffer) - 1 - ptr > 1)
    {
        *ptr-- = '0';
    }

    int len = buffer + sizeof(buffer) - 1 - ptr;

    if (width > len && !left_justify)
    {
        char pad = zero_padding ? '0' : ' ';
        while (width-- > len)
        {
            WRITE_CHAR(writer, pad, count);
        }
    }

    while (*++ptr)
    {
        WRITE_CHAR(writer, *ptr, count);
    }

    while (width-- > len)
    {
        WRITE_CHAR(writer, ' ', count);
    }
}

static void write_octal(writer_t *writer, unsigned int num, int width, bool zero_padding, bool left_justify, bool alternative_form, int *count)
{
    char buffer[32];
    char *ptr = buffer + sizeof(buffer) - 1;

    if (num == 0)
        *ptr-- = '0';
    else
    {
        while (num != 0)
        {
            *ptr-- = '0' + (num % 8);
            num /= 8;
        }
    }

    if (alternative_form && buffer + sizeof(buffer) - 1 - ptr > 1)
    {
        *ptr-- = '0';
    }

    int len = buffer + sizeof(buffer) - 1 - ptr;

    if (width > len && !left_justify)
    {
        char pad = zero_padding ? '0' : ' ';
        while (width-- > len)
        {
            WRITE_CHAR(writer, pad, count);
        }
    }

    while (*++ptr)
    {
        WRITE_CHAR(writer, *ptr, count);
    }

    while (width-- > len)
    {
        WRITE_CHAR(writer, ' ', count);
    }
}

static void write_hex(writer_t *writer, unsigned long long num, bool uppercase, bool alternative_form, int width, bool zero_padding, bool left_justify, int *count)
{
    char buffer[32];
    char *ptr = buffer + sizeof(buffer) - 1;
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

    if (num == 0)
        *ptr-- = '0';
    else
    {
        while (num != 0)
        {
            *ptr-- = digits[num % 16];
            num /= 16;
        }
    }

    if (alternative_form && buffer + sizeof(buffer) - 1 - ptr > 1)
    {
        *ptr-- = '0';
        *ptr-- = uppercase ? 'X' : 'x';
    }

    int len = buffer + sizeof(buffer) - 1 - ptr;

    if (width > len && !left_justify)
    {
        char pad = zero_padding ? '0' : ' ';
        while (width-- > len)
        {
            WRITE_CHAR(writer, pad, count);
        }
    }

    while (*++ptr)
    {
        WRITE_CHAR(writer, *ptr, count);
    }

    while (width-- > len)
    {
        WRITE_CHAR(writer, ' ', count);
    }
}

int _writer_vprintf(writer_t *writer, const char *fmt, va_list args)
{
    int count = 0;

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            bool left_justify = false, force_sign = false, space_before_positive = false, alternative_form = false, zero_padding = false;
            int width = 0, precision = -1;
            int length = 0;
            bool uppercase = false;

            while (*fmt == '-' || *fmt == '+' || *fmt == ' ' || *fmt == '#' || *fmt == '0')
            {
                if (*fmt == '-')
                    left_justify = true;
                if (*fmt == '+')
                    force_sign = true;
                if (*fmt == ' ')
                    space_before_positive = true;
                if (*fmt == '#')
                    alternative_form = true;
                if (*fmt == '0')
                    zero_padding = true;
                fmt++;
            }

            if (*fmt >= '0' && *fmt <= '9')
            {
                width = 0;
                while (*fmt >= '0' && *fmt <= '9')
                {
                    width = width * 10 + (*fmt++ - '0');
                }
            }
            else if (*fmt == '*')
            {
                width = va_arg(args, int);
                fmt++;
            }

            if (*fmt == '.')
            {
                fmt++;
                if (*fmt >= '0' && *fmt <= '9')
                {
                    precision = 0;
                    while (*fmt >= '0' && *fmt <= '9')
                    {
                        precision = precision * 10 + (*fmt++ - '0');
                    }
                }
                else if (*fmt == '*')
                {
                    precision = va_arg(args, int);
                    fmt++;
                }
                else
                {
                    precision = 0;
                }
            }

            if (*fmt == 'h')
            {
                fmt++;
                length = (*fmt == 'h') ? 1 : 2;
                if (length == 1)
                    fmt++;
            }
            else if (*fmt == 'l')
            {
                fmt++;
                length = (*fmt == 'l') ? 4 : 3;
                if (length == 3)
                    fmt++;
            }
            else if (*fmt == 'j')
            {
                length = 5;
                fmt++;
            }
            else if (*fmt == 'z')
            {
                length = 6;
                fmt++;
            }
            else if (*fmt == 't')
            {
                length = 7;
                fmt++;
            }
            else if (*fmt == 'L')
            {
                length = 8;
                fmt++;
            }

            switch (*fmt)
            {
            case 's':
            {
                const char *str_arg = va_arg(args, const char *);
                while (*str_arg)
                {
                    WRITE_CHAR(writer, *str_arg++, &count);
                }
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                WRITE_CHAR(writer, (char)ch, &count);
                break;
            }
            case 'd':
            case 'i':
            {
                int int_arg;
                if (length == 1)
                    int_arg = (signed char)va_arg(args, int);
                else if (length == 2)
                    int_arg = (short int)va_arg(args, int);
                else if (length == 3)
                    int_arg = (long int)va_arg(args, long int);
                else if (length == 4)
                    int_arg = (long long int)va_arg(args, long long int);
                else
                    int_arg = va_arg(args, int);
                write_int(writer, int_arg, width, zero_padding, left_justify, force_sign, space_before_positive, &count);
                break;
            }
            case 'u':
            {
                unsigned int uint_arg;
                if (length == 1)
                    uint_arg = (unsigned char)va_arg(args, unsigned int);
                else if (length == 2)
                    uint_arg = (unsigned short int)va_arg(args, unsigned int);
                else if (length == 3)
                    uint_arg = (unsigned long int)va_arg(args, unsigned long int);
                else if (length == 4)
                    uint_arg = (unsigned long long int)va_arg(args, unsigned long long int);
                else
                    uint_arg = va_arg(args, unsigned int);
                write_uint(writer, uint_arg, width, zero_padding, left_justify, alternative_form, &count);
                break;
            }
            case 'o':
            {
                unsigned int uint_arg;
                if (length == 1)
                    uint_arg = (unsigned char)va_arg(args, unsigned int);
                else if (length == 2)
                    uint_arg = (unsigned short int)va_arg(args, unsigned int);
                else if (length == 3)
                    uint_arg = (unsigned long int)va_arg(args, unsigned long int);
                else if (length == 4)
                    uint_arg = (unsigned long long int)va_arg(args, unsigned long long int);
                else
                    uint_arg = va_arg(args, unsigned int);
                write_octal(writer, uint_arg, width, zero_padding, left_justify, alternative_form, &count);
                break;
            }
            case 'x':
            case 'X':
            {
                unsigned long long uint_arg;
                if (length == 1)
                    uint_arg = (unsigned char)va_arg(args, unsigned int);
                else if (length == 2)
                    uint_arg = (unsigned short int)va_arg(args, unsigned int);
                else if (length == 3)
                    uint_arg = (unsigned long int)va_arg(args, unsigned long int);
                else if (length == 4)
                    uint_arg = (unsigned long long int)va_arg(args, unsigned long long int);
                else
                    uint_arg = va_arg(args, unsigned long long);
                uppercase = (*fmt == 'X');
                write_hex(writer, uint_arg, uppercase, alternative_form, width, zero_padding, left_justify, &count);
                break;
            }
            case '%':
            {
                WRITE_CHAR(writer, '%', &count);
                break;
            }
            default:
                WRITE_CHAR(writer, '%', &count);
                WRITE_CHAR(writer, *fmt, &count);
                break;
            }
            fmt++;
        }
        else
        {
            WRITE_CHAR(writer, *fmt, &count);
            fmt++;
        }
    }

    return count;
}
