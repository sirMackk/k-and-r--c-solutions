#include <stdio.h>

#define PRINTLIMIT 80
#define MAXLINE 1000

int getline(char line[], int limit);
void copy(char from[], char to[]);

/* 1-17: Write a program to print all input lines that are longer than
 * 80 characters. */

main()
{
    int len;
    char line[MAXLINE];

    while((len = getline(line, MAXLINE)) > 0) {
        if (len > 80)
            printf("%s\n", line);
    }
}

int getline(char line[], int limit)
{

    int i, c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

void copy(char from[], char to[])
{
    int i;

    for (i = 0; (to[i] = from[i]) != '\0'; ++i)
            ;
}
