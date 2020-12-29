#include <stdio.h>
#include <math.h>

double newtonAnalytic(double MAX_ITERATIONS, double x, double (*func)(double), double (*funcDeri)(double)){
    double count;
    double holder;
    while (count<=MAX_ITERATIONS)
    {
        //filtering out holder with the help of funciton pointers
        holder = x - func(x)/funcDeri(x);

        //check if x is already root
        if (isnan(holder))
        {
            return x;
        }

        printf("%.10lf ", x);
        printf("%.10lf iteration: %.2lf \n", holder, count+1);

        //ending of while loop
        if (fabs(holder - x)<pow(10, -10) || count==MAX_ITERATIONS)
        {
            printf("Number of iterations: %.2lf\n", count+1);
            break;
        } else
        {
            //setting x=holder to get a more accurate result
            x=holder;
            count++;
        }
    }
    return holder;
}

double newtonNumeric(double MAX_ITERATIONS, double x, double (*func)(double), double (*funcDeri)(double(*function)(double),double)){
    double count;
    double holder;
    
    while (count<=MAX_ITERATIONS)
    {
        //filtering out x2 with the help of funciton pointers
        holder = x - func(x)/funcDeri(func,x);

        //check if x is already root
        if (isnan(holder))
        {
            return x;
        }

        printf("%.10lf ", x);
        printf("%.10lf iteration: %.2lf \n", holder, count+1);

        //ending of while loop
        if (fabs(holder - x)<pow(10, -10) || count==MAX_ITERATIONS)
        {
            printf("Number of iterations: %.2lf\n", count+1);
            break;
        } else
        {
            //setting x=holder to get a more accurate result
            x=holder;
            count++;
        }
    }
    return holder;
}