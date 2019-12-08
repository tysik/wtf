#ifndef WTF_VECTOR_TYPE_H
#define WTF_VECTOR_TYPE_H

#include "ScalarType.h"

#define PACKED __attribute__((packed, aligned(1)))

typedef union wtf_vec_t {
    struct PACKED {
        wtf_scalar_t x, y, z;
    };
    wtf_scalar_t data[3];
} wtf_vec_t;

#undef PACKED

#endif // WTF_VECTOR_TYPE_H
