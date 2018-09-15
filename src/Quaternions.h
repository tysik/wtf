#ifndef QUATERNIONS_H_
#define QUATERNIONS_H_

#include "Vectors.h"

#include <stdbool.h>

// Quaternion can be used either by components w, i, j, k
// or by scalar s and vector v. In the latter case field 
// is_normalized of v denotes normalized (unit) quaternion.
typedef union Quat {
    struct {
        double w, i, j, k;
        bool is_normalized;
    } PACKED;
    struct {
        double s;
        Vect v;
    } PACKED;
} Quat;

// Construct an empty quaternion (0, 0, 0, 0)
Quat qempty();

// Get the conjugate version of a quaternion
Quat qconj(const Quat* q);

// Get the unit version of a quaternion
// TODO Add test
Quat qunit(const Quat* q);

// Get the inverse of a quaternion
// TODO Add test
Quat qinv(const Quat* q);

// Scale a quaternion by a scalar
Quat qscale(double k, const Quat* q);

// Add two quaternions
Quat qadd(const Quat* q1, const Quat* q2);

// Subtract two quaternions
Quat qsub(const Quat* q1, const Quat* q2);

// Multiply two quaternions
Quat qmul(const Quat* q1, const Quat* q2);

// Divide two quaternions
// TODO Add test
Quat qdiv(const Quat* q1, const Quat* q2);

// Get the imaginary part of a quaternion
Vect qpure(const Quat* q);

// Get the real part of a quaternion
double qreal(const Quat* q);

// Get the norm of a quaternion
double qnorm(const Quat* q);

// Get a squared norm of a quaternion
double qnormSquared(const Quat* q);

// Compare two quaternions by components
bool qcmp(const Quat* q1, const Quat* q2);

#endif // QUATERNIONS_H_