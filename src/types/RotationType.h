#ifndef WTF_ROTATION_TYPE_H
#define WTF_ROTATION_TYPE_H

#include "ScalarType.h"
#include "VectorType.h"
#include "MatrixType.h"

#define PACKED __attribute__((packed, aligned(1)))

// 3D rotation matrix
typedef union wtf_rot_t {
    struct PACKED {
        wtf_vec_t i, j, k;
    };
    wtf_vec_t vectors[3];
    // TODO: switch to matrix3
    wtf_scalar_t matrix[3][3];
} wtf_rot_t;

#undef PACKED

#endif // WTF_ROTATION_TYPE_H
