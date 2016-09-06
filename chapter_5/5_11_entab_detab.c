/* 5-11: Modify the programs entab and detab (written as exercises in Chapter 1)
 * to accept a list of tab stops as arguments. Use the default tab settings if
 * there are no arguments. */

#include <stdio.h>
#include <stdlib.h>

int get_next_tab(void);
int getline(char line[], int limit);
void entab(const char line[], char output[]);
void detab(char line[], char output[]);

#define MAXLINE 1000
#define MAXARGS 1000
#define TABWIDTH 5

static int tabstops[MAXARGS];

int main(int argc, char *argv[])
{
    int i, len;
    char line[MAXLINE], output[MAXLINE];

    for (i = 1; i < argc; i++)
        tabstops[i] = atoi(argv[i]);

    printf("Type something with spaces:\n");
    while ((len = getline(line, MAXLINE)) > 0) {
        printf("input: %s\n", line);
        entab(line, output);
        printf("entabbed: %s\n", output);
        detab(line, output);
        printf("detabbed: %s\n", output);
    }

    return 0;
}

int get_next_tab(void)
{
    static int i = 0;
    return (tabstops[i] == 0) ? TABWIDTH : tabstops[i++];
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
            if ((i + 1) % get_next_tab() == 0) {
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

void detab(char line[], char output[])
{
    int i, j, space_no;
    i = j = 0;

    for (i = 0; i < MAXLINE; ++i)
        output[i] = '\x41';
    output[i] = '\0';

    for (i = 0; i < MAXLINE; ++i, ++j) {
        if (line[i] == '\t') {
            space_no = i % get_next_tab() + 2;
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
