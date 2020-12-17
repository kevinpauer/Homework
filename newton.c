#include <stdio.h>
#include <math.h>

double newton(double count, double MAX_ITERATIONS, double x, double (*func)(double), double (*funcDeri)(double)){
    double x2;
    while (count<=MAX_ITERATIONS)
    {
        //filtering out x2 with the help of funciton pointers
        x2 = x - func(x)/funcDeri(x);

        printf("%.10lf  ", x);
        printf("%.10lf \n", x2);

        //ending of while loop
        if (fabs(x2 - x)<pow(10, -10) || count==MAX_ITERATIONS)
        {
            printf("Number of iterations: %.2lf\n", count);
            break;
        } else
        {
            //setting x=x2 to get a more accurate result
            x=x2;
            count++;
        }
    }
    return x2;
}