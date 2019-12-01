#ifndef WTF_VECTORS_H_
#define WTF_VECTORS_H_

#include <stdbool.h>

#define PACKED __attribute__((packed, aligned(1)))
#define MUST_USE __attribute__((warn_unused_result))

// 3D cartesian vector
typedef struct PACKED wtf_vec_t {
    double x, y, z;
    bool is_normalized;
} wtf_vec_t;

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

// Negate a vector
void wtf_negate_vec(wtf_vec_t* v);

// Scale a vector by a scalar
void wtf_scale_vec(wtf_vec_t* v, double k);

// Normalize a vector
// Returns:
//  1 if the vector was already normalized
//  0 if the normalization was OK
// -1 in case of failure
int MUST_USE wtf_normalize_vec(wtf_vec_t* v);

// Add vector v2 to vector v1
void wtf_add_vec(wtf_vec_t* v1, const wtf_vec_t* v2);

// Subtract vector v2 from vector v1
void wtf_subtract_vec(wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a cross product of two vectors: v1 x v2
void wtf_vec_cross(wtf_vec_t* v, const wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a dot product of two vectors: v1 * v2
double MUST_USE wtf_vec_dot(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Get a norm of a vector
double MUST_USE wtf_vec_norm(const wtf_vec_t* v);

// Get a squared norm of a vector
double MUST_USE wtf_vec_squared_norm(const wtf_vec_t* v);

// Compare two vectors by coordinates
bool MUST_USE wtf_compare_vec(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Print a vector to stdout
void wtf_print_vec(const wtf_vec_t* v);

#undef PACKED
#undef MUST_USE

#endif // WTF_VECTORS_H_