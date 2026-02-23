#ifndef METHODS_H
#define METHODS_H

#include "functions.h"

double root(func_t f, func_t g, double a, double b, double eps);
double integral(func_t f, double a, double b, double eps);
int root_last_iterations(void);

#endif
