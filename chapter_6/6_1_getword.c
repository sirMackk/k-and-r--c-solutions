/* 6-1: Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write
 * a better version. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"int", 0},
    {"static", 0},
    {"return", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

#define NKEYS (sizeof keytab / sizeof(struct key))
#define MAXWORD 100

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

int main(int argc, char *argv[])
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    }

    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else {
            return mid;
        }
    }

    return -1;
}

int skip = 0;

int getword(char *word, int lim)
{
    int c, tmp;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    tmp = getch();
    if (skip && ((c == '"' &&  skip) || (c == '*' && tmp == '/'))) {
        skip = 0;
    } else if (c == '"' || (c == '/' && tmp == '*')) {
        skip = 1;
        *w = '\0';
        if (c != '"')
            ungetch(tmp);
        return c;
    }
    ungetch(tmp);

    if (skip) {
        *w = '\0';
        return c;
    }

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;


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
