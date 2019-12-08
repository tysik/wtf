#ifndef WTF_QUATERNION_H_
#define WTF_QUATERNION_H_

#include "types/ScalarType.h"

#include <stdbool.h>

#define MUST_USE __attribute__((warn_unused_result))

// Forward declarations:
//

typedef union wtf_vec_t wtf_vec_t;
typedef union wtf_quat_t wtf_quat_t;

// Constructors:
//

// Construct an empty quaternion (0, 0, 0, 0)
wtf_quat_t wtf_quat_empty();

// Construct a pure quaternion from vector (0, x, y, z)
wtf_quat_t wtf_quat_pure(const wtf_vec_t* v);

// Construct a real quaternion from scalar (s, 0, 0, 0)
wtf_quat_t wtf_quat_real(wtf_scalar_t s);

// Construct a rotor about an axis
// Axis must be a normalized vector.
// Angle must be given in radians.
wtf_quat_t wtf_quat_rotor(const wtf_vec_t* axis, wtf_scalar_t angle);

// TODO: Add SLERP https://en.wikipedia.org/wiki/Slerp

// Variations:
//

// Get a conjugate of a quaternion
wtf_quat_t wtf_quat_conjugate(const wtf_quat_t* q);

// Get a scaled quaternion
wtf_quat_t wtf_quat_scaled(const wtf_quat_t* q, wtf_scalar_t k);

// Get a normalized quaternion
// The quaternion length must be greater than 0.
wtf_quat_t wtf_quat_normalized(const wtf_quat_t* q);

// Get an inverse of a quaternion
// The quaternion length must be greater than 0.
wtf_quat_t wtf_quat_inversed(const wtf_quat_t* q);

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
wtf_scalar_t wtf_quat_norm(const wtf_quat_t* q);

// Get a squared norm of a quaternion
wtf_scalar_t wtf_quat_squared_norm(const wtf_quat_t* q);

// Check if quaternion is normalized
bool wtf_quat_is_normalized(const wtf_quat_t* q);

// Check if a quaternion is pure
bool wtf_quat_is_pure(const wtf_quat_t* q);

// Check if a quaternion is real
bool wtf_quat_is_real(const wtf_quat_t* q);

// Auxiliary:
//

// Compare two quaternions by components
bool MUST_USE wtf_quat_compare(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Printf a quaternion to stdout
void wtf_quat_print(const wtf_quat_t* q);

#undef MUST_USE

#endif // WTF_QUATERNION_H_