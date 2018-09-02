#include "MathUtils.h"

bool dcmp(double a, double b) {
    static const double Precision = 1.0e-5;
    return fabs(a - b) <= Precision * dmax(1.0, fabs(a), fabs(b));
}

double dmax(double n_args, ...) {
    register int i;
    double max, a;
    va_list ap;

    va_start(ap, n_args);
    max = va_arg(ap, double);
    for (i = 2; i <= n_args; i++) {
        if ((a = va_arg(ap, double)) > max)
            max = a;
    }

    va_end(ap);
    return max;
}