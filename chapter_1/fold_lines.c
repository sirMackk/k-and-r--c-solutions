#include <stdio.h>

#define MAXLINE 1000
#define MAXCOL 14

/* 1-22: Write a program to "fold" long input lines into two or more shorter
 * lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent
 * with very long lines, and if there are no blanks or tabs before
 * the specified column. */

/* 16-05-28 - Does not handle 'ragged' output well. */
/* 16-05-29 - new version - better ragged output handling, 
 * still some issues */

int getline(char line[], const int limit);
void fold(const char line[], char output[], const int max_fold);
void fold2(const char line[], char output[], const int max_fold);

int main()
{
    int len;
    char line[MAXLINE], output[MAXLINE];

    while ((len = getline(line, MAXLINE)) != 0) {
        fold2(line, output, MAXCOL);
        printf("%s", output);
    }

    return 0;
}

int getline(char line[], const int limit)
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

void fold(const char input[], char output[], const int max_fold)
{
    int i, j, k, last_blank;

    i = j = k = last_blank = 0;

    for (i = 0; i < MAXLINE && input[i] != '\0'; ++i) {
        if (input[i] == ' ') {
            last_blank = i;
        }

        if (++k > max_fold) {
            printf("%d - %d - %d\n", i, k, last_blank);
            if (last_blank == 0) {
                output[j++] = '\n';
                k = 0;
            } else {
                output[last_blank] = '\n';
                k = k - last_blank;
            }
            last_blank = 0;
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
}
