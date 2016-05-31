#include <stdio.h>

/* 1-14 Write a program to print a histogram of the frequencies of different
 * characters in its input. */

#define ASCII_START 33
#define ASCII_END 125

main()
{
    int c, i, j;
    int char_freq[ASCII_END-ASCII_START];

    for (i < 0; i < ASCII_END-ASCII_START; ++i)
        char_freq[i] = 0;

    while((c = getchar()) != EOF)
        ++char_freq[c-ASCII_START];

    for (i = 0; i < ASCII_END-ASCII_START; ++i) {
        printf("%c - %d: ", i+ASCII_START, char_freq[i]);
        for (j = 0; j < char_freq[i]; ++j)
            putchar('#');
        putchar('\n');
    }
}
