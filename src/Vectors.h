#ifndef VECTORS_H_
#define VECTORS_H_

#include <stdbool.h>

typedef struct Vect { double x, y, z; } Vect;

Vect vEmpty();
Vect vFrom(double x, double y, double z);

Vect vadd(const Vect* v1, const Vect* v2);
Vect vsub(const Vect* v1, const Vect* v2);

double vdot(const Vect* v1, const Vect* v2);
Vect vcross(const Vect* v1, const Vect* v2);

Vect vscale(double k, const Vect* v);

bool vcmp(const Vect* v1, const Vect* v2);

double vnorm(const Vect* v);
double vnormSquared(const Vect* v);

#endif // VECTORS_H_