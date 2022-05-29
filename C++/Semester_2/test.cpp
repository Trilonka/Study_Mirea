#include <iostream>
#include <stdarg.h>
#include <complex>
using namespace std;

void my_printf(char* s, ...)
{
    va_list l;
    va_start(l, s);
    char* p = s;
    int n_value;
    //Fraction f; // (1)
    while (*p) //while (*s!='\0') 
    {
        if (*p=='%')
        {
            switch (*++p)
            {
                case 'd':
                    n_value = va_arg(l, int);
                    printf("%d", n_value);
                    break;
                // case 'F': // (1)
                //     f = va_arg(l, Fraction);
                //     printf("%d/%d", F.num_r, F.num_z); 
                //     break;
                default:
                    printf("%");
                    printf("%c", *p);
            }
        }
        *p++;
    }
    //va_arg(type, l);
    va_end(l);
}

double product(double arg,...)
{
    // if (arg==0) return ?; throw ?;
    double* ptr = &arg;
    double res = *++ptr;
    while (*++ptr!=0.0)
    {
        res*= *ptr;
    }
    return res;
}

int Max(int n, ...) // попробовать дома на ПК
{
    int* p = &n;
    p++; p++; p++;
    int m = *++p;
    for (int i = 0; i<n-1; i++)
    {
        p++; p++;
        if (m < *p)
            m = *p;
    }
    return m;
}

int my(double n,...)
{
    double* p = &n;
    double m = *++p;
    cout << m << endl;
    cout << p << endl;
    cout << *p << endl;

    cout << "What am i doing?\n";

    for (int i = 0; i<8; i++)
    {
        cout << p << endl;
        cout << *p << endl << endl;
        p++;
    }
}

int main()
{
    //my_printf("Int value = &d, Fraction = %f", 2, F);
    
    double a = product(2.0, 3.0, 5.0, 0.0);
    int b = Max(3, a, 5, 7);
    cout << a << " " << b << endl;

}