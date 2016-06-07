#include <stdio.h>
#include <limits.h>

/* 2-1: Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate
 * values from standard headers and by direct computation. Harder if you
 * compute them: determine the ranges of the various floating-point
 * types */

int main()
{
    printf("Signed char min: %d\n", SCHAR_MIN);
    printf("Signed char max: %d\n", SCHAR_MAX);
    printf("Unsigned char min: %d\n", CHAR_MIN);
    printf("Unsigned char max: %d\n", CHAR_MAX);

    printf("signed short min: %d\n", SHRT_MIN);
    printf("signed short max: %d\n", SHRT_MAX);
    printf("unsigned short min: %d\n", 0);
    printf("unsigned short max: %d\n", USHRT_MAX);

    printf("signed int min: %d\n", INT_MIN);
    printf("signed int max: %d\n", INT_MAX);
    printf("unsigned int min: %d\n", 0);
    printf("unsigned int max: %d\n", UINT_MAX);

    printf("signed long min: %ld\n", LONG_MIN);
    printf("signed long max: %ld\n", LONG_MAX);
    printf("unsigned long min: %ld\n", 0ul);
    printf("unsigned long max: %ld\n", ULONG_MAX);

    return 0;
}
