#include <stdio.h>

#define MAXLINE 1000

/* 1-18: Write a program to remove trailing blanks and tabs from each
 * line of input and to delete enitrely blank lines. */

int readline(char line[], int limit);
void remove_whitespace(char from[]);

int main()
{
    int len;
    char line[MAXLINE];

    while ((len = readline(line, MAXLINE)) > 0) {
        remove_whitespace(line);
        printf("%d: %s\n", len, line);
    }

    return 0;
}

int readline(char line[], int limit)
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

void remove_whitespace(char line[])
{
    int i, c, last_char;


    for (i = 0; (c = line[i]) != '\0'; ++i)
        if (c != ' ' && c != '\t' && c != '\n')
            last_char = i;

    if (last_char == 1 && line[last_char - 1] == '\n')
        line[0] = '\0';
    else
        line[last_char + 1] = '\0';
}
