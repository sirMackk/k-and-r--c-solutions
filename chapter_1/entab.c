#include <stdio.h>

#define MAXLINE 1000
#define TABWIDTH 8

/* 1-21: Write a program entab that replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. Use the same tab stops
 * as for detab. When either a tab or a single blank would suffice to reach a
 * tab stop, which should be given preference? */

int getline(char line[], int limit);
void entab(const char line[], char output[]);

int main()
{
    char line[MAXLINE], output[MAXLINE];
    int len;

    while ((len = getline(line, MAXLINE)) > 0) {
        entab(line, output);
        printf("entabbed: %s", output);
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

void entab(const char line[], char output[])
{
    int i;
    int output_index;
    int spaces;
    i = output_index = spaces = 0;

    for (i = 0; i < MAXLINE; ++i)
        output[i] = '\0';

    for (i = 0; i < MAXLINE && line[i] != '\0'; ++i) {
        if (line[i] == ' ') {
            if ((i + 1) % TABWIDTH == 0) {
                output[output_index++] = '\t';
                spaces = 0;
            } else {
                ++spaces;
            }
        } else {
            while (spaces > 0) {
                output[output_index++] = ' ';
                --spaces;
            }
            output[output_index++] = line[i];
        }
    }

    output[output_index] = '\0';
}
