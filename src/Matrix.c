#include "Matrix.h"
#include "MathUtils.h"
#include "Vector.h"

#include "types/MatrixType.h"
#include "types/VectorType.h"

#include <assert.h>
#include <stdio.h>

wtf_mat_t wtf_mat_eye() {
    return (wtf_mat_t){
        .i = wtf_vec_versor_x(),
        .j = wtf_vec_versor_y(),
        .k = wtf_vec_versor_z(),
    };
}

wtf_mat_t wtf_mat_diag(wtf_scalar_t s) {
    wtf_mat_t result = wtf_mat_eye();
    return wtf_mat_scaled(&result, s);
}

wtf_mat_t wtf_mat_diag_vec(const wtf_vec_t* v) {
    return (wtf_mat_t){
        .i = wtf_vec_custom(v->x, 0.0, 0.0),
        .j = wtf_vec_custom(0.0, v->y, 0.0),
        .k = wtf_vec_custom(0.0, 0.0, v->z),
    };
}

wtf_mat_t wtf_mat_skew(const wtf_vec_t* v) {
    return (wtf_mat_t){
        .i = wtf_vec_custom(0.0, -v->z, v->y),
        .j = wtf_vec_custom(v->z, 0.0, -v->x),
        .k = wtf_vec_custom(-v->y, v->x, 0.0),
    };
}

wtf_mat_t wtf_mat_outer_product(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_mat_t){
        .i = wtf_vec_scaled(v2, v1->x),
        .j = wtf_vec_scaled(v2, v1->y),
        .k = wtf_vec_scaled(v2, v1->z),
    };
}

wtf_mat_t wtf_mat_scaled(const wtf_mat_t* m, wtf_scalar_t s) {
    return (wtf_mat_t){
        .i = wtf_vec_scaled(&m->i, s),
        .j = wtf_vec_scaled(&m->j, s),
        .k = wtf_vec_scaled(&m->k, s),
    };
}

wtf_mat_t wtf_mat_transposed(const wtf_mat_t* m) {
    wtf_mat_t result = *m;
    result.i.y = m->j.x;
    result.i.z = m->k.x;

    result.j.z = m->k.y;
    result.j.x = m->i.y;

    result.k.x = m->i.z;
    result.k.y = m->j.z;
    return result;
}

wtf_mat_t wtf_mat_inversed(const wtf_mat_t* m) {
    assert(!wtf_dcmp(wtf_mat_determinant(m), 0.0) && "Trying to inverse singular matrix");

    // M_inv = |j x k   k x i   i x j| / det(M)
    wtf_scalar_t det_inv = 1.0 / wtf_mat_determinant(m);
    wtf_vec_t v_01 = wtf_vec_cross(&m->i, &m->j);
    wtf_vec_t v_20 = wtf_vec_cross(&m->k, &m->i);
    wtf_vec_t v_12 = wtf_vec_cross(&m->j, &m->k);

    v_01 = wtf_vec_scaled(&v_01, det_inv);
    v_20 = wtf_vec_scaled(&v_20, det_inv);
    v_12 = wtf_vec_scaled(&v_12, det_inv);

    return (wtf_mat_t){
        .i = wtf_vec_custom(v_12.x, v_20.x, v_01.x),
        .j = wtf_vec_custom(v_12.y, v_20.y, v_01.y),
        .k = wtf_vec_custom(v_12.z, v_20.z, v_01.y),
    };
}

wtf_mat_t wtf_mat_add(const wtf_mat_t* m1, const wtf_mat_t* m2) {
    return (wtf_mat_t){
        .i = wtf_vec_add(&m1->i, &m2->i),
        .j = wtf_vec_add(&m1->j, &m2->j),
        .k = wtf_vec_add(&m1->k, &m2->k),
    };
}

wtf_mat_t wtf_mat_multiply(const wtf_mat_t* m1, const wtf_mat_t* m2) {
    wtf_mat_t result;
    wtf_mat_t m2_trans = wtf_mat_transposed(m2);
    for (int rows = 0; rows < 3; ++rows) {
        for (int cols = 0; cols < 3; ++cols) {
            result.data[rows][cols] = wtf_vec_dot(&m1->vectors[rows], &m2_trans.vectors[cols]);
        }
    }
    return result;
}

wtf_scalar_t wtf_mat_trace(const wtf_mat_t* m) {
    return m->data[0][0] + m->data[1][1] + m->data[2][2];
}

wtf_scalar_t wtf_mat_determinant(const wtf_mat_t* m) {
    wtf_vec_t j_cross_k = wtf_vec_cross(&m->j, &m->k);
    return wtf_vec_dot(&m->i, &j_cross_k);
}

bool wtf_mat_is_orthogonal(const wtf_mat_t* m) {
    wtf_mat_t m_trans = wtf_mat_transposed(m);
    wtf_mat_t identity = wtf_mat_eye();
    wtf_mat_t mul = wtf_mat_multiply(m, &m_trans);
    return wtf_mat_compare(&identity, &mul);
}

bool wtf_mat_compare(const wtf_mat_t* m1, const wtf_mat_t* m2) {
    return wtf_vec_compare(&m1->i, &m2->i) && wtf_vec_compare(&m1->j, &m2->j) &&
           wtf_vec_compare(&m1->k, &m2->k);
}

void wtf_mat_print(const wtf_mat_t* m) {
    for (int i = 0; i < 3; ++i) {
        wtf_vec_print(&m->vectors[i]);
        printf("\n");
    }
}
