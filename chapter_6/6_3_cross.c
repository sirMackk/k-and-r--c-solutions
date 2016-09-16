/* 6-3: Write a cross-referencer that prints a list of all words in
 * a document, and, for each word, a list of the linenumbers on which
 * it occurs. Remove noise words like "the", "and", and so on. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINENOMAX 1000

struct tnode {
    char *word;
    char lines[LINENOMAX];
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);

char *strdup(char *);

void treeprint(struct tnode *);
int legal_word(char *);

int getword(char *, int);
int getch(void);
void ungetch(int);

int line_no = 1;

char *illegal_words[] = {
    "the",
    "and",
    "that",
    "and",
    "or",
    "to",
    NULL
};


int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

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
        sprintf(p->lines, "%d, ", line_no);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        sprintf(p->lines + strlen(p->lines)-1, "%d, ", line_no);
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
        printf("%s: %s\n", p->word, p->lines);
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

int skip = 1;
int getword(char *word, int lim)
{
    int c;
    char *w;

    while (1) {
        w = word;

        do {
            c = getch();
            if (c == '\n') {
                line_no++;
            } else if (c == EOF || isalpha(c)) {
                skip = 0;
            } else {
                skip = 1;
            }
        } while (skip);

        if (c != EOF)
            *w++ = c;


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
        if (legal_word(&word[0]))
            return word[0];
    }
}

int legal_word(char *s)
{
    char **p = illegal_words;
    int legal = 1;

    while (*++p) {
        if (strcmp(*p, s) == 0)
            legal = 0;
    }

    return legal;
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
