/* 5-5: Write versions of the library functions strncpy, strncat,
 * and strncmp, which operate on at most the first n characters of
 * their argument strings. For example, strncpy(s, t, n) copies
 * at most n characters of t to s. Full descriptions are in Appendix
 * B. */

#include <stdio.h>
#include <string.h>

char *m_strncpy(char *, char *, size_t);
char *m_strncat(char *, char *, size_t);
int m_strncmp(char *, char *, size_t);

int main()
{
    char s1[32] = "catdogtown";
    char s1a[32] = "catdogtown";
    char s2[32] = "catdogcity";
    char s3[32];

    char s4[32];

    char s5[32] = "citycat";
    char s6[32] = "megacatcity";

    char *pt;
    int result;

    pt = m_strncpy(s3, s1, (size_t) 3);
    printf("Expected '%s', got: '%s'\n", strncpy(s4, s1, 3), pt);

    pt = m_strncat(s1, s2, (size_t) 6);
    printf("Expected '%s', got: '%s'\n", strncat(s1a, s2, 6), pt);

    result = m_strncmp(s1, s1, (size_t) 6);
    printf("Expected %d, got %d\n", strncmp(s1, s1, 6), result);

    result = m_strncmp(s1, s2, (size_t) 8);
    printf("Expected %d, got %d\n", strncmp(s1, s2, 8), result);

    result = m_strncmp(s2, s1, (size_t) 8);
    printf("Expected %d, got %d\n", strncmp(s2, s1, 8), result);

    result = m_strncmp(s1, s2, (size_t) 6);
    printf("Expected %d, got %d\n", strncmp(s1, s2, 6), result);

    result = m_strncmp(s2, s1, (size_t) 6);
    printf("Expected %d, got %d\n", strncmp(s2, s1, 6), result);

    result = m_strncmp(s5, s6, (size_t) 6);
    printf("Expected %d, got %d\n", strncmp(s5, s6, 6), result);

    result = m_strncmp(s6, s5, (size_t) 6);
    printf("Expected %d, got %d\n", strncmp(s6, s5, 6), result);


    return 0;
}

char *m_strncpy(char *dest, char *src, size_t n)
{
    int i;
    char *dest_start = dest;

    for (i = 0; *src != '\0' && i < n; i++, src++, dest++)
        *dest = *src;

    *dest = '\0';

    return dest_start;
}

char *m_strncat(char *dest, char *src, size_t n)
{
    int i;
    char *dest_start = dest;

    while (*++dest != '\0')
        ;

    for (i = 0; *src != '\0' && i < n; i++, src++, dest++)
        *dest = *src;

    *dest = '\0';

    return dest_start;
}

int m_strncmp(char *s1, char *s2, size_t n)
{
    int i, j;

    i = j = 0;
    for (; i < n - 1 && *s1 == *s2; ++s1, ++s2, ++i)
        ;

    if (*s1 == *s2)
        return 0;


    j = i;
    while (*s1++ != '\0')
        i++;

    while (*s2++ != '\0')
        j++;

    if (i > j)
        return i + 1;
    else
        return -j - 1;
}
