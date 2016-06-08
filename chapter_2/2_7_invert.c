#include <stdio.h>

/* 2-7: Write a function invert(x, p, n) that returns x with the n bits that
 * begin at position p inverted (ie. 1 changed into 0 and vice versa), 
 * leaving the others unchanged. */

unsigned int invert(unsigned int x, int n, int p);

int main()
{
    unsigned int x;

    x = invert(187, 3, 5);

    printf("inverted: %u\n", x);
    printf("expected: %u\n", 167);

    return 0;
}

unsigned int invert(unsigned int x, int n, int p)
{
    return x ^ (~(~0 << n) << (p - n));
}
