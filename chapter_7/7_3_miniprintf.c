/* 7-3: Revise miniprintf to handle more of the other facilities of
 * printf. */


#include <stdarg.h>
#include <stdio.h>

void miniprintf(char *, ...);


int main()
{
    char *p = "dogs";
    miniprintf("%d %f %s %p %x\n", 10, 5.25, "cats", p, 100);

    return 0;
}

void miniprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    void *uval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch(*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case 'p':
                uval = (void *) va_arg(ap, unsigned long);
                printf("%p", uval);
                break;
            case 'x':
                ival = va_arg(ap, int);
                printf("%x", ival);
                break;
            default:
                putchar(*p);
                break;
        }
    }

    va_end(ap);
}
