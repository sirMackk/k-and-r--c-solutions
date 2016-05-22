#include <stdio.h>

/* 1-12: Write a program that prints it input one word per line. */

#define IN 1
#define OUT 0

main()
{
    int state, c;

    state = OUT;

    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == OUT) {
                state = IN;
                putchar('\n');
            }
        } else {
            state = OUT;
            putchar(c);
        }
    }

    /* my solution */
        /*if ((c == ' ' || c == '\t' || c == '\n') && state == IN) {*/
            /*putchar('\n');*/
            /*state = OUT;*/
        /*} else if (state == OUT && (c != ' ' && c != '\t' && c != '\n')) {*/
            /*putchar(c);*/
            /*state = IN;*/
        /*} else if (state == IN) {*/
            /*putchar(c);*/
        /*}*/
    /*}*/
}
