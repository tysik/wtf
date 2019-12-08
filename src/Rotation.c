#include "Rotation.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

#include "types/QuaternionType.h"
#include "types/RotationType.h"
#include "types/VectorType.h"

#include <assert.h>
#include <math.h>

wtf_rot_t wtf_rot_x(wtf_scalar_t angle) {
    wtf_rot_t result = wtf_mat_diag(cos(angle));
    result.data[1][2] = result.data[2][1] = sin(angle);
    result.data[1][2] *= -1.0;
    result.data[0][0] = 1.0;
    return result;
}

wtf_rot_t wtf_rot_y(wtf_scalar_t angle) {
    wtf_rot_t result = wtf_mat_diag(cos(angle));
    result.data[0][2] = result.data[2][0] = sin(angle);
    result.data[2][0] *= -1.0;
    result.data[1][1] = 1.0;
    return result;
}

wtf_rot_t wtf_rot_z(wtf_scalar_t angle) {
    wtf_rot_t result = wtf_mat_diag(cos(angle));
    result.data[0][1] = result.data[1][0] = sin(angle);
    result.data[0][1] *= -1.0;
    result.data[2][2] = 1.0;
    return result;
}

wtf_rot_t wtf_rot_local_rpy(wtf_scalar_t roll, wtf_scalar_t pitch, wtf_scalar_t yaw) {
    wtf_rot_t rot_x = wtf_rot_x(roll);
    wtf_rot_t rot_y = wtf_rot_y(pitch);
    wtf_rot_t rot_z = wtf_rot_z(yaw);
    wtf_rot_t result = wtf_mat_multiply(&rot_x, &rot_y);
    return wtf_mat_multiply(&result, &rot_z);
}

wtf_rot_t wtf_rot_global_rpy(wtf_scalar_t roll, wtf_scalar_t pitch, wtf_scalar_t yaw) {
    wtf_rot_t rot_x = wtf_rot_x(roll);
    wtf_rot_t rot_y = wtf_rot_y(pitch);
    wtf_rot_t rot_z = wtf_rot_z(yaw);
    wtf_rot_t result = wtf_mat_multiply(&rot_z, &rot_y);
    return wtf_mat_multiply(&result, &rot_x);
}

wtf_rot_t wtf_rot_from_axis_angle(const wtf_vec_t* axis, wtf_scalar_t angle) {
    assert(wtf_vec_is_normalized(axis) && "Trying to construct rotation matrix from non-unit axis");

    // R = cos(a) * I + sin(a) * skew(axis) + (1 - cos(a)) * (axis (x) axis)
    wtf_scalar_t cos_angle = cos(angle);
    wtf_mat_t result = wtf_mat_eye();
    result = wtf_mat_scaled(&result, cos_angle);

    wtf_mat_t skew = wtf_mat_skew(axis);
    skew = wtf_mat_scaled(&skew, sin(angle));

    wtf_mat_t prod = wtf_mat_outer_product(axis, axis);
    prod = wtf_mat_scaled(&prod, 1.0 - cos_angle);

    result = wtf_mat_add(&result, &skew);
    return wtf_mat_add(&result, &prod);
}

wtf_rot_t wtf_rot_from_quaternion(const wtf_quat_t* q) {
    wtf_mat_t diag = wtf_mat_diag(q->w * q->w - wtf_vec_squared_norm(&q->v));
    wtf_vec_t aux = wtf_vec_scaled(&q->v, 2.0 * q->w);
    wtf_mat_t skew = wtf_mat_skew(&aux);
    wtf_mat_t prod = wtf_mat_outer_product(&q->v, &q->v);
    prod = wtf_mat_scaled(&prod, 2.0);
    wtf_mat_t result = wtf_mat_add(&diag, &skew);
    return wtf_mat_add(&result, &prod);
}

wtf_vec_t wtf_rot_rotate(const wtf_rot_t* r, const wtf_vec_t* v) {
    return (wtf_vec_t){
        .x = wtf_vec_dot(&r->i, v),
        .y = wtf_vec_dot(&r->j, v),
        .z = wtf_vec_dot(&r->k, v),
    };
}

wtf_vec_t wtf_rot_norms(const wtf_rot_t* r) {
    return (wtf_vec_t){
        .x = wtf_vec_norm(&r->i),
        .y = wtf_vec_norm(&r->j),
        .z = wtf_vec_norm(&r->k),
    };
}
