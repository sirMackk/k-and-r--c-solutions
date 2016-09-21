/* 7-1: Write a program that converts upper case to lower or lower case to
 * upper, depending on the name it is invoked with, as found in argv[0]. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int (*fn)(int) = toupper;
    int c, len;
    char *name;

    len = strlen(*argv);

    for (; len > 0; len--)
        if ((*argv+len)[0] == '/')
            break;

    name = (*argv+len+1);

    if (strcmp(name, "lower") == 0)
        fn = tolower;

    while ((c = getchar()) != EOF)
        putchar(fn(c));

    return 0;
}
