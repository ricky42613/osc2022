#include <string.h>

int strcmp(char *str1, char *str2)
{
    char c1, c2;

    while ((c1 = *str1++) == (c2 = *str2++) && c1 && c2) {};

    return c1 - c2;
}

int strncmp(char *str1, char *str2, int n)
{
    char c1, c2;

    if (n <= 0)
        return 0;

    while ((c1 = *str1++) == (c2 = *str2++) && c1 && c2 && --n > 0) {};

    return n ? c1 - c2 : 0;
}

int strlen(char *str)
{
    int ret = 0;
    
    while (*str++) {
        ret += 1;
    }

    return ret;
}

int atoi(char *str)
{
    int i = 0, tmp = 0;

    while (*str) {
        if ('0' > *str || *str > '9') {
            return 0;
        }

        i *= 10;

        tmp = i + (*str - '0');

        if (tmp < i) {
            // Maybe overflow
            return 0;
        }

        i = tmp;

        str++;
    }

    return i;
}
