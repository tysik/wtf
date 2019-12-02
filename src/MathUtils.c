#include "MathUtils.h"

#include <math.h>
#include <stdio.h>

double wtf_dmax(int num_args, ...) {
    // Based on http://publications.gbdirect.co.uk/c_book/chapter9/stdarg.html
    va_list args;
    va_start(args, num_args);

    double max = va_arg(args, double);
    for (int i = 1; i < num_args; ++i) {
        double a = va_arg(args, double);
        if (a > max) {
            max = a;
        }
    }

    va_end(args);
    return max;
}

bool wtf_dcmp(double a, double b) {
    // Based on http://realtimecollisiondetection.net/blog/?p=89
    static const double Precision = 1.0e-7;
    return fabs(a - b) < Precision * wtf_dmax(3, 1.0, fabs(a), fabs(b));
}