#include <stdio.h>

/* 1-10: Write a program to copy its input to its output,
 * replacing each tab by \t, each backspace by \b, and each
 * backslash by \\. This makes tabs and backspaces visible
 * in an unambigous way. */

main()
{
    int c;

    int sentinel = 0;

    while((c = getchar()) != EOF) {
        if (c == '\t') {
            sentinel = 1;
            putchar('\\');
            putchar('t');
        }
        if (c == '\b') {
            sentinel = 1;
            putchar('\\');
            putchar('b');
        }

        if (c == '\\') {
            sentinel = 1;
            putchar('\\');
            putchar('\\');
        }

        if (sentinel == 0)
            putchar(c);
    }
}
