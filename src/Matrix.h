#ifndef WTF_MATRIX_H_
#define WTF_MATRIX_H_

#include "types/ScalarType.h"
#include "types/VectorType.h"
#include "types/MatrixType.h"

#include <stdbool.h>

#define MUST_USE __attribute__((warn_unused_result))

// Constructors:
//

// Construct an identity matrix
wtf_mat_t wtf_mat_eye();

// Construct a diagonal matrix with repeated value along diagonal
wtf_mat_t wtf_mat_diag(wtf_scalar_t value);


// EMPTY, EYE, DIAG, DIAGVEC, SKEW, OUTER_PRODUCT

// Variations:
//

// Get a scaled matrix
wtf_mat_t wtf_mat_scaled(const wtf_mat_t* m, wtf_scalar_t k);

// Get a transposed matrix
wtf_mat_t wtf_mat_transposed(const wtf_mat_t* m);

// Get an inversed matrix
wtf_mat_t wtf_mat_inversed(const wtf_mat_t* m);



// Operations:
//

// Multiply matrices m1 times m2
wtf_mat_t wtf_mat_multiply(const wtf_mat_t* m1, const wtf_mat_t* m2);

// Vector traits:
//

// TRACE

// Get matrix determinant
wtf_scalar_t wtf_mat_determinant(const wtf_mat_t* m);

// Auxiliary:
//

// Compare two matrices
bool MUST_USE wtf_compare_mat3(const wtf_mat_t* m1, const wtf_mat_t* m2);

// Print a matrix to stdout
void wtf_print_mat(const wtf_mat_t* m);

#undef MUST_USE

#endif // WTF_MATRIX_H_