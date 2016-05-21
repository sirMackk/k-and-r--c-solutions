#include <stdio.h>

/* verify that the expressoin getchar() != EOF is 0 or 1 */
main()
{
    int c;

    c = getchar() != EOF;
    printf("getchar() != EOF is: %d\n", c);
}
