#ifndef QUATERNIONS_H_
#define QUATERNIONS_H_

#include "Vectors.h"

#include <stdbool.h>

// Quaternion can be used either by components w, i, j, and k
// or by scale s and vector v form
typedef union Quat {
    struct {
        double w, i, j, k;
    };
    struct {
        double s;
        Vect v;
    };
} Quat;

// TODO: Consider using ResultQuat
// typedef struct ResultQuat {
//     bool ok;
//     Quat q;
// } ResultQuat;

// Construct an empty quaternion (1, 0, 0, 0)
Quat qempty();

// Get the real part from a quaternion
Quat qreal(const Quat* q);

// Get the imaginary part of a quaternion
Quat qpure(const Quat* q);

// Get the conjugate of a quaternion
Quat qconj(const Quat* q);

// Add two quaternions
Quat qadd(const Quat* q1, const Quat* q2);

// Subtract two quaternions
Quat qsub(const Quat* q1, const Quat* q2);

// Multiply two quaternions
Quat qmul(const Quat* q1, const Quat* q2);

// Divide quaternion q1 by quaternion q2
Quat qdiv(const Quat* q1, const Quat* q2);

// Scale a quaternion by a scalar
Quat qscale(double k, const Quat* q);

// Compare two quaternions by components
bool qcmp(const Quat* q1, const Quat* q2);

// Get the norm of a quaternion
double qnorm(const Quat* q);

// Get a squared norm of a quaternion
double qnormSquared(const Quat* q);

#endif // QUATERNIONS_H_