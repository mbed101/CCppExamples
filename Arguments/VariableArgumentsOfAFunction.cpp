
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

void simple_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0')
    {
        if (*fmt == 'd')
        {
            int i = va_arg(args, int);
            printf("%d\n", i);
        }
        else if (*fmt == 'c')
        {
            int i = va_arg(args, int);
            printf("%c\n", i);
        }
        else if (*fmt == 'f')
        {
            double f = va_arg(args, double);
            printf("%f\n", f);
        }

        ++fmt;
    }
    va_end(args);
}

int main()
{
    std::cout << "test"
              << "\n";

    simple_printf("dcff", 10, 'a', 10.01, 11.2);
}
