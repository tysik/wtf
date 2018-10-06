#ifndef CTF_VECTORS_H_
#define CTF_VECTORS_H_

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))
#define MUST_USE __attribute__((warn_unused_result))

// 3D cartesian vector
typedef struct PACKED Vect {
    double x, y, z;
    bool is_normalized;
} Vect;

// Construct an empty vector (0, 0, 0)
void vempty(Vect* v);

// Construct an X axis versor (1, 0, 0)
void vversorX(Vect* v);

// Construct a Y axis versor (0, 1, 0)
void vversorY(Vect* v);

// Construct a Z axis versor (0, 0, 1)
void vversorZ(Vect* v);

// Construct a vector from array of 3 doubles
void vfromArray(Vect* v, double (*a)[3]);

// Negate a vector
void vnegate(Vect* v);

// Scale a vector by a scalar
void vscale(Vect* v, double k);

// Normalize a vector
// Returns:
//  1 if the vector was already normalized
//  0 if the normalization was OK
// -1 in case of failure
int MUST_USE vnormalize(Vect* v);

// Add vector v2 to vector v1
void vadd(Vect* v1, const Vect* v2);

// Subtract vector v2 from vector v1
void vsub(Vect* v1, const Vect* v2);

// Get a cross product of two vectors: v1 x v2
void vcross(Vect* v, const Vect* v1, const Vect* v2);

// Get a dot product of two vectors: v1 * v2
double MUST_USE vdot(const Vect* v1, const Vect* v2);

// Get a norm of a vector
double MUST_USE vnorm(const Vect* v);

// Get a squared norm of a vector
double MUST_USE vnormSquared(const Vect* v);

// Compare two vectors by coordinates
bool MUST_USE vcmp(const Vect* v1, const Vect* v2);

// Print a vector to stdout
void vprint(const Vect* v);

#undef PACKED
#undef MUST_USE

#endif // CTF_VECTORS_H_