/* 6-4: Write a program that prints the distinct words in its input sorted
 * into decreasing order of frequency of occurance. Precede each word
 * by its count. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tnode {
    char *word;
    int count;
    int read;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdup(char *);
void treeprint(struct tnode *);
void tree_sort_print(struct tnode *);
int getword(char *, int);
int getch(void);
void ungetch(int);
struct tnode *df_reader(struct tnode *);

struct tnode *treesort(struct tnode *, struct tnode *);


int main(int argc, char *argv[])
{
    struct tnode *root, *sorted_root, *item;
    char word[MAXWORD];

    root = NULL;
    item = NULL;
    sorted_root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    while ((item = df_reader(root)) != NULL)
        sorted_root = treesort(sorted_root, item);

    tree_sort_print(sorted_root);
    return 0;
}

struct tnode *df_reader(struct tnode *tree)
{
    if (tree->left != NULL && !tree->left->read) {
        return df_reader(tree->left);
    } else if (tree->right != NULL && !tree->right->read) {
        return df_reader(tree->right);
    } else if (!tree->read) {
        tree->read = 1;
        return tree;
    } else {
        return NULL;
    }
}


struct tnode *treesort(struct tnode *parent, struct tnode *item)
{

    if (parent == NULL) {
        parent = talloc();
        parent->word = strdup(item->word);
        parent->count = item->count;
        parent->read = 0;
        parent->left = parent->right = NULL;
    } else if (item->count > parent->count) {
        parent->right = treesort(parent->right, item);
    } else if (item->count <= parent->count) {
        parent->left = treesort(parent->left, item);
    }

    return parent;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->read = 0;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
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

void tree_sort_print(struct tnode *p)
{
    if (p != NULL) {
        tree_sort_print(p->right);
        printf("%4d %s\n", p->count, p->word);
        tree_sort_print(p->left);
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
