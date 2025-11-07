#include "common.h"

void putchar(char ch);

void *memset(char *begin, char c, unsigned int n)
{
    for (unsigned int i=0;i<n;i++) {
        *(begin + i) = c;
    }
    return begin;
}


void *memcpy(void *dst, const void *src, size_t n)
{
    for (size_t i=0;i<n;i++) {
        ((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
    }
    return dst;
}

char *strcpy(char *dst, const char *src)
{
    char *cur = dst;
    while (*src != '\0') {
        *cur = *src;
        src++; cur++;
    }
    *cur = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2)
            break;
        s1++; s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}


void printf(const char *fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case '\0':
                    goto end;

                case '%':
                    putchar('%');
                    break;

                case 's': {
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }

                case 'd': {
                    unsigned value = (unsigned)va_arg(vargs, int);
                    if ((signed)value < 0) {
                        putchar('-');
                        value = -value;
                    }
                    unsigned divisor = 1;
                    
                    while (value / divisor > 9)
                        divisor *= 10;

                    while (divisor) {
                        putchar('0' + value / divisor);
                        value %= divisor;
                        divisor /= 10;
                    }
                    break;
                }

                case 'x': {
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                    break;
                }
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }

end:
    va_end(vargs);
}
