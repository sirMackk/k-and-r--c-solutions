#include <stdio.h>

/* 2-2: Write a loop equivalent to the foor loop above without using
 * && or ||. */

/* for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 *      s[i] = c;
 */

int getline(char line[], int limit);

int main()
{
    char line[100];
    int len;

    len = getline(line, 100);
    printf("%d - %s\n", len, line);

    return 0;
}

int getline(char line[], int limit)
{
    int i, c;

    i = 0;

    while (i < limit - 1) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        line[i++] = c;
    }
    line[i] = '\0';

    return i;
}
