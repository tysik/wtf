#ifndef CTF_VECTORS_H_
#define CTF_VECTORS_H_

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))

// 3D cartesian vector
typedef struct PACKED Vect {
    double x, y, z;
    bool is_normalized;
} Vect;

#undef PACKED

// Construct an empty vector (0, 0, 0)
Vect vempty();

// Get a negated version of a vector
Vect vneg(const Vect* v);

// Get a normalized version of a vector
Vect vnormal(const Vect* v);

// Get a scaled version of a vector
Vect vscale(double k, const Vect* v);

// Add two vectors
Vect vadd(const Vect* v1, const Vect* v2);

// Subtract two vectors
Vect vsub(const Vect* v1, const Vect* v2);

// Get a cross product of two vectors
Vect vcross(const Vect* v1, const Vect* v2);

// Get a dot product of two vectors
double vdot(const Vect* v1, const Vect* v2);

// Get a norm of a vector
double vnorm(const Vect* v);

// Get a squared norm of a vector
double vnormSquared(const Vect* v);

// Compare two vectors by coordinates
bool vcmp(const Vect* v1, const Vect* v2);

// Print a vector to stdout
void vprint(const Vect* v);

#endif // CTF_VECTORS_H_