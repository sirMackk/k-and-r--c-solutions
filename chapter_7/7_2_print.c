/* 7-2: Write a program that iwll print arbitrary input in a sensible way.
 * As a minimum, it should print non-graphic characters in octal or hexidecimal
 * according to local custom, and break long text lines. */

#include <stdio.h>

static char buf[4];
static int line_length = 0;

char *process_char(char c)
{
    line_length++;
    if (c == '\n') {
        line_length = 0;
        sprintf(buf, "%c",'\n');
        return buf;
    }

    if (line_length > 79) {
        line_length = 0;
        ungetc(c, stdin);
        sprintf(buf, "%c", '\n');
        return buf;
    }

    if (c < 32 || c > 126) {
        sprintf(buf, "x%02x", c);
        return buf;
    } else {
        sprintf(buf, "%c", c);
        return buf;
    }

    sprintf(buf, "%c", ' ');
    return buf;
}

int main()
{
    char c, *item;

    while ((c = getchar()) != EOF) {
        item = process_char(c);
        printf("%s", item);
    }

    return 0;
}
