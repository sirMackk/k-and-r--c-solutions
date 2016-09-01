#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#include <ctype.h>

#ifndef CALCH
#define CALCH
#include "calc.h"
#endif


int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
                ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}
