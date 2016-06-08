#include <stdio.h>

#define MAXLINE 1000

/* 2-10: Rewrite the function lower, which converst upper case letters
 * to lower case, with a conditional expression instead of if-else. */

char lower(char c);

int main()
{
    char i1 = 'A';
    char i2 = 'z';

    printf("A = %c\n", lower(i1));
    printf("z = %c\n", lower(i2));
    return 0;
}

char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
