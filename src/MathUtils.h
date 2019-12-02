#ifndef WTF_MATH_UTILS_H_
#define WTF_MATH_UTILS_H_

#include <stdarg.h>
#include <stdbool.h>

// Get the largest value from the arguments
double wtf_dmax(int num_args, ...);

// Compare a and b for equality with limited precission
// Returns true if a is approx. equal to b
bool wtf_dcmp(double a, double b);

#endif // WTF_MATH_UTILS_H_