#ifndef WTF_MATRIX_H_
#define WTF_MATRIX_H_

#include "types/MatrixType.h"
#include "types/ScalarType.h"
#include "types/VectorType.h"

#include <stdbool.h>

#define MUST_USE __attribute__((warn_unused_result))

// Constructors:
//

// Construct an identity matrix
wtf_mat_t wtf_mat_eye();

// Construct a diagonal matrix with repeated value along diagonal
wtf_mat_t wtf_mat_diag(wtf_scalar_t s);

// Construct a diagonal matrix with elements of vector along diagonal
wtf_mat_t wtf_mat_diag_vec(const wtf_vec_t* v);

// Construct a skew-symmetric matrix from a vector
wtf_mat_t wtf_mat_skew(const wtf_vec_t* v);

// Construct an outer product of two vectors v1 (x) v2
wtf_mat_t wtf_mat_outer_product(const wtf_vec_t* v1, const wtf_vec_t* v2);

// Variations:
//

// Get a scaled matrix
wtf_mat_t wtf_mat_scaled(const wtf_mat_t* m, wtf_scalar_t s);

// Get a transposed matrix
wtf_mat_t wtf_mat_transposed(const wtf_mat_t* m);

// Get an inversed matrix
wtf_mat_t wtf_mat_inversed(const wtf_mat_t* m);

// Operations:
//

// Add matrices m1 and m2
wtf_mat_t wtf_mat_add(const wtf_mat_t* m1, const wtf_mat_t* m2);

// Multiply matrices m1 times m2
wtf_mat_t wtf_mat_multiply(const wtf_mat_t* m1, const wtf_mat_t* m2);

// Vector traits:
//

// Get a matrix trace
wtf_scalar_t wtf_mat_trace(const wtf_mat_t* m);

// Get a matrix determinant
wtf_scalar_t wtf_mat_determinant(const wtf_mat_t* m);

// Check if matrix is orthogonal
bool wtf_mat_is_orthogonal(const wtf_mat_t* m);

// Auxiliary:
//

// Compare two matrices
bool MUST_USE wtf_mat_compare(const wtf_mat_t* m1, const wtf_mat_t* m2);

// Print a matrix to stdout
void wtf_mat_print(const wtf_mat_t* m);

#undef MUST_USE

#endif // WTF_MATRIX_H_