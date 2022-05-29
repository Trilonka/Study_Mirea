#include <iostream>
#include <stdarg.h>
#include <complex>
using namespace std;

void my_printf(char* s, ...)
{
    va_list l;
    va_start(l, s);
    char* p = s;
    int d_value;
	double f_value;
	complex<double> c_value;
    while (*p) //while (*s!='\0') 
    {
        if (*p=='%')
        {
            switch (*++p)
            {
                case 'd': // int
                    d_value = va_arg(l, int);
                    printf("%d", d_value);
                    break;
                case 'f': // double
                    f_value = va_arg(l, double);
                    printf("%f", f_value); 
                    break;
				case 'C': // complex<double>
					c_value = va_arg(l, complex<double>);
					printf("%f + %fi", c_value.real(), c_value.imag());
					break;
                default: // default character
                    printf("%%");
                    printf("%c", *p);
            }
        } else 
		{
			printf("%c", *p);
		}
        *p++;
    }
    va_end(l);
}

int main()
{
	complex<double> com(7, -8);
	my_printf("Hello, i am integer: %d\nHi, i'm double: %f\nWow, and i'm complex: %C\nAm...I just t char: %t", 432, -63.234, com);
	my_printf("\nSome ints: %d, %d, %d.", 4, 12, -954);
}
