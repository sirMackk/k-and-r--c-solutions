#include <stdio.h>
#include <limits.h>

/* 2-8: Write a function rightrot(x,n) that returns the value of the
 * integer x rotate to the right by n bit positions. */

unsigned int rightrot(unsigned int x, int n);

int main()
{
    unsigned int x;

    x = rightrot(187, 3);

    printf("rightrot: %u\n", x);
    printf("expected: %u (32bit unsigned int)\n", 1610612759);

    return 0;
}

unsigned int rightrot(unsigned int x, int n)
{
    unsigned int i;
    int j;

    for (j = 0; j < n; ++j) {
        i = (x & 1) << ((sizeof(i) * CHAR_BIT) - 1);
        x = i ^ (x >> 1);
    }

    return x;
}
