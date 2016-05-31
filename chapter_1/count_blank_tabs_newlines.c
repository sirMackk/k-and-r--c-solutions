#include <stdio.h>

/* 1-8: Write a program to count blanks, tabs, newlines */
main()
{
    int c, tabs, blanks, nl;
    tabs = 0;
    blanks = 0;
    nl = 0;

    while((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
        if (c == '\t')
            ++tabs;
        if (c == ' ')
            ++blanks;
    }

    printf("Newlines: %d\n", nl);
    printf("Tabs: %d\n", tabs);
    printf("Blanks: %d\n", blanks);
}
