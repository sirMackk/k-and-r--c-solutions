#include <stdio.h>

/* 2-5: Write the function any(s1, s2), which returns the first location
 * in the string s1 where any character from the string s2 occurs, or -1
 * if s1 contains no characters from s2. */

signed int any(const char s1[], const char s2[]);

int main()
{
    signed int pos;
    char str1[] = "The lazy dog jumped over the lazy cat";
    char str2[] = "rzc";

    printf("Original: %s\n", str1);
    pos = any(str1, str2);
    printf("First occurance: %c - %d\n", str1[pos], pos);

    return 0;
}

signed int any(const char s1[], const char s2[])
{
    signed int pos;
    int i, j;

    pos = -1;

    for (i = 0; s1[i] != '\0' && pos < 0; ++i)
        for (j = 0; s2[j] != '\0' && pos < 0; ++j)
            if (s1[i] == s2[j])
                pos = (signed int) i;

    return pos;
}
