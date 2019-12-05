#ifndef WTF_QUATERNION_H_
#define WTF_QUATERNION_H_

#include "types/ScalarType.h"
#include "types/VectorType.h"
#include "types/QuaternionType.h"

#include <stdbool.h>

#define MUST_USE __attribute__((warn_unused_result))

// Constructors:
//

// Construct an empty quaternion (0, 0, 0, 0)
wtf_quat_t wtf_empty_quat();

// Construct a pure quaternion from vector (0, x, y, z)
wtf_quat_t wtf_pure_quat(const wtf_vec_t* v);

// Construct a real quaternion from scalar (s, 0, 0, 0)
wtf_quat_t wtf_real_quat(wtf_scalar_t s);

// Construct a rotor about an axis
// Axis must be a normalized vector.
// Angle must be given in radians.
wtf_quat_t wtf_rotor_quat(const wtf_vec_t* axis, wtf_scalar_t angle);

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
bool MUST_USE wtf_compare_quat(const wtf_quat_t* q1, const wtf_quat_t* q2);

// Printf a quaternion to stdout
void wtf_print_quat(const wtf_quat_t* q);

#undef MUST_USE

#endif // WTF_QUATERNION_H_