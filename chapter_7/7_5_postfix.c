/* 7-5: Rewrite the postfix calculator of Chapter 4 to use scanf and/or
 * sscanf to do the input and number conversion. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define OPERATOR '1'
#define NUMBER '0'

int sp = 0;
double val[MAXVAL];

int getop(double *, char *);
void push(double);
double pop(void);
void peek(void);
void dupe(void);
void swap(void);
void clear_stack(void);
void print_stack(void);

char buf[MAXOP];

int main()
{
    int type;
    double op2, dp;
    char s[MAXOP], dc[MAXOP];


    while ((type = getop(&dp, dc)) != EOF) {
        if (type == NUMBER) {
            push(dp);
        }
        else if (type == OPERATOR) {
            switch (*dc) {
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
    }
    return 0;
}

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

int getch(void);
void ungetch(int);

int getop(double *dp, char *cp)
{
    if (scanf("%lf", dp)) {
        return NUMBER;
    } else if (scanf(" %c", cp)) {
        return OPERATOR;
    }

    printf("EOF\n");
    return EOF;
}
