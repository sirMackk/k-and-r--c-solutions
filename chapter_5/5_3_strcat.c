/* 5-3: Write a pointer version of the function
 * strcat that we showed in chapter 2: strcat(s,t) copies the string
 * t to the end of s. */

#include <stdio.h>

void m_strcat(char *s, char *t)
{
    while (*++s != '\0')
        ;

    while (*s++ = *t++)
        ;

    *s = '\0';
}

int main()
{
    char s[40] = "catdog";
    char t[40] = "-dogtown";
    m_strcat(s, t);
    printf("%s\n", s);

    return 0;
}
