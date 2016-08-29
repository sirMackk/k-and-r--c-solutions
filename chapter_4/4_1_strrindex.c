/* 4-1: Write the function strrindex(s, t), which returns the position
 * of the rightmost occurence of t in s, or -1 if there is none. */

#include <stdio.h>
#include <string.h>

#include "getline.h"

int strrindex(char s[], char t[]);

int main()
{
    /*char output[32];*/
    char *inputs[] = {"How much wood would", "a wood chuck chuck",
                      "if a woodchuck", "could chuck wood?"};
    char *searches[] = {"wood", "chuck", "the", "could"};

    int i;

    for (i = 0; i < 4; i++) {
        printf("Input: %s\nSearch: %s\nIndex: %d\n",
               inputs[i], searches[i], strrindex(inputs[i], searches[i]));
    }
    return 0;
}

int strrindex(char s[], char t[])
{
    int i, j, k, t_len;

    t_len = strlen(t);

    for (i = strlen(s) - 1; i > 0; i--) {
        for (j = i, k = t_len - 1; j > 0 && k > 0 && s[j] == t[k]; j--, k--)
            ;

        if (k == 0) {
            return j;
        }
    }

    return -1;
}

