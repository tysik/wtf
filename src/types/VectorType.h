#ifndef WTF_VECTOR_TYPE_H
#define WTF_VECTOR_TYPE_H

#include "ScalarType.h"

#define PACKED __attribute__((packed, aligned(1)))

// 3D cartesian vector
typedef struct PACKED {
    wtf_scalar_t x, y, z;
} wtf_vec_t;

#undef PACKED

#endif // WTF_VECTOR_TYPE_H
