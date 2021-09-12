#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int len;
    int curmax;
    int max;
    int c;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
        /* 1-16: Revise the main routine of the longest line program
         * so it will correctly print the length of arbitrarily long
         * input lines, and as much as possible of the text. */
        if (len == MAXLINE - 1)
        {
            curmax = len;
            c = getchar();

            while (c != EOF && c != '\n')
            {
                    ++curmax;
                    c = getchar();
            }

            if (c == '\n')
            {
                    ++curmax;
            }

            if (curmax > max)
            {
                    max = curmax;
            }
        }
    }

    if (max > 0)
        printf("%d: %s", max, longest);
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is bug enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
