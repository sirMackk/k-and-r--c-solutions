#include <stdio.h>

/* file input to output; 2nd version */
main()
{
    int c;

    while((c = getchar()) != EOF)
        putchar(c);
}
