#include <stdio.h>

/* 2-6: Write a function setbits(x,p,n,y) that returns x with the n bits
 * that begin at position p set to the rightmost n bits of y, leaving
 * the other bits unchanged. */

unsigned int getbits(unsigned int x, int p, int n);
unsigned int setbits(unsigned int x, int p, int n, int y);

int main()
{
    unsigned int getbit_test = 187;
    printf("getbit: %u\n", getbits(getbit_test, 4, 3));
    printf("setbit: %u\n", setbits(187, 5, 3, 189));
    printf("expect: 171\n");

    return 0;
}

unsigned int getbits(unsigned int x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned int setbits(unsigned int x, int p, int n, int y)
{
    return ((x & ~(~(~0 << n) << n)) | ((y << n) & (~(~0 << n) << n)));
}
