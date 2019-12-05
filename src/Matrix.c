#include "Matrix.h"
#include "Vector.h"

wtf_mat_t wtf_mat_eye() {
    return (wtf_mat_t){
        .v[0] = wtf_versor_x(),
        .v[1] = wtf_versor_y(),
        .v[2] = wtf_versor_z(),
    };
}

wtf_mat_t wtf_mat_diag(wtf_scalar_t value) {
    wtf_mat_t result = wtf_mat_eye();
    return wtf_mat_scaled(&result, value);
}

wtf_mat_t wtf_mat_scaled(const wtf_mat_t* m, wtf_scalar_t k) {
    return (wtf_mat_t){
        .v[0] = wtf_vec_scaled(&m->v[0], k),
        .v[1] = wtf_vec_scaled(&m->v[1], k),
        .v[2] = wtf_vec_scaled(&m->v[2], k),
    };
}

wtf_mat_t wtf_mat_transposed(const wtf_mat_t* m) {
    wtf_mat_t result = *m;
    result.v[0].y = m->v[1].x;
    result.v[0].z = m->v[2].x;

    result.v[1].z = m->v[2].y;
    result.v[1].x = m->v[0].y;

    result.v[2].x = m->v[0].z;
    result.v[2].y = m->v[1].z;
    return result;
}

wtf_mat_t wtf_mat_multiply(const wtf_mat_t* m1, const wtf_mat_t* m2) {
    wtf_mat_t result;
    wtf_mat_t m2_trans = wtf_mat_transposed(m2);
    for (int rows = 0; rows < 3; ++rows) {
        for (int cols = 0; cols < 3; ++cols) {
            result.m[rows][cols] = wtf_vec_dot(&m1->v[rows], &m2_trans.v[cols]);
        }
    }
    return result;
}

wtf_scalar_t wtf_mat_determinant(const wtf_mat_t* m) {
    wtf_vec_t j_cross_k = wtf_vec_cross(&m->v[1], &m->v[2]);
    return wtf_vec_dot(&m->v[0], &j_cross_k);
}

void wtf_print_mat(const wtf_mat_t* m) {
    for (int i = 0; i < 3; ++i) {
        wtf_print_vec(&m->v[i]);
        printf("\n");
    }
}
