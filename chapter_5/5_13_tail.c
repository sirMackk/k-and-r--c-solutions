/* 5-13: Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, let us say, but it can be changed by an optional argument,
 * so that: tail -n - prints the last n lines. The program should behave rationally
 * no matter how unreasonable the input or the value of n. Write the program so it
 * makes thebest use of available storage; lines should be stored as in the sorting
 * program of section 5.6, not in a two dimensional array of fixed size. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXLINES 10000

static int line_no = 0;


int getline(char line[], int limit);
void print_usage(char *);

int main(int argc, char *argv[])
{
    int len, i, n;
    char line[MAXLINE], *lines[MAXLINES];

    if (argc <= 1) {
        print_usage(*argv++);
        return 0;
    }

    while (*++argv)
        if ((*argv)[0] == '-')
            n = atoi((*argv)+1);

    while((len = getline(line, MAXLINE)) > 0) {
        lines[line_no] = malloc(len);
        strncpy(lines[line_no], line, len);
        line_no++;
    }

    i = (line_no - n > 0) ? line_no - n : 0;

    for (; i < line_no; i++)
        printf("%s", lines[i]);

    return 0;
}

int getline(char line[], int limit)
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

void print_usage(char name[])
{
    printf("Usage: '%s -n' where n is a positive integer.\n", name);
}
