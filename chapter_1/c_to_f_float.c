#include <stdio.h>

/* print Celsius-Fahrenheit table
 * for celsius = 0, 20, ... 300; floating point version */
main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;

    printf("Celsius\t\tFahrenheit\n");

    while (celsius <= upper) {
        fahr = celsius * (9.0/5.0) + 32;
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
