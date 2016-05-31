#include <stdio.h>

#define MAXLENGTH 30
#define OUT 0
#define IN 1

/* 1-13. Write a program to print a historgram of the lengths of
 * words in its input. It is easy to draw the histogram with the bars
 * horizontal; a vertical orientation is more challenging. */
main()
{
    int state, l, i, j, c;
    int word_lengths[MAXLENGTH];

    for (i = 0; i < MAXLENGTH; ++i)
        word_lengths[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                ++word_lengths[l];
                l = 0;
                state = OUT;
            }
        } else {
            state = IN;
            ++l;
        }
    }

    for (i = 0; i < MAXLENGTH; ++i) {
        printf("%d: ", i);
        for (j = 0; j < word_lengths[i]; ++j) {
            putchar('#');
        }
        putchar('\n');
    }
}
