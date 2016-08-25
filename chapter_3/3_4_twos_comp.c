/* 3-4: In a two's complement number representation, our version of itoa
 * does not handle the largest negative number, that is, the value of n
 * equal to -2^(wordsize-1). Explain why not. Modify it to print that
 * value correctly, regardless of the machine on which it runs. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
    char output[16];
    int input;
    input = ~(~0U >> 1);
    input = -5814;
    itoa(input, output);
    printf("%s\n", output);
    return 0;
}

void itoa(int n, char s[])
{
    int i, sign;

    if (n < 0) {
        sign = -1;
    } else {
        sign = 1;
    }

    i = 0;

    do {
        s[i++] = sign * (n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int len = strlen(s);
    int i, j, c;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


