/* 3-3: Write a function expand(s1, s2) that expands shorthand notation
 * like a-z in the string s1 into the equivalent complete list 
 * abc...xyz in s2. Allow for letters of either case and digits, and 
 * be prepared to handle cases like a-b-c and a-z0-9 and -a-z. 
 * Arrange that the leading or trailing - is taken literally.
 */

#include <stdio.h>

#define MAXLINE 1000
#define INRANGE 1
#define OUTOFRANGE 0

void expand(char s1[], char s2[]);
int c_in_range(char c);

int main() {
    char output[MAXLINE];

    char input[] = "-a-b-mA-Z0-9-\0";

    printf("input: %s\n", input);
    expand(input, output);
    printf("output: '%s'\n", output);


    return 0;
}

void expand(char s1[], char s2[]) {
    int i, j, c, in_range;

    in_range = OUTOFRANGE;

    i = j = 0;

    while (i < MAXLINE - 1 && s1[i] != '\n' && s1[i] != '\0') {
        c = s1[i];

        if (c_in_range(c) && s1[i+1] == '-' && c_in_range(s1[i+2])) {
            in_range = INRANGE;
        } else if (c == '-' && (s1[i+1] == '\0' || i == 0)) {
            s2[j++] = '-';
        }


        if (in_range) {
            if (s2[j-1] == c)
                c++;

            while (c != s1[i+2] + 1) {
                s2[j++] = c;
                c++;
            }
            in_range = OUTOFRANGE;
            i = i + 2;
        } else {
            ++i;
        }

    }
    s2[j] = '\0';
}

int c_in_range(char c) {
    if ((c > 47 && c < 58) || (c > 64 && c < 123))
        return 1;
    return 0;
}
