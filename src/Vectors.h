#ifndef VECTORS_H_
#define VECTORS_H_

#include <stdbool.h>

// 3D cartesian vector
typedef struct Vect {
    double x, y, z;
} Vect;

// Construct an empty vector (0, 0, 0)
Vect vempty();

// Negate a vector
// TODO add tests
Vect vneg(const Vect* v);

// Add two vectors
Vect vadd(const Vect* v1, const Vect* v2);

// Subtract two vectors
Vect vsub(const Vect* v1, const Vect* v2);

// Get a dot product of two vectors
double vdot(const Vect* v1, const Vect* v2);

// Get a cross product of two vectors
Vect vcross(const Vect* v1, const Vect* v2);

// Scale a vector by a scalar
Vect vscale(double k, const Vect* v);

// Compare two vectors by coordinates
bool vcmp(const Vect* v1, const Vect* v2);

// Get a norm of a vector
double vnorm(const Vect* v);

// Get a squared norm of a vector
double vnormSquared(const Vect* v);

#endif // VECTORS_H_