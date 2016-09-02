/* 5-2: Write getfloat, the floating-point analog of getint. What
 * type does getfloat return as it function value? */

#include <stdio.h>
#include <ctype.h>

#define SIZE 3

int getch(void);
void ungetch(int);
int getfloat(double *);
int power(int, int);

int main()
{

    int n;
    double array[SIZE];

    for (n = 0; n < SIZE; n++)
        array[n] = 0.0;

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    for (n = 0; n < SIZE; n++)
        printf("%d: %g\t", n, array[n]);

    printf("\n");

    return 0;
}

int getfloat(double *pn)
{
    int c, sign, i;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    if (c != '.')
        return c;

    c = getch();

    for (i = 1; isdigit(c); c = getch(), i++)
        *pn += (c - '0') / (float) power(10, i);

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int power(int a, int b)
{
    int i, j;
    for (i = 1, j = 1; i < b + 1; i++)
        j *= a;

    return j;
}
