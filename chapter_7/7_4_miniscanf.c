/* 7-4: Write a private version of scanf analogous to miniprintf
 * from the previous section. */

#include <stdarg.h>
#include <stdio.h>

void miniscanf(char *, ...);


int main()
{
    char buf[100];
    int i;
    miniscanf("Please input a str and number> %s %d\n", buf, &i);
    printf("scanf output: %s, %d\n", buf, i);

    return 0;
}

void miniscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int *ip;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch(*++p) {
            case 'd':
                ip = va_arg(ap, void *);
                scanf("%d", ip);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf("%s", sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }

    va_end(ap);
}
