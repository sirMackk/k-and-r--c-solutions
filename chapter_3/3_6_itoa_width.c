/* 3-6: Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted
 * number must be padded with blanks on the left if necessary to make
 * it wide enough. */

#include <stdio.h>
#include <string.h>

#define MAXOUT 100

void itoa(int n, char s[], int width);
void reverse(char s[]);

int main()
{
    signed int inputs[] = {13, -5814, 125123};
    int widths[] = {3, 12, 8};
    int i;
    char output[MAXOUT];

    for (i = 0; i < 3; ++i) {
        itoa(inputs[i], output, widths[i]);
        printf("%d: %s\n", i, output);
    }
    return 0;
}

void itoa(int n, char s[], int width)
{
    int i, sign;

    sign = (n < 0) ? -1 : 1;
    i = 0;

    do {
        s[i++] = sign * (n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    if (i < width) {
        for (; i < width - 1; i++) {
            s[i] = ' ';
        }
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int len, i, j, c;
    len = strlen(s);

    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
