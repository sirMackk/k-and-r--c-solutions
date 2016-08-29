/* 4-2: Extend atof to handle scientific notation in the form
 * 123.45-e6 where a floating-point number may be followed by e or E
 * and an optionally signed exponent. */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

double atof(char s[]);

int main()
{
    double atof(char []);
    printf("%s == %g\n", "10.23", atof("10.23"));
    printf("%s == %g\n", "300.00", atof("300.00"));
    printf("%s == %g\n", "3e2 == 300.00", atof("3e2"));
    printf("%s == %g\n", "3e10 == 30000000000", atof("3e10"));
    printf("%s == %g\n", "0.57e5 == 57000", atof("0.57e5"));
    printf("%s == %g\n", "0.57e-5 == 0.0000057", atof("0.57e-5"));
    return 0;
}

double atof(char s[])
{
    double val, power, scientific;
    int i, sign, scientific_sign;

    power = 1.0;

    /* skip whitespace */
    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.') {
        i++;

        for (power = 1.0; isdigit(s[i]); i++) {
            val = 10.0 * val + (s[i] - '0');
            power *= 10.0;
        }
    }

    if (s[i] != '\0' && s[i] == 'e') {
        int j;
        i++;

        scientific_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '-' || s[i] == '+');
            i++;

        j = strlen(s);


        for (scientific = 0.0; isdigit(s[i]); i++) {
            scientific += (s[i] - '0') * pow(10, (j - i - 1));
        }

        val *= pow(10, scientific_sign * scientific);
    }

    return sign * val / power;
}
