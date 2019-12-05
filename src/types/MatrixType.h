#ifndef WTF_MATRIX_TYPE_H
#define WTF_MATRIX_TYPE_H

#include "ScalarType.h"
#include "VectorType.h"

// 3 x 3 matrix
typedef union wtf_mat_t { 
    wtf_scalar_t m[3][3]; 
    wtf_vec_t v[3];
} wtf_mat_t;

#endif // WTF_MATRIX_TYPE_H
