#include <math.h>

//fs(x)=(f(x+h)-f(x))/h
double functionNumericDeri(double(*function)(double),double x){
    double h = pow(10,-8);
    double m;

    m = (function(x+h)-function(x))/h;
    return m;
}