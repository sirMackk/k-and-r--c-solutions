#include <stdio.h>

#define MAXLINE 1000

/* 1-19: Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverse its input a line
 * at a time. */

int getline(char line[], int limit);
void reverse(char from[], char to[], int length);

int main()
{
    int len;
    char line[MAXLINE];
    char output[MAXLINE];

    while((len = getline(line, MAXLINE)) != 0) {
        reverse(line, output, len);
        printf("%s\n", output);
    }

    return 0;
}

int getline(char line[], int limit)
{
    int i, c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    line[i] = '\0';
    return i;
}

void reverse(char from[], char to[], int len)
{
    int i;

    for (i = len - 1; i >= 0; i--)
        to[len-i] = from[i];

    to[len + 1] = '\0';
}
