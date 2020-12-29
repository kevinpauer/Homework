#ifndef NEWTON_H_
#define NEWTON_H_

double newtonAnalytic(double, double x, double (*)(double), double (*)(double));
double newtonNumeric(double , double x, double (*)(double), double (*)(double(*)(double),double));

#endif