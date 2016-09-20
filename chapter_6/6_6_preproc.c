/* 6-6: Implement a simple version of the #define processor (i.e, no
 * arguments) suitable for use with C programs, based on the routines
 * of this section. You may also find getch and ungetch helpful. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101

unsigned int hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *strdup(char *);

void remove_def(char *, char *);

int getword(char *, int);
int getch(void);
void ungetch(int);

static struct nlist *hashtab[HASHSIZE];

#define MAXWORD 100

int main()
{
    char word[MAXWORD], *name, *defn;
    int in_define = 0;
    struct nlist *item;


    while (getword(word, MAXWORD) != EOF) {
        if (word[0] != ' ' && in_define == 1) {
            name = strdup(word);
            in_define++;
        } else if (word[0] != ' ' && in_define == 2) {
            defn = strdup(word);
            install(name, defn);
            in_define = 0;
        }

        if (strcmp(word, "#define") == 0)
            in_define = 1;

        if ((item = lookup(word)) != NULL)
            printf("%s", item->defn);
        else
            printf("%s", word);
    }

    return 0;
}

unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}


char *strdup(char *s)
{
    char *new_str;
    new_str = (char *) malloc(strlen(s) + 1);

    if (new_str != NULL) {
        strcpy(new_str, s);
    }

    return new_str;
}

void remove_def(char *name, char *defn)
{
    struct nlist *p, *current;
    p = current = NULL;

    for ((current  = hashtab[hash(name)]); current != NULL; current = current->next) {
        if (strcmp(current->name, name) == 0 && strcmp(current->defn, defn) == 0) {
            if (p == NULL) {
                hashtab[hash(name)] = current->next;
            } else {
                p->next = current->next;
            }

            free((void *) current->name);
            free((void *) current->defn);
            free((void *) current);
            break;
        } else {
            p = current;
        }
    }
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

/* Modified getword function. doesnt skip spaces, comments, or strings.
 * Additionally, treats strings of digits as valid words to return. */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    c = getch();

    if (c != EOF)
        *w++ = c;


    if (!isalnum(c) && c != '_' && c != '#') {
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
