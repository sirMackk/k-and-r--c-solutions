#include <stdio.h>

/* 1-9: Write a program to copy its input to its output
 * replacing each string of one or more blanks by a single blank. */

main()
{
    int c, blank;

    blank = 0;

    while((c = getchar()) != EOF) {
        if (c != ' ') {
            blank = 0;
            putchar(c);
        }

        if (c == ' ') {
            if (blank == 0) {
                putchar(c);
                blank = 1;
            }
        }
    }
}


