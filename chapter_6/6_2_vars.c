/* 6-2: Write a program that reads a C program and prints in alphabetical
 * order each group of variable names that are identical in the first
 * 6 characters, but different somewhere thereafter. Don't count words
 * in strings and comments. Make 6 a parameter that can be set from the
 * command line. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdup(char *);
void treeprint(struct tnode *);
int getword(char *, int);
int getch(void);
void ungetch(int);

int char_match = 6;

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

    if (*++argv)
        char_match = atoi(*argv);

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, char_match)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }

    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
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
    if (c == '"' || (c == '/' && tmp == '*')) {
        skip = 1;
        if (c == '/')
            ungetch(tmp);
        while (skip) {
            c = getch();
            if (c == '"' || (c == '*' && (tmp = getch()) == '/')) {
                skip = 0;
                if (c == '*')
                    ungetch(tmp);
            }
        }
    } else {
        ungetch(tmp);
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
