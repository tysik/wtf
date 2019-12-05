#ifndef WTF_VECTOR_H_
#define WTF_VECTOR_H_

#include "types/ScalarType.h"
#include "types/VectorType.h"

#include <stdbool.h>

#define MUST_USE __attribute__((warn_unused_result))

// Constructors:
//

// Construct an empty vector (0, 0, 0)
wtf_vec_t wtf_empty_vec();

// Construct an X axis versor (1, 0, 0)
wtf_vec_t wtf_versor_x();

// Construct a Y axis versor (0, 1, 0)
wtf_vec_t wtf_versor_y();

// Construct a Z axis versor (0, 0, 1)
wtf_vec_t wtf_versor_z();

// Construct a custom vector 
wtf_vec_t wtf_custom_vec(wtf_scalar_t x, wtf_scalar_t y, wtf_scalar_t z);

// Variations:
//

// Negate a vector
wtf_vec_t wtf_vec_negated(const wtf_vec_t* v);

// Scale a vector by a scalar
wtf_vec_t wtf_vec_scaled(const wtf_vec_t* v, wtf_scalar_t s);

// Get a normalized version of a vector
// The vector length must be greater than 0.
wtf_vec_t wtf_vec_normalized(const wtf_vec_t* v);

// TODO: Add reflected vector
// TODO: Add LERP https://en.wikipedia.org/wiki/Linear_interpolation

// Vector operations:
//

// Add vectors v1 and v2
wtf_vec_t wtf_vec_add(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Subtract vector v2 from vector v1
wtf_vec_t wtf_vec_subtract(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a cross product of two vectors: v1 x v2
wtf_vec_t wtf_vec_cross(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a dot product of two vectors: v1 * v2
wtf_scalar_t wtf_vec_dot(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Vector traits:
//

// Get a norm of a vector
wtf_scalar_t wtf_vec_norm(const wtf_vec_t* v);

// Get a squared norm of a vector
wtf_scalar_t wtf_vec_squared_norm(const wtf_vec_t* v);

// Check if vector is normalized
bool wtf_vec_is_normalized(const wtf_vec_t* v);

// Auxiliary:
//

// Compare two vectors by coordinates
bool MUST_USE wtf_compare_vec(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Print a vector to stdout
void wtf_print_vec(const wtf_vec_t* v);

#undef MUST_USE

#endif // WTF_VECTOR_H_