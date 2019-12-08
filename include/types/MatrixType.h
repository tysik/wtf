#ifndef WTF_MATRIX_TYPE_H
#define WTF_MATRIX_TYPE_H

#include "ScalarType.h"
#include "VectorType.h"

#define PACKED __attribute__((packed, aligned(1)))

typedef union wtf_mat_t {
    struct PACKED {
        wtf_vec_t i, j, k;
    };
    wtf_scalar_t data[3][3];
    wtf_vec_t vectors[3];
} wtf_mat_t;

#undef PACKED

#endif // WTF_MATRIX_TYPE_H
