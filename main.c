#include <stdio.h>
#include "functionBib.h"
#include "numericDeri.h"
#include <math.h>
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
    printf("(2) Numeric :   fs(x)=(f(x+h)-f(x))/h \n");
    printf("Do you want to test the analytic or numeric option?: \n");
    scanf("%d", &choice);
    
    //getting x from user
    double x;
    printf("Which x do you want to work with: \n");
    scanf("%lf", &x);

    //setting the pointer for functions
    double (*funcP)(double);
    funcP = &function;

    double (*analyticDeriP)(double);
    analyticDeriP = &functionAnalyticDeri;
    
    double (*numDeriP)(double (*)(double), double);
    numDeriP=&functionNumericDeri;

    //using the specified case
    if (choice==1)
    {
        result = newtonAnalytic(MAX_ITERATIONS, x, funcP, analyticDeriP);
    } else if (choice==2)
    {
        result = newtonNumeric(MAX_ITERATIONS, x, funcP, numDeriP);
    } else
    {
        printf("Choice not valid, please try again! \n");
        return 0;
    }

    printf("Result: %.8lf\n", result);

    return 0;
}

