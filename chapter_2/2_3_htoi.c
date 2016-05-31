#include <stdio.h>
#include <math.h>

/* 2-3: Write the function htoi(s), which converts a string of hexadecimal
 * digits (including an optional 0x or 0X) into its equivalent integer
 * value. The allowable digits are 0 through 9, a through f, and A
 * through F. */

unsigned long htoi(const char input[]);
char c_lower(char c);


int main()
{

    char test1[] = "010515\0";
    char test2[] = "010x150X22\0";

    unsigned long result1 = htoi(test1);
    unsigned long result2 = htoi(test2);

    printf("Result 1: %lu == 66837\n", result1);
    printf("Result 2: %lu == 70946\n", result2);

    return 0;
}

char c_lower(char c)
{
    if (c > 90)
        return c;
    else
        return c + 32;
}


unsigned long htoi(const char input[])
{
    int i, j, c, skip;
    unsigned long accumulator;

    i = accumulator = skip = j = 0;

    while (input[i++] != '\0')
        ;

    for (; i >= 0; --i) {
        c = input[i];

        if (skip || c < 48) {
            skip = 0;
            continue;
        }

        if (c == 'x' || c == 'X') {
            skip = 1;
            continue;
        }

        if (c > 57)
            c = c_lower(c) - 87;
        else
            c = c - 48;

        accumulator += c * pow(16, j++);
    }

    return accumulator;
}
