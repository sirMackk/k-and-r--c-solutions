#include <stdio.h>

/* 2-9: In a two's complement number system, x &= (x-1) deletes the
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount. */

/* x &= (x-1) deletes the rightmost 1-bit in x because ANDing a number
 * with number-1 results in an even number and all even binary numbers
 * have 0 at thend */

/* This version is faster because it essentially skips over 0 when 
 * counting. */

int bitcount(unsigned int x);

int main()
{
    int x;

    x = bitcount(187);

    printf("bitcount: %d\n", x);
    printf("expected: %d\n", 6);

    return 0;
}

int bitcount(unsigned int x)
{
    int b;

    for (b = 0; x != 0; x &= (x-1))
        b++;

    return b;
}
