/* 7-9: Functions like isupper can be implemented to save space
 * or to save time. Explore both possibilities. */

#include <stdio.h>

#define ISUPPER(a) ((a) >= 'A' && (a) <= 'Z')

int m_isupper(char c);

int main()
{
    printf("A isupper: %d\n", m_isupper('A'));
    printf("B ISUPPER: %d\n", ISUPPER('B'));
    printf("a isupper: %d\n", m_isupper('a'));
    printf("b ISUPPER: %d\n", ISUPPER('b'));

    return 0;
}

int m_isupper(char c)
{
    return c >= 'A' && c <= 'Z';
}


/* You can implement isupper as either a function or a macro.
 * A macro avoid the overhead of calling of a functionc all ie.
 * building and destroying the stackframe (saves time).
 * A function in turn prevents the preprocessor from
 * copying the same piece of code over and over again (saves space).
 */
