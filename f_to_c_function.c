#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float f_to_c(float fahr);

/* 1-15: Rewrite the temperature conversion program of section 1.2 to use
 * a function for conversion. */

main()
{
    float fahr;
    fahr = LOWER;

    for (fahr = 0; fahr < UPPER; fahr = fahr + STEP)
        printf("%3.0fF - %6.1fC\n", fahr, f_to_c(fahr));
}

float f_to_c(float fahr)
{
    return (5.0/9.0)*(fahr-32.);
}
