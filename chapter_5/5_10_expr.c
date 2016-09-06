/* 5-10: Write the program expr, which evaluates a reverse polish notation
 * expression from the command line, where each operator or operand is a
 * separate argument. For example: expr 2 3 4 + * evaluates to
 * 2 * (3 + 4) */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'

double val[MAXVAL];

int getop_argv(char *, char *);
void push(double);
double pop(void);
void peek(void);
void dupe(void);
void swap(void);
void clear_stack(void);
void print_stack(void);

int getop_argv(char s[], char arg[])
{
    int i, c, j;
    for (j = 0; (s[0] = c = arg[j]) == ' ' || c == '\t'; j++)
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;


    if (isdigit(c))
        for (i = 0; isdigit(s[i] = c = arg[j]); ++i, ++j)
            ;

    if (c == '.')
        for (; isdigit(s[i] = c = arg[j]); ++i, ++j)
            ;

    s[i] = '\0';

    return NUMBER;
}


int main(int argc, char *argv[])
{
    int type, i;
    double op2;
    char s[MAXOP];
    for (i = 1; i < argc && (type = getop_argv(s, argv[i])) != EOF; i++) {
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
    peek();
    return 0;
}
