#include <stdio.h>

/* 3-1: Our binary search makes two tests inside the loop, when one would
 * suffice (at the price of more tests outside). Write a version with
 * only one test inside the loop and measure the difference in run-time. */

int binsearch(int x, int v[], int n);

int main()
{
    int array[] = {2, 5, 6, 7, 10, 15, 25, 28, 55, 71, 72, 73, 88};

    printf("binsearch 15: %d\n", binsearch(15, array, 13));
    printf("binsearch 16: %d\n", binsearch(16, array, 13));

    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (v[mid] == x)
        return mid;
    else
        return -1;
}
