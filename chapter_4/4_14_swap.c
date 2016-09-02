/* 4-14: Define a macro swap(t, x, y) that interchanges two arguments
 * of type t. */

#include <stdio.h>

#define swap(t, x, y) \
    do { \
        t tmp = x; \
        x = y; \
        y = tmp; \
    } while(0)

int main()
{
    int i = 1;
    int j = 2;

    printf("Initial: i = %d, j = %d\n", i, j);
    swap(int, i, j);
    printf("Swapped: i = %d, j = %d\n", i, j);

    return 0;
}
