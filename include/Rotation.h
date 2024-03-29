#ifndef WTF_ROTATION_H_
#define WTF_ROTATION_H_

#include "types/ScalarType.h"

// Forward declarations:
//

typedef union wtf_vec_t wtf_vec_t;
typedef union wtf_quat_t wtf_quat_t;
typedef union wtf_mat_t wtf_mat_t;
typedef wtf_mat_t wtf_rot_t;

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

// Construct a rotation matrix from RPY angles in a local coordinate frame
// Angles roll, pitch and yaw must be given in radians.
wtf_rot_t wtf_rot_local_rpy(wtf_scalar_t roll, wtf_scalar_t pitch, wtf_scalar_t yaw);

// Construct a rotation matrix from RPY angles in a global coordinate frame
// Angles roll, pitch and yaw must be given in radians.
wtf_rot_t wtf_rot_global_rpy(wtf_scalar_t roll, wtf_scalar_t pitch, wtf_scalar_t yaw);

// Construct a rotation matrix about custom axis
// Axis must be a normalized vector.
// Angle must be given in radians.
wtf_rot_t wtf_rot_from_axis_angle(const wtf_vec_t* axis, wtf_scalar_t angle);

// Construct a rotation matrix from a quaternion
// Quaternion must be normalized.
// TODO: Test
wtf_rot_t wtf_rot_from_quaternion(const wtf_quat_t* q);

// Methods:
//

// Rotate a vector with a rotation matrix
wtf_vec_t wtf_rot_rotate(const wtf_rot_t* r, const wtf_vec_t* v);

// Traits:
//

// Get norms of each rotation matrix row
wtf_vec_t wtf_rot_norms(const wtf_rot_t* r);

#endif // WTF_ROTATION_H_