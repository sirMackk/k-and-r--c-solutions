#include <stdio.h>

#define MAXLINE 1000

/* 3-2: Write a function escape(s,t) that converst characters like newline
 * and tab into visible sequences like \n and \t as it copies the string
 * t to s. Use a switch. Write a function for the other direction as well,
 * converting escape sequence into the real characters. */

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char str[] = "This is\t\t a\t\t\t\nstring\nwith many\n\tescapes.";
    char target[MAXLINE];

    escape(str, target);

    printf("escaped: %s\n", target);

    unescape(target, str);

    printf("unescaped: %s\n", str);
    return 0;
}

void escape(char s[], char t[])
{
    int i, j;
    for (i = j = 0; i < MAXLINE - 1 && s[i] != '\0'; ++i) {
        switch (s[i]) {
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }

    t[j++] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;
    for (i = j = 0; i < MAXLINE - 1 && s[i] != '\0'; ++i) {
        switch (s[i]) {
            case '\\':
                switch(s[++i]) {
                    case 't':
                        t[j++] = '\t';
                        break;
                    case 'n':
                        t[j++] = '\n';
                        break;
                }
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }

    t[j] = '\0';
}
