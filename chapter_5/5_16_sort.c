/* 5-16: Add the -d ("directory order") option, which makes comparisons only on letters
 * numbers, and blanks. Make sure it works in conjunction with -f. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 100

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int getline(char *, int);

void my_qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));

int numcmp(char *, char *);
void swap(void *v[], int, int);

void lowercase(char *);
void directory(char *);

int numeric, reverse, fold, dir;

int main(int argc, char *argv[])
{
    int nlines;

    numeric = reverse = fold = dir = 0;


    while (*++argv) {
        if (strcmp(*argv, "-n") == 0)
            numeric = 1;
        else if (strcmp(*argv, "-r") == 0)
            reverse = 1;
        else if (strcmp(*argv, "-f") == 0)
            fold = 1;
        else if (strcmp(*argv, "-d") == 0)
            dir = 1;

    }


    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort((void **) lineptr, 0, nlines-1,
                (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void my_qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last, cmp;
    char s1[1000], s2[1000];

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left+1; i <= right; i++) {
        if (!numeric) {
            strcpy(s1, v[i]);
            strcpy(s2, v[left]);

            if (dir) {
                directory(s1);
                directory(s2);
            }

            if (fold) {
                lowercase(s1);
                lowercase(s2);
            }

            cmp = (*comp)(s1, s2);
        } else {
            cmp = (*comp)(v[i], v[left]);
        }
        cmp = (reverse) ? -cmp : cmp;
        if (cmp < 0)
            swap(v, ++last, i);
    }

    swap(v, left, last);
    my_qsort(v, left, last-1, comp);
    my_qsort(v, last+1, right, comp);
}

#include <stdlib.h>
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 1)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len-1] = '\0';
            p = malloc(len);
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

int getline(char *line, int limit)
{
    int i, c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n') {
        line[i] = '\n';
        ++i;
    }

    line[i] = '\0';

    return i;
}

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void lowercase(char *input)
{
    int i;

    for (i = 0; input[i]; i++)
        input[i] = tolower(input[i]);

}

void directory(char *input)
{
    int i, j, len, c;

    len = strlen(input);

    for (i = 0, j = 0; i < len; i++) {
        if ((c = input[i]) == ' ' || isalnum(c))
            input[j++] = c;
    }

    input[j] = '\0';
}
