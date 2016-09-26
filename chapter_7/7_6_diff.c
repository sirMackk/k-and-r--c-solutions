/* 7-6: Write a program to compare two files, printing the first line where
 * they differ. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096

int read_two_lines(FILE *, FILE *, char *, char *);
int compare_line(char *, char *);

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line_fp1[MAXLINE], line_fp2[MAXLINE];

    if (argc != 3) {
        printf("usage: %s file1 file2\n", argv[0]);
        return 0;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    if (fp1 == NULL) {
        printf("Cannot open file '%s' for reading, exiting\n", argv[1]);
        return 1;
    } else if (fp2 == NULL) {
        printf("Cannot open file '%s' for reading, exiting\n", argv[2]);
        return 1;
    }

    while (read_two_lines(fp1, fp2, line_fp1, line_fp2) > 0) {
        if (compare_line(line_fp1, line_fp2)) {
            printf("Differing lines:\n");
            printf("=== %s: \n%s\n", argv[1], line_fp1);
            printf("=== %s: \n%s\n", argv[2], line_fp2);
            return 1;
        }

    }

    return 0;
}

int read_two_lines(FILE *f1, FILE *f2, char *line1, char *line2)
{
    char *l1, *l2;
    l1 = fgets(line1, MAXLINE - 1, f1);
    l2 = fgets(line2, MAXLINE - 1, f2);
    return (l1 == NULL || l2 == NULL) ? 0 : 1;
}

int compare_line(char *line1, char *line2)
{
    return strncmp(line1, line2, MAXLINE);
}
