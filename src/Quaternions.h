#ifndef CTF_QUATERNIONS_H_
#define CTF_QUATERNIONS_H_

#include "Vectors.h"

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))

// Quaternion can be used either by components w, i, j, k
// or by scalar s and vector v. In the latter case field
// is_normalized of v denotes normalized (unit) quaternion.
typedef union Quat {
    struct PACKED {
        double w, i, j, k;
        bool is_normalized;
    };
    struct PACKED {
        double s;
        Vect v;
    };
} Quat;

#undef PACKED

// Construct an empty quaternion (0, 0, 0, 0)
Quat qempty();

// Get the conjugate version of a quaternion
Quat qconj(const Quat* q);

// Get the unit version of a quaternion
Quat qunit(const Quat* q);

// Get the inverse of a quaternion
Quat qinv(const Quat* q);

// Scale a quaternion by a scalar
Quat qscale(double k, const Quat* q);

// Construct a rotor about axis v
// theta must be in radians
Quat qrotor(double theta, const Vect* axis);

// Add two quaternions
Quat qadd(const Quat* q1, const Quat* q2);

// Subtract two quaternions
Quat qsub(const Quat* q1, const Quat* q2);

// Multiply two quaternions
Quat qmul(const Quat* q1, const Quat* q2);

// Divide two quaternions
Quat qdiv(const Quat* q1, const Quat* q2);

// Get the imaginary part of a quaternion
Vect qpure(const Quat* q);

// Rotate vector v with quaternion q
Vect qrotate(const Vect* v, const Quat* q);

// Get the real part of a quaternion
double qreal(const Quat* q);

// Get the norm of a quaternion
double qnorm(const Quat* q);

// Get a squared norm of a quaternion
double qnormSquared(const Quat* q);

// Compare two quaternions by components
bool qcmp(const Quat* q1, const Quat* q2);

// Printf a quaterniong to stdout
void qprint(const Quat* q);

#endif // CTF_QUATERNIONS_H_