#include <stdio.h>

#define MAXLINE 1000
#define IN 1
#define OUT 0

/* 1-23: Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants
 * properly. C comments do not nest */


/* 16-05-29: Figure out how to handle newlines */


int getline(char line[], int limit);
void remove_comments(const char input[], char output[], int limit);


int main()
{
    int len;
    char line[MAXLINE], output[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        remove_comments(line, output, MAXLINE);
        printf("%s", output);
    }

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

void remove_comments(const char input[], char output[], int limit)
{
    int i, j, in;

    i = j = in = 0;

    for (i = 0; i < limit - 1 && input[i] != '\0'; ++i) {
        if (in == OUT) {
            if (input[i] == '/' && input[i + 1] == '*')
                in = IN;
            else
                output[++j] = input[i];
        } else {
            if (input[i] == '/' && input[i - 1] == '*')
                in = OUT;
        }
    }
}
