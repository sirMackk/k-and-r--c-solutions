/* 4-12: Adapt the idea of printd to write a recursive version
 * of itoa; that is, convert an integer into a string by calling a
 * recursive routine. */

#include <stdio.h>

void printd(int n)
{
    printf("%d\n", n);
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

int itoa(int n, char s[])
{
    int i = 0;

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10)
        i = itoa(n / 10, s);
    s[i++] = n % 10 + '0';
    s[i] = '\0';
    return i;
}

#define MAXVAL 128
int main()
{
    char s[MAXVAL];
    int i;
    int tests[] = {123, 0, -1, -123};

    for (i = 0; i < 4; i++) {
        itoa(tests[i], s);
        printf("Using %d, outcome: %s\n", tests[i], s);
    }

    return 0;
}
