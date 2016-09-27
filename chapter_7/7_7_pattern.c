/* 7-7: Modify the pattern finding program of Chapter 5 to take its input
 * from a set of named files or, if no files are named as arguments, from
 * the standard-input. Should the file name be printed when a matching
 * line is found? */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

int getline(char *line, int max);

int main(int argc, char *argv[])
{
    char line[MAXLINE], pattern[MAXLINE], *filenames[10], *result;
    long lineno;
    int c, except = 0, number = 0, found = 0, patterns = 0;
    FILE *fd;

    if (argc < 1)
        printf("usage: find -x -n pattern filename1 filename2\n");

    /* Process arguments: args starting with '-' are flags, the first
     * arg that does't start with '-' is the pattern to search for,
     * and all remaining args are treated as filenames. */
    while (--argc > 0 && (c = (*++argv)[0]))
        switch (c) {
            case '-':
                c = *++argv[0];
                switch (c) {
                    case 'x':
                        except = 1;
                        break;
                    case 'n':
                        number = 1;
                        break;
                    default:
                        printf("find: illegal option %c\n", c);
                        argc = 0;
                        found = -1;
                        break;
                }
                break;
            default:
                if (!patterns) {
                    strncpy(pattern, *argv, MAXLINE - 1);
                    patterns = 1;
                } else {
                    filenames[patterns - 1] = (char *) malloc(strlen(*argv) + 1);
                    /* does not check for null, potential error */
                    strcpy(filenames[patterns - 1], *argv);
                    patterns++;
                }
                break;
        }

    /* Iterate over filenames, opening each one and searching for 'pattern'
     * line by line. */
    for (c = 0; c < patterns - 1; c++) {
        fd = fopen(filenames[c], "r");
        if (fd == NULL) {
            printf("Cannot open '%s', skipping.\n", filenames[c]);
            continue;
        }
        lineno = 0;
        while ((result = fgets(line, MAXLINE - 1, fd)) != NULL) {
            lineno++;
            if((strstr(line, pattern) != NULL) != except) {
                if (number)
                    printf("%ld: ", lineno);
                printf("(%s): %s", filenames[c], line);
                found++;
            }
        }

        fclose(fd);
    }

    return found;
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
