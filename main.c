#include <stdio.h>
#include <math.h>
#include "functionBib.h"
#include "newton.c"
#define MAX_ITERATIONS 100

int main()
{
    int choice;
    double result;

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

    double count;

    double (*funcP)(double);
    funcP = &function;

    double (*deriP)(double);
    deriP = &functionDeri;

    double (*numDeriP)(double);
    numDeriP=&functionNumDiff;

    if (choice==1)
    {
        result = newton(count, MAX_ITERATIONS, x, funcP, deriP);
    } else if (choice==2)
    {
        result = newton(count, MAX_ITERATIONS, x, funcP, numDeriP);
    } else
    {
        printf("Choice not valid, please try again! \n");
        return 0;
    }

    printf("Result: %lf\n", result);
    printf("Number of iterations: %lf\n", count);
    
    return 0;
}

