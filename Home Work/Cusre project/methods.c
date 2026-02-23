#include <math.h>
#include "methods.h"

static int g_root_iterations = 0;

static double diff(func_t f, func_t g, double x) {
    return f(x) - g(x);
}

int root_last_iterations(void) {
    return g_root_iterations;
}

double root(func_t f, func_t g, double a, double b, double eps) {
    double fa, fb, m, fm;

    g_root_iterations = 0;

    fa = diff(f, g, a);
    fb = diff(f, g, b);

    if (fabs(fa) < eps) return a;
    if (fabs(fb) < eps) return b;

    if (fa * fb > 0.0) return NAN;

    while ((b - a) > eps) {
        m = (a + b) / 2.0;
        fm = diff(f, g, m);
        g_root_iterations++;

        if (fabs(fm) < eps) return m;

        if (fa * fm <= 0.0) {
            b = m;
            fb = fm;
        } else {
            a = m;
            fa = fm;
        }
    }

    return (a + b) / 2.0;
}

static double simpson(func_t f, double a, double b, int n) {
    int i;
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) sum += 2.0 * f(x);
        else sum += 4.0 * f(x);
    }

    return sum * h / 3.0;
}

double integral(func_t f, double a, double b, double eps) {
    int n = 2;
    double s_prev = simpson(f, a, b, n);
    double s_curr;

    while (1) {
        n *= 2;
        s_curr = simpson(f, a, b, n);

        if (fabs(s_curr - s_prev) / 15.0 < eps) return s_curr;

        s_prev = s_curr;

        if (n > (1 << 24)) break;
    }

    return s_prev;
}