#ifndef WTF_QUATERNION_TYPE_H
#define WTF_QUATERNION_TYPE_H

#include "ScalarType.h"
#include "VectorType.h"

#define PACKED __attribute__((packed, aligned(1)))

typedef union {
    struct PACKED {
        wtf_scalar_t w, i, j, k;
    };
    struct PACKED {
        wtf_scalar_t s;
        wtf_vec_t v;
    };
    wtf_scalar_t data[4];
} wtf_quat_t;

#undef PACKED

#endif // WTF_QUATERNION_TYPE_H
