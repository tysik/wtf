#ifndef WTF_VECTOR_H_
#define WTF_VECTOR_H_

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))
#define MUST_USE __attribute__((warn_unused_result))

// 3D cartesian vector
typedef union wtf_vec_t {
    struct PACKED {
        double x, y, z;
    };
    double array[3];
} wtf_vec_t;

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

// Construct a vector from array of 3 doubles
wtf_vec_t wtf_vec_from_array(double (*a)[3]);

// Variations:
//

// Negate a vector
wtf_vec_t wtf_vec_negated(const wtf_vec_t* v);

// Scale a vector by a scalar
wtf_vec_t wtf_vec_scaled(const wtf_vec_t* v, double k);

// Get a normalized version of a vector
// The vector length must be greater than 0.
wtf_vec_t wtf_vec_normalized(const wtf_vec_t* v);

// TODO: Add reflected vector
// TODO: Add LERP

// Vector operations:
//

// Add vectors v1 and v2
wtf_vec_t wtf_vec_add(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Subtract vector v2 from vector v1
wtf_vec_t wtf_vec_subtract(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a cross product of two vectors: v1 x v2
wtf_vec_t wtf_vec_cross(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a dot product of two vectors: v1 * v2
double wtf_vec_dot(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Vector traits:
//

// Get a norm of a vector
double wtf_vec_norm(const wtf_vec_t* v);

// Get a squared norm of a vector
double wtf_vec_squared_norm(const wtf_vec_t* v);

// Check if vector is normalized
bool wtf_vec_is_normalized(const wtf_vec_t* v);

// Auxiliary:
//

// Compare two vectors by coordinates
bool MUST_USE wtf_compare_vec(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Print a vector to stdout
void wtf_print_vec(const wtf_vec_t* v);

#undef PACKED
#undef MUST_USE

#endif // WTF_VECTOR_H_