#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef CALCH
#define CALCH
#include "calc.h"
#endif

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];


void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void peek(void)
{
    if (sp > 0)
        printf("top of stack: %g\n", val[sp - 1]);
    else
        printf("error: stack empty\n");
}

void dupe(void)
{
    double tmp;
    tmp = pop();
    push(tmp);
    push(tmp);
}

void swap(void)
{
    double item1, item2;
    item1 = pop();
    item2 = pop();
    push(item1);
    push(item2);
}

void clear_stack(void)
{
    int i;
    for (i = 0; i < sp; i++)
        val[i] = 0.0;

    sp = 0;
}

void print_stack(void)
{
    int i;
    if (sp > 0)
        for (i = sp - 1; i >= 0; i--)
            printf("%d: %g\n", sp - i, val[i]);
    else
        printf("error: stack empty\n");
}
