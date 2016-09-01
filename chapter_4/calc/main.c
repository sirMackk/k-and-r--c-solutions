#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#include <stdlib.h>
#include <math.h>
#include "calc.h"
#define MAXOP 100

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
            switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case 'p':
                peek();
                break;
            case 'd':
                dupe();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear_stack();
                break;
            case 'o':
                print_stack();
                break;
            case 'i':
                push(sin(pop()));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case 'l':
                op2 = pop();
                push(pow(op2, pop()));
                break;
            case '\n':
                /*printf("\t%.8g\n", pop());*/
                break;
            default:
                printf("error: unknown command '%s'\n", s);
                break;
            }
    }
    return 0;
}
