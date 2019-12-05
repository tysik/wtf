#include "Rotation.h"
#include "Matrix.h"
#include "Vector.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

wtf_rot_t wtf_rot_x(wtf_scalar_t angle) {
    wtf_rot_t result = wtf_rot_eye();
    result.matrix[1][1] = result.matrix[2][2] = cos(angle);
    result.matrix[1][2] = result.matrix[2][1] = sin(angle);
    result.matrix[1][2] *= -1.0;
    return result;
}

wtf_rot_t wtf_rot_y(wtf_scalar_t angle) {
    wtf_rot_t result = wtf_rot_eye();
    result.matrix[0][0] = result.matrix[2][2] = cos(angle);
    result.matrix[0][2] = result.matrix[2][0] = sin(angle);
    result.matrix[2][0] *= -1.0;
    return result;
}

wtf_rot_t wtf_rot_z(wtf_scalar_t angle) {
    wtf_rot_t result = wtf_rot_eye();
    result.matrix[0][0] = result.matrix[1][1] = cos(angle);
    result.matrix[0][1] = result.matrix[1][0] = sin(angle);
    result.matrix[0][1] *= -1.0;
    return result;
}

wtf_rot_t wtf_from_axis_angle(wtf_vec_t axis, wtf_scalar_t angle) {
    return wtf_rot_eye();
    // TODO:
}

// void rfromQuat(wtf_rot_t* r, const wtf_quat_t* q) {
//     assert(q->is_normalized && "Non-unit quaternion");

//     // Diagonal
//     (*r)[0][0] = q->w * q->w + q->i * q->i - 0.5;
//     (*r)[1][1] = q->w * q->w + q->j * q->j - 0.5;
//     (*r)[2][2] = q->w * q->w + q->k * q->k - 0.5;

//     // Upper triange
//     (*r)[0][1] = q->i * q->j - q->w * q->k;
//     (*r)[0][2] = q->w * q->j + q->i * q->k;
//     (*r)[1][2] = q->j * q->k - q->w * q->i;

//     // Lower triangle
//     (*r)[1][0] = q->w * q->k + q->i * q->j;
//     (*r)[2][0] = q->i * q->k - q->w * q->j;
//     (*r)[2][1] = q->w * q->i + q->j * q->k;

//     rscale(r, 2.0);
// }

// void rtoQuat(wtf_quat_t* q, const wtf_rot_t* r) {
//     // double trace = (*r)[0][0] + (*r)[1][1] + (*r)[2][2];
//     // q->w = sqrt(trace + 1.0) / 2.0;
//     // q->i =
// }

// void rscale(wtf_rot_t* r, double k) {
//     int rows, cols;
//     for (rows = 0; rows < 3; ++rows) {
//         for (cols = 0; cols < 3; ++cols) {
//             (*r)[rows][cols] = k * (*r)[rows][cols];
//         }
//     }
// }

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

bool wtf_rot_is_orthogonal(const wtf_rot_t* r) {
    wtf_rot_t r_trans = wtf_rot_transposed(r);
    wtf_rot_t identity = wtf_rot_eye();
    wtf_rot_t mul = wtf_rot_multiply(r, &r_trans);
    return wtf_compare_rot(&identity, &mul);
}

bool wtf_compare_rot(const wtf_rot_t* r1, const wtf_rot_t* r2) {
    return wtf_compare_vec(&r1->i, &r2->i) && wtf_compare_vec(&r1->j, &r2->j) &&
           wtf_compare_vec(&r1->k, &r2->k);
}

void wtf_print_rot(const wtf_rot_t* r) {
    wtf_print_mat(&r->matrix);
}