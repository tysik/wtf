#ifndef WTF_QUATERNION_H_
#define WTF_QUATERNION_H_

#include "MacroUtils.h"
#include "QuaternionImpl.h"
#include "TypesFwd.h"

// Constructors:
//

// Construct an empty quaternion (0, 0, 0, 0)
wtf_quat_t wtf_quat_empty();

// Construct a pure quaternion from vector (0, x, y, z)
#define wtf_quat_pure(v) WTF_ONE_VEC_ARG_QUAT_FUNC(pure, v)

// Construct a real quaternion from scalar (s, 0, 0, 0)
wtf_quat_t wtf_quat_real(wtf_scalar_t s);

// Construct a rotor about an axis
// Axis must be a normalized vector.
// Angle must be given in radians.
#define wtf_quat_rotor(axis, angle) WTF_TWO_VEC_ARG_QUAT_FUNC(rotor, axis, angle)

// TODO: Add SLERP https://en.wikipedia.org/wiki/Slerp

// Variations:
//

// Get a conjugate of a quaternion
#define wtf_quat_conjugate(q) WTF_ONE_ARG_QUAT_FUNC(conjugate, q)

// Get a scaled quaternion
#define wtf_quat_scaled(q, s) WTF_TWO_ARGS_QUAT_FUNC(scaled, q, s)

// Get a normalized quaternion
// The quaternion length must be greater than 0.
#define wtf_quat_normalized(q) WTF_ONE_ARG_QUAT_FUNC(normalized, q)

// Get an inverse of a quaternion
// The quaternion length must be greater than 0.
#define wtf_quat_inversed(q) WTF_ONE_ARG_QUAT_FUNC(inversed, q)

// Operations:
//

// Add quaternions q1 and q2
#define wtf_quat_add(q1, q2) WTF_TWO_ARGS_QUAT_FUNC(add, q1, q2)

// Subtract quaternion q2 from quaternion q1
#define wtf_quat_subtract(q1, q2) WTF_TWO_ARGS_QUAT_FUNC(subtract, q1, q2)

// Multiply quaternion q1 times q2
#define wtf_quat_multiply(q1, q2) WTF_TWO_ARGS_QUAT_FUNC(multiply, q1, q2)

// Divide quaternion q1 by q2
// The quaternion q2 length must be greater than 0.
#define wtf_quat_divide(q1, q2) WTF_TWO_ARGS_QUAT_FUNC(divide, q1, q2)

// Methods:
//

// Rotate a vector about a quaternion
// Quaternion q must be a proper (normalized) rotor
#define wtf_quat_rotate(q, v) WTF_TWO_ARGS_QUAT_FUNC(rotate, q, v)

// Traits:
//

// Get a norm of a quaternion
#define wtf_quat_norm(q) WTF_ONE_ARG_QUAT_FUNC(norm, q)

// Get a squared norm of a quaternion
#define wtf_quat_squared_norm(q) WTF_ONE_ARG_QUAT_FUNC(squared_norm, q)

// Check if quaternion is normalized
#define wtf_quat_is_normalized(q) WTF_ONE_ARG_QUAT_FUNC(is_normalized, q)

// Check if a quaternion is pure
#define wtf_quat_is_pure(q) WTF_ONE_ARG_QUAT_FUNC(is_pure, q)

// Check if a quaternion is real
#define wtf_quat_is_real(q) WTF_ONE_ARG_QUAT_FUNC(is_real, q)

// Auxiliary:
//

// Compare two quaternions by components
#define wtf_quat_compare(q1, q2) WTF_TWO_ARGS_QUAT_FUNC(compare, q1, q2)

// Printf a quaternion to stdout
#define wtf_quat_print(q) WTF_ONE_ARG_QUAT_FUNC(print, q)

#endif // WTF_QUATERNION_H_