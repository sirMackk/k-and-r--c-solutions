/* 5-12: Extend entab and detab to accept the shorthand entab +m -n to mean
 * tab stops every n columns, starting at column m. Choose convenient
 * (for the user) default behavior. */

#include <stdio.h>
#include <stdlib.h>

int get_next_tab(void);
int getline(char line[], int limit);
void entab(const char line[], char output[]);
void detab(char line[], char output[]);
void print_usage(char []);

#define MAXLINE 1000
#define TABWIDTH 5
#define TABSTOPS 2

static int tabstops[TABSTOPS];

int main(int argc, char *argv[])
{
    int i, len;
    char line[MAXLINE], output[MAXLINE];

    if (argc <= 1)
        print_usage(argv[0]);

    for (i = 0; i < TABSTOPS; i++)
        tabstops[i] = TABWIDTH;

    /* read -n and +n */
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            tabstops[1] = atoi(argv[i]+1);
        } else if (argv[i][0] == '+') {
            tabstops[0] = atoi(argv[i]+1);
        }
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        entab(line, output);
        printf("entabbed: %s\n", output);
        detab(line, output);
        printf("detabbed: %s\n", output);
    }

    return 0;
}

void print_usage(char name[])
{
    printf("Usage: %s +m -n - add tabstops everyn columns starting from m\n", name);
    printf("Default n = m = 5.\n");
}

/* use the first tabstop (m) ONCE, then always use the second tabstop (n). */
int get_next_tab(void)
{
    static int i = 0;
    return (i == 0) ? tabstops[i++] : tabstops[i];
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
