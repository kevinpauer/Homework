#include <stdio.h>
#include "functionBib.h"
#include "numericDeri.h"
#include <math.h>
#define MAX_ITERATIONS 100

double newtonAnalytic(double x, double (*func)(double), double (*funcDeri)(double)){
    double count;
    double x2;
    while (count<=MAX_ITERATIONS)
    {
        //filtering out x2 with the help of funciton pointers
        x2 = x - func(x)/funcDeri(x);

        printf("%.10lf ", x);
        printf("%.10lf iteration: %.2lf \n", x2, count+1);

        //ending of while loop
        if (fabs(x2 - x)<pow(10, -10) || count==MAX_ITERATIONS)
        {
            printf("Number of iterations: %.2lf\n", count+1);
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

double newtonNumeric(double x, double (*func)(double), double (*funcDeri)(double(*function)(double),double)){
    double count;
    double x2;
    while (count<=MAX_ITERATIONS)
    {
        //filtering out x2 with the help of funciton pointers
        x2 = x - func(x)/funcDeri(func,x);

        printf("%.10lf ", x);
        printf("%.10lf iteration: %.2lf \n", x2, count+1);

        //ending of while loop
        if (fabs(x2 - x)<pow(10, -10) || count==MAX_ITERATIONS)
        {
            printf("Number of iterations: %.2lf\n", count+1);
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

    double (*numDeriP)(double(*)(double),double);
    numDeriP=&functionNumericDeri(function(x));

    //using the specified case
    if (choice==1)
    {
        result = newtonAnalytic(x, funcP, analyticDeriP);
    } else if (choice==2)
    {
        result = newtonNumeric(x, funcP, numDeriP);
    } else
    {
        printf("Choice not valid, please try again! \n");
        return 0;
    }

    printf("Result: %.8lf\n", result);

    return 0;
}

