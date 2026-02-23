#include <stdio.h>
#include <string.h>
#include <math.h>
#include "functions.h"
#include "methods.h"
#include "tests.h"

static const double EPS_ROOT = 1e-7;
static const double EPS_INT = 1e-7;

static void print_help(const char *prog) {
    printf("Использование: %s [КЛЮЧИ]\n", prog);
    printf("Ключи:\n");
    printf("  --help           Показать справку\n");
    printf("  --points         Печатать абсциссы точек пересечения\n");
    printf("  --iters          Печатать число итераций root()\n");
    printf("  --test-root      Тесты root()\n");
    printf("  --test-integral  Тесты integral()\n");
}

static double f1_minus_f3(double x) { return f1(x) - f3(x); }
static double f1_minus_f2(double x) { return f1(x) - f2(x); }

int main(int argc, char *argv[]) {
    int i;
    int show_points = 0;
    int show_iters = 0;
    int do_test_root = 0;
    int do_test_integral = 0;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--points") == 0) {
            show_points = 1;
        } else if (strcmp(argv[i], "--iters") == 0) {
            show_iters = 1;
        } else if (strcmp(argv[i], "--test-root") == 0) {
            do_test_root = 1;
        } else if (strcmp(argv[i], "--test-integral") == 0) {
            do_test_integral = 1;
        } else {
            printf("Неизвестный ключ: %s\n", argv[i]);
            printf("Используйте --help\n");
            return 1;
        }
    }

    if (do_test_root || do_test_integral) {
        int ok = 1;
        if (do_test_root && !run_root_tests()) ok = 0;
        if (do_test_integral && !run_integral_tests()) ok = 0;
        return ok ? 0 : 1;
    }

    double x13, x23, x12;
    double S1, S2, S;

    x13 = root(f1, f3, 0.5, 1.5, EPS_ROOT);
    if (show_iters) printf("Итерации для x13 (f1=f3): %d\n", root_last_iterations());

    x23 = root(f2, f3, 3.0, 3.5, EPS_ROOT);
    if (show_iters) printf("Итерации для x23 (f2=f3): %d\n", root_last_iterations());

    x12 = root(f1, f2, 3.5, 4.5, EPS_ROOT);
    if (show_iters) printf("Итерации для x12 (f1=f2): %d\n", root_last_iterations());

    if (isnan(x13) || isnan(x23) || isnan(x12)) {
        printf("Ошибка поиска точек пересечения\n");
        return 1;
    }

    if (show_points) {
        printf("x13 = %.10f\n", x13);
        printf("x23 = %.10f\n", x23);
        printf("x12 = %.10f\n", x12);
    }

    S1 = integral(f1_minus_f3, x13, x23, EPS_INT);
    S2 = integral(f1_minus_f2, x23, x12, EPS_INT);
    S = S1 + S2;

    printf("Площадь фигуры = %.10f\n", S);

    return 0;
}