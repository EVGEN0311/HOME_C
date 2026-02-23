#include <stdio.h>
#include <math.h>
#include "methods.h"
#include "tests.h"

static double t_line(double x) { return x; }
static double t_zero(double x) { (void)x; return 0.0; }
static double t_square(double x) { return x * x; }
static double t_one(double x) { (void)x; return 1.0; }

int run_root_tests(void) {
    int ok = 1;
    double r;
    double eps = 1e-7;

    printf("== Тесты root ==\n");

    r = root(t_line, t_zero, -1.0, 1.0, eps);
    if (isnan(r) || fabs(r) > 1e-5) {
        printf("FAIL: root(x,0) expected 0, got %.10f\n", r);
        ok = 0;
    } else {
        printf("PASS: root(x,0) = %.10f\n", r);
    }

    r = root(t_square, t_one, 0.0, 2.0, eps);
    if (isnan(r) || fabs(r - 1.0) > 1e-5) {
        printf("FAIL: root(x^2,1) expected 1, got %.10f\n", r);
        ok = 0;
    } else {
        printf("PASS: root(x^2,1) = %.10f\n", r);
    }

    return ok;
}

int run_integral_tests(void) {
    int ok = 1;
    double I;
    double eps = 1e-7;

    printf("== Тесты integral ==\n");

    I = integral(t_line, 0.0, 1.0, eps);
    if (fabs(I - 0.5) > 1e-5) {
        printf("FAIL: integral(x,0,1) expected 0.5, got %.10f\n", I);
        ok = 0;
    } else {
        printf("PASS: integral(x,0,1) = %.10f\n", I);
    }

    I = integral(t_square, 0.0, 1.0, eps);
    if (fabs(I - 1.0 / 3.0) > 1e-5) {
        printf("FAIL: integral(x^2,0,1) expected %.10f, got %.10f\n", 1.0 / 3.0, I);
        ok = 0;
    } else {
        printf("PASS: integral(x^2,0,1) = %.10f\n", I);
    }

    return ok;
}