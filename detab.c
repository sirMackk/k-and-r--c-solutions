#include <stdio.h>

#define MAXLINE 1000
#define TABWIDTH 4

/* 1-20: Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed
 * set of tab stops, say every n columns. Should n be a variable or a 
 * symbolic parameter? */

int getline(char line[], int limit);
void detab(char line[], char output[]);

int main()
{
    char line[MAXLINE], output[MAXLINE];
    int len;

    while ((len = getline(line, MAXLINE)) > 0) {
        detab(line, output);
        printf("detabbed: %s", output);
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

void detab(char line[], char output[])
{
    int i, j, space_no;
    i = j = 0;

    for (i = 0; i < MAXLINE; ++i)
        output[i] = '\x41';
    output[i] = '\0';

    for (i = 0; i < MAXLINE; ++i, ++j) {
        if (line[i] == '\t') {
            space_no = i % TABWIDTH + 2;
            while (j < i + space_no) {
                output[j] = ' ';
                j++;
            }
            --j;
        } else {
            output[j] = line[i];
        }
    }
}



