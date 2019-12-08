#ifndef WTF_TF_TYPE_H
#define WTF_TF_TYPE_H

#include "RotationType.h"
#include "ScalarType.h"
#include "VectorType.h"

#define PACKED __attribute__((packed, aligned(1)))

typedef union wtf_tf_t {
    struct PACKED {
        wtf_rot_t rotation;
        wtf_vec_t translation;
    };
    struct PACKED {
        wtf_vec_t i, j, k, t;
    };
    wtf_vec_t vectors[4];
    wtf_scalar_t data[3][4];
} wtf_tf_t;

#undef PACKED

#endif // WTF_TF_TYPE_H
