#ifndef WTF_QUATERNION_H_
#define WTF_QUATERNION_H_

#include "Vectors.h"

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))
#define MUST_USE __attribute__((warn_unused_result))

// Quaternion type
typedef union wtf_quat_t {
    struct PACKED {
        double w, i, j, k;
    };
    struct PACKED {
        double s;
        Vect v;
    };
    double array[4];
} wtf_quat_t;

// Constructors:
//

// Construct an empty quaternion (0, 0, 0, 0)
wtf_quat_t wtf_empty_quat();

// Construct a pure quaternion from vector (0, x, y, z)
wtf_quat_t wtf_pure_quat(const Vect* v);

// Construct a real quaternion from number (s, 0, 0, 0)
wtf_quat_t wtf_real_quat(double s);

// Construct a rotor about an axis
// - theta must be given in radians
// - axis must be a normalized vector
wtf_quat_t wtf_rotor_quat(double theta, const Vect* axis);

// Variations:
//

// Get a conjugate of a quaternion
wtf_quat_t wtf_quat_conjugate(const wtf_quat_t* q);

// Get a scaled quaternion
wtf_quat_t wtf_quat_scaled(const wtf_quat_t* q, double k);

// Get a normalized quaternion
wtf_quat_t wtf_quat_normalized(const wtf_quat_t* q);

// Get an inverse of a quaternion
wtf_quat_t wtf_quat_inversed(const wtf_quat_t* q);

// Operations:
//

// Add quaternions q1 and q2
wtf_quat_t wtf_quat_add(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Subtract quaternion q2 from quaternion q1
wtf_quat_t wtf_quat_subtract(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Multiply two quaternions
wtf_quat_t wtf_quat_multiply(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Divide two quaternions
wtf_quat_t wtf_quat_divide(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Rotate a vector about a quaternion
// Q must be a proper (normalized) rotor
Vect wtf_quat_rotated(const Vect* v, const wtf_quat_t* q);


// Traits:
//

// Get the norm of a quaternion
double MUST_USE wtf_quat_norm(const wtf_quat_t* q);

// Get a squared norm of a quaternion
double MUST_USE wtf_quat_norm_squared(const wtf_quat_t* q);

// Check if a quaternion is pure
bool MUST_USE wtf_quat_is_pure(const wtf_quat_t* q);

// Check if a quaternion is real
bool MUST_USE wtf_quat_is_real(const wtf_quat_t* q);

// Auxiliary:
//

// Compare two quaternions by components
bool MUST_USE wtf_compare_quat(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Printf a quaterniong to stdout
void wtf_print_quat(const wtf_quat_t* q);

#undef PACKED
#undef MUST_USE

#endif // WTF_QUATERNION_H_