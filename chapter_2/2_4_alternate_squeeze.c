#include <stdio.h>

/* 2-4: Write an alternate version of squeeze(s1, s2) that deletes
 * each character in s1 that matches any character in the string s2. */

#define YES 1
#define NO 0

void squeeze(char s1[], const char s2[]);

int main()
{
    char str1[] = "The lazy dog jumps over the excited cat";
    char str2[] = "hoe";

    printf("Original:\t%s\n", str1);
    squeeze(str1, str2);
    printf("Updated:\t%s\n", str1);

    return 0;
}

void squeeze(char s1[], const char s2[])
{
    int i, j, k, skip;

    for (i = j = 0; s1[i] != '\0'; ++i) {
        skip = NO;
        for (k = 0; s2[k] != '\0'; ++k) {
            if (s1[i] == s2[k]) {
                skip = YES;
                break;
            }
        }

        if (skip == NO)
            s1[j++] = s1[i];
    }

    s1[j] = '\0';
}
