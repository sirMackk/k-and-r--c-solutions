/* 4.13 - Write a recursive version of the function reverse(s),
 * which reverses the string s in place. */

#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    static int i = 0;
    char c;
    int j = strlen(s) - i - 1;

    if (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++;
        reverse(s);
    } else {
        i = 0;
        return;
    }
}

int main()
{
    int i;
    char strings[][8] = {"catdog", "odd"};

    for (i = 0; i < 2; i++) {
        printf("str: %s\t", strings[i]);
        reverse(strings[i]);
        printf("reverse: %s\n", strings[i]);
    }

    return 0;
}
