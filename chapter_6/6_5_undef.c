/* 6-5: Write a function undef that will remove a name and definiation
 * from the table maintained by lookup and install. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static struct nlist *hashtab[HASHSIZE];

int main()
{

    struct nlist *item;
    install("cat", "false");
    install("cxn", "true");
    item = lookup("cat");
    printf("%s - %p, %p\n", item->defn, item->next, item);
    item = lookup("cxn");
    printf("%s - %p, %p\n", item->defn, item->next, item);
    remove_def("cxn", "true");
    item = lookup("cxn");
    if (item != NULL)
        printf("%s - %p, %p\n", item->defn, item->next, item);

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
