/* getline - get input from user char by char until RETURN is pressed. */

#include <stdio.h>
#include "getline.h"


int getline(char s[], int lim)
{
    int c, i;

    i = 0;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}
