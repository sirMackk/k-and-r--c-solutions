/* 7-8: Write a program to print a set of files, starting each new one
 * on a new page, with a title and w running page count for each file. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 8192
#define LINES 24

int main(int argc, char *argv[])
{
    char line[MAXLINE], *filenames[10], *result;
    int i, page, line_no;
    FILE *fd;

    for (i = 0; i < argc - 1; i++) {
        filenames[i] = (char *) malloc(strlen(*++argv));
        if (filenames[i] == NULL)
            continue;
        strcpy(filenames[i], *argv);
    }

    for (i = 0; i < argc - 1; i++) {
        page = 0;
        line_no = 0;

        fd = fopen(filenames[i], "r");
        if (fd == NULL) {
            printf("cannot open file '%s'\n", filenames[i]);
            continue;
        }

        while ((result = fgets(line, MAXLINE - 1, fd)) != NULL) {
            if (line_no % LINES == 0) {
                page++;
                printf("========================================\n");
                printf("Page: %d\t---\t%s\n", page, filenames[i]);
                printf("========================================\n");
            }
            line_no++;
            printf("%s", line);
        }
        fclose(fd);
    }

    return 0;
}
