#ifndef WTF_VECTOR_H_
#define WTF_VECTOR_H_

#include "VectorImpl.h"

// Constructors:
//

// Construct an empty vector (0, 0, 0)
wtf_vec_t wtf_vec_empty();

// Construct an X axis versor (1, 0, 0)
wtf_vec_t wtf_vec_versor_x();

// Construct a Y axis versor (0, 1, 0)
wtf_vec_t wtf_vec_versor_y();

// Construct a Z axis versor (0, 0, 1)
wtf_vec_t wtf_vec_versor_z();

// Construct a custom vector
wtf_vec_t wtf_vec_custom(wtf_scalar_t x, wtf_scalar_t y, wtf_scalar_t z);

// Variations:
//

// Negate a vector
#define wtf_vec_negated(v) WTF_VEC_ONE_ARG_FUNC(negated, v)

// Scale a vector by a scalar
#define wtf_vec_scaled(v, s) WTF_VEC_TWO_ARGS_FUNC(scaled, v, s)

// Get a normalized version of a vector
// The vector length must be greater than 0.
#define wtf_vec_normalized(v) WTF_VEC_ONE_ARG_FUNC(normalized, v)

// TODO: Add reflected vector
// TODO: Add LERP https://en.wikipedia.org/wiki/Linear_interpolation

// Vector operations:
//

// Add vectors v1 and v2
#define wtf_vec_add(v1, v2) WTF_VEC_TWO_ARGS_FUNC(add, v1, v2)

// Subtract vector v2 from vector v1
#define wtf_vec_subtract(v1, v2) WTF_VEC_TWO_ARGS_FUNC(subtract, v1, v2)

// Get a cross product of two vectors: v1 x v2
#define wtf_vec_cross(v1, v2) WTF_VEC_TWO_ARGS_FUNC(cross, v1, v2)

// Get a dot product of two vectors: v1 * v2
#define wtf_vec_dot(v1, v2) WTF_VEC_TWO_ARGS_FUNC(dot, v1, v2)

// Vector traits:
//

// Get a norm of a vector
#define wtf_vec_norm(v) WTF_VEC_ONE_ARG_FUNC(norm, v)

// Get a squared norm of a vector
#define wtf_vec_squared_norm(v) WTF_VEC_ONE_ARG_FUNC(squared_norm, v)

// Check if vector is normalized
#define wtf_vec_is_normalized(v) WTF_VEC_ONE_ARG_FUNC(is_normalized, v)

// Auxiliary:
//

// Compare two vectors by coordinates
#define wtf_vec_compare(v1, v2) WTF_VEC_TWO_ARGS_FUNC(compare, v1, v2)

// Print a vector to stdout
#define wtf_vec_print(v) WTF_VEC_ONE_ARG_FUNC(print, v)

#endif // WTF_VECTOR_H_