/* 4-5: Reverse Polish notation calculator.
 * Add access to library functions like sin, exp, and pow. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define VARIABLE '1'

int sp = 0;
double val[MAXVAL];
int variable;
char vars[27];
char map[] = "abcdefghijklmnopqrstuvwxyz_";

int getop(char []);
void push(double);
double pop(void);
void peek(void);
void dupe(void);
void swap(void);
void clear_stack(void);
void print_stack(void);

int get_index(char);
double get_var(int);
void print_vars(void);

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
            case VARIABLE:
                push(vars[variable]);
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
            case '!':
                peek();
                break;
            case '@':
                dupe();
                break;
            case '#':
                swap();
                break;
            case '$':
                clear_stack();
                break;
            case '%':
                print_stack();
                break;
            case '^':
                push(sin(pop()));
                break;
            case '&':
                push(exp(pop()));
                break;
            case ')':
                op2 = pop();
                push(pow(op2, pop()));
                break;
            case '=':
                /* pop empty item */
                pop();
                vars[variable] = pop();
                break;
            case '(':
                print_vars();
                break;
            case '\n':
                op2 = pop();
                vars[26] = op2;
                printf("\t%.8g\n", op2);
                break;
            default:
                printf("error: unknown command '%s'\n", s);
                break;
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

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (isalpha(c)) {
        variable = get_index(c);
        return VARIABLE;
    }

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


#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int get_index(char c)
{
    char *result;
    result =  strchr(map, c);
    if (!result)
        return -1;
    return result - map;
}

void print_vars(void)
{
    int i;
    for (i = 0; i < strlen(map); i++)
        printf("%c = %d\n", map[i], vars[i]);
}
