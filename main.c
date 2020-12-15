#include <stdio.h>
#include <math.h>
#include "functionBib.h"
#define MAX_ITERATIONS 100

int main(int argc, char const *argv[])
{
    int choice;

    //User interface
    printf("Newton-Raphson-Calculator \n \n");
    printf("Function    :   f(x)=(x-3)^2 \n");
    printf("(1) Analytic:   fs(x)=2*(x-3) \n");
    printf("(2) Numeric :   (f(x+h)-f(x))/h \n");
    printf("Do you want to test the analytic or numeric option?: \n");
    scanf("%d", &choice);
    
    //getting x
    double x;
    printf("Which x do you want to work with: \n");
    scanf("%lf", &x);

    int count;
    double x2;

    //while loop with limiter
    while (count<=MAX_ITERATIONS)
    {
        //function for filtering out x2
        if (choice==1)
        {
            x2 = x - function(x)/functionDeri(x);
        } else
        {
            x2 = x - function(x)/functionNumDiff(x);
        }
        
    
        printf("%.10lf  ", x2);
        printf("%.10lf \n", x);

        //ending of while loop
        if (fabs(x2 - x)<pow(10, -10) || count==MAX_ITERATIONS)
        {
            printf("Result: %lf \n", x2);
            printf("Number of iterations: %d\n", count);
            return 0;
        } else
        {
            //setting x=x2 to get a more accurate result
            x=x2;
            count++;
        }
    }
    return 0;
}

