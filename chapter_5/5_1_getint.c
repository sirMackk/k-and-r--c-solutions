/* 5-1: As written, getint treats a + or - not followed by a digit
 * as a valid representation of zero. Fix it to push such a
 * character back on the input. */

#include <ctype.h>
#include <stdio.h>

#define SIZE 3

int getch(void);
void ungetch(int);

int getint(int *pn)
{
    int c, sign, tmp;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        tmp = c;
        c = getch();
        if (!isdigit(c) && c != EOF) {
            ungetch(c);
            ungetch(tmp);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main()
{
    int n, array[SIZE];

    for (n = 0; n < SIZE; n++)
        array[n] = 0;

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    for (n = 0; n < SIZE; n++)
        printf("%d: %d, ", n, array[n]);

    return 0;
}
