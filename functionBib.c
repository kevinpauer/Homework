#include <stdio.h>
#include <math.h>

//f(x)=(x-3)^2
double function(double x){
    double y;
    y = pow((x-3),2);
    return y;
}

//fs(x)=2*(x-3)
double functionDeri(double x){
    double m;
    m = 2.0*(x-3.0);
    return m;
}
//fs(x)=(f(x+h)-f(x))/h
double functionNumDiff(double x){
    double h = pow(10,-8);
    double m;

    m = (function(x+h)-function(x))/h;
    return m;
}