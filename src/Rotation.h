#ifndef WTF_ROTATION_H_
#define WTF_ROTATION_H_

#include "types/QuaternionType.h"
#include "types/RotationType.h"
#include "types/ScalarType.h"
#include "types/VectorType.h"

#include <stdbool.h>

#define MUST_USE __attribute__((warn_unused_result))

// Constructors:
//

// Construct a rotation matrix about X axis
// Angle must be given in radians.
wtf_rot_t wtf_rot_x(wtf_scalar_t angle);

// Construct a rotation matrix about Y axis
// Angle must be given in radians.
wtf_rot_t wtf_rot_y(wtf_scalar_t angle);

// Construct a rotation matrix about Y axis
// Angle must be given in radians.
wtf_rot_t wtf_rot_z(wtf_scalar_t angle);

wtf_rot_t wtf_rot_extrinsic_rpy(wtf_scalar_t roll, wtf_scalar_t pitch, wtf_scalar_t yaw);
wtf_rot_t wtf_rot_intrinsic_rpy(wtf_scalar_t roll, wtf_scalar_t pitch, wtf_scalar_t yaw);

// Construct a rotation matrix about custom axis
// Axis must be a normalized vector.
// Angle must be given in radians.
wtf_rot_t wtf_from_axis_angle(wtf_vec_t axis, wtf_scalar_t angle);

// // Construct rotation matrix from a quaternion
// // Q must be a proper (normalized) rotor
// void rfromQuat(wtf_rot_t* r, const wtf_quat_t* q);

// void rtoQuat(wtf_quat_t* q, const wtf_rot_t* r);

// // Scale a matrix by a scalar
// void rscale(wtf_rot_t* r, double k);

// Methods:
//

// Rotate a vector with a rotation matrix
wtf_vec_t wtf_rot_rotate(const wtf_rot_t* r, const wtf_vec_t* v);

// Traits:
//

// Get norms of each rotation matrix row
wtf_vec_t wtf_rot_norms(const wtf_rot_t* r);

// Check if matrix is orthogonal
bool wtf_rot_is_orthogonal(const wtf_rot_t* r);

// Auxiliary:
//

// Compare two rotation matrices by components
bool MUST_USE wtf_compare_rot(const wtf_rot_t* r1, const wtf_rot_t* r2);

// Print a rotation matrix to stdout
void wtf_print_rot(const wtf_rot_t* r);

#undef MUST_USE

#endif // WTF_ROTATION_H_