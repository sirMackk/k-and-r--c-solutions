/* 5-4: Write the function strend(s, t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise. */

#include <stdio.h>

int strend(char *, char *);

int main()
{
    char s1[] = "catdogtown";
    char s2[] = "dogbertcity";

    printf("Result - %s - %d\nResult - %s - %d\n", s1, strend(s1, "town"), s2, strend(s2, "town"));

    return 0;
}

int strend(char *s, char *t)
{
    char *start_t = t;

    while (*s++ != '\0')
        ;

    while (*t++ != '\0')
        ;

    while (*--t == *--s && t != start_t)
        ;

    if (t == start_t)
        return 1;
    else
        return 0;
}

