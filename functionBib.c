#include <stdio.h>
#include <math.h>

/*  
1) f(x)=(x-3)^2
2) fs(x)=2*(x-3)

2 functions --> 2 seperate methodes

*/

double function(double x){
    double y;
    y = pow((x-3),2);
    return y;
}

double functionDeri(double x){
    double m;
    m = 2.0*(x-3.0);
    return m;
}

double functionNumDiff(double x){
    double h = pow(10,-8);
    double m;

    m = (function(x+h)-function(x))/h;
    return m;
}