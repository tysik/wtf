#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <math.h>

bool dcmp(double a, double b) {
    static const double Precision = 1.0e-9;
    return fabs(a - b) < Precision;
}

#endif // MATH_UTILS_H_