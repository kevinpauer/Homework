#include <math.h>

//f(x)=(x-3)^2
double function(double x){
    double y;
    y = pow((x-3),2);
    return y;
}

//fs(x)=2*(x-3)
double functionAnalyticDeri(double x){
    double m;
    m = 2.0*(x-3.0);
    return m;
}
