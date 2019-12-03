#ifndef WTF_QUATERNION_H_
#define WTF_QUATERNION_H_

#include "Vector.h"

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))
#define MUST_USE __attribute__((warn_unused_result))

// Quaternion
typedef union wtf_quat_t {
    struct PACKED {
        double w, i, j, k;
    };
    struct PACKED {
        double s;
        wtf_vec_t v;
    };
    double array[4];
} wtf_quat_t;

// Constructors:
//

// Construct an empty quaternion (0, 0, 0, 0)
wtf_quat_t wtf_empty_quat();

// Construct a pure quaternion from vector (0, x, y, z)
wtf_quat_t wtf_pure_quat(const wtf_vec_t* v);

// Construct a real quaternion from number (s, 0, 0, 0)
wtf_quat_t wtf_real_quat(double s);

// Construct a rotor about an axis
// - theta must be given in radians
// - axis must be a normalized vector
wtf_quat_t wtf_rotor_quat(double theta, const wtf_vec_t* axis);

// Variations:
//

// Get a conjugate of a quaternion
wtf_quat_t wtf_quat_conjugate(const wtf_quat_t* q);

// Get a scaled quaternion
wtf_quat_t wtf_quat_scaled(const wtf_quat_t* q, double k);

// Get a normalized quaternion
// The quaternion length must be greater than 0.
wtf_quat_t wtf_quat_normalized(const wtf_quat_t* q);

// Get an inverse of a quaternion
// The quaternion length must be greater than 0.
wtf_quat_t wtf_quat_inversed(const wtf_quat_t* q);

// TODO: Add LERP

// Operations:
//

// Add quaternions q1 and q2
wtf_quat_t wtf_quat_add(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Subtract quaternion q2 from quaternion q1
wtf_quat_t wtf_quat_subtract(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Multiply quaternion q1 times q2
wtf_quat_t wtf_quat_multiply(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Divide quaternion q1 by q2
// The quaternion q2 length must be greater than 0.
wtf_quat_t wtf_quat_divide(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Methods:
//

// Rotate a vector about a quaternion
// Quaternion q must be a proper (normalized) rotor
wtf_vec_t wtf_quat_rotate(const wtf_quat_t* q, const wtf_vec_t* v);

// Traits:
//

// Get a norm of a quaternion
double wtf_quat_norm(const wtf_quat_t* q);

// Get a squared norm of a quaternion
double wtf_quat_squared_norm(const wtf_quat_t* q);

// Check if quaternion is normalized
bool wtf_quat_is_normalized(const wtf_quat_t* q);

// Check if a quaternion is pure
bool wtf_quat_is_pure(const wtf_quat_t* q);

// Check if a quaternion is real
bool wtf_quat_is_real(const wtf_quat_t* q);

// Auxiliary:
//

// Compare two quaternions by components
bool MUST_USE wtf_compare_quat(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Printf a quaterniong to stdout
void wtf_print_quat(const wtf_quat_t* q);

#undef PACKED
#undef MUST_USE

#endif // WTF_QUATERNION_H_