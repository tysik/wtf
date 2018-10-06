#ifndef CTF_QUATERNIONS_H_
#define CTF_QUATERNIONS_H_

#include "Vectors.h"

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))
#define MUST_USE __attribute__ ((warn_unused_result))

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

// Construct an empty quaternion (0, 0, 0, 0)
void qempty(Quat* q);

// Construct a pure quaternion from vector (0, x, y, z)
void qpure(Quat* q, const Vect* v);

// Construct real quaternion from number (s, 0, 0, 0)
void qreal(Quat* q, double s);

// Construct a rotor about an axis
// Theta must be given in radians
// Axis must be normalized
void qrotor(Quat* q, double theta, const Vect* axis);

// Conjugate a quaternion
void qconjugate(Quat* q);

// Scale a quaternion by a scalar
void qscale(Quat* q, double k);

// Normalize a quaternion
// Returns:
//  1 if the quaternion was already normalized
//  0 if the normalization was OK
// -1 in case of failure
int MUST_USE qnormalize(Quat* q);

// Inverse a quaternion
// Returns:
//  0 if the inversion was OK
// -1 in case of failure
int MUST_USE qinverse(Quat* q);

// Add quaternion q2 to quaternion q1
void qadd(Quat* q1, const Quat* q2);

// Subtract quaternion q2 from quaternion q1
void qsub(Quat* q1, const Quat* q2);

// Multiply two quaternions
void qmul(Quat* q, const Quat* q1, const Quat* q2);

// Divide two quaternions
// Returns:
//  0 if the division was OK
// -1 in case of failure
int MUST_USE qdiv(Quat* q, const Quat* q1, const Quat* q2);

// Rotate a vector about a quaternion
// Q must be a proper (normalized) rotor 
void qrotate(Vect* v, const Quat* q);

// Get the norm of a quaternion
double MUST_USE qnorm(const Quat* q);

// Get a squared norm of a quaternion
double MUST_USE qnormSquared(const Quat* q);

// Check if a quaternion is pure
bool MUST_USE qisPure(const Quat* q);

// Check if a quaternion is real
bool MUST_USE qisReal(const Quat* q);

// Compare two quaternions by components
bool MUST_USE qcmp(const Quat* q1, const Quat* q2);

// Printf a quaterniong to stdout
void qprint(const Quat* q);

#undef PACKED
#undef MUST_USE

#endif // CTF_QUATERNIONS_H_