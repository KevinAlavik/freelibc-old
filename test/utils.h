#ifndef UTILS_H
#define UTILS_H

void putc(char ch)
{
    __asm__ volatile(
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

#endif // UTILS_H