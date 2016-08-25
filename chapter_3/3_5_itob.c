/* 3-5: Write the function itob(n, s, b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n, s, 16) formats n as a hexadecimal integer in s. */

#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    int inputs[] = {12, 4, 88, 4312};
    int i;
    char output[32];

    for (i = 0; i < 4; ++i) {
        itob(inputs[i], output, 16);
        printf("%s\n", output);
    }
    return 0;
}

void itob(int n, char s[], int b)
{
    int i, j;
    i = 0;
    char map[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    do {
        j = n % b;
        s[i++] = map[j];
        n /= b;
    } while (n > 1);

    if ((j = n % b) > 0) {
        s[i++] = map[n % b];
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int len = strlen(s);
    int i, j, c;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
