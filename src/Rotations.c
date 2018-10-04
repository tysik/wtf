#include "Rotations.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void reye(Rot* R) {
    int rows, cols;
    for (rows = 0; rows < 3; ++rows) {
        for (cols = rows + 1; cols < 3; ++cols) {
            (*R)[rows][cols] = 0.0;
            (*R)[cols][rows] = 0.0;
        }
        (*R)[rows][rows] = 1.0;
    }
}

void rfromQuat(const Quat* q, Rot* result) {
    assert(q->is_normalized && "Non-unit quaternion");

    // Diagonal
    (*result)[0][0] = q->w * q->w + q->i * q->i - 0.5;
    (*result)[1][1] = q->w * q->w + q->j * q->j - 0.5;
    (*result)[2][2] = q->w * q->w + q->k * q->k - 0.5;

    // Upper triange
    (*result)[0][1] = q->i * q->j - q->w * q->k;
    (*result)[0][2] = q->w * q->j + q->i * q->k;
    (*result)[1][2] = q->j * q->k - q->w * q->i;

    // Lower triangle
    (*result)[1][0] = q->w * q->k + q->i * q->j;
    (*result)[2][0] = q->i * q->k - q->w * q->j;
    (*result)[2][1] = q->w * q->i + q->j * q->k;

    rscale(2.0, result, result);
}

void rrand(Rot* R) {
    int rows, cols;
    for (rows = 0; rows < 3; ++rows) {
        for (cols = 0; cols < 3; ++cols) {
            (*R)[rows][cols] = (double)rand() / (double)(RAND_MAX);
        }
    }
}

void rscale(double d, const Rot* R, Rot* result) {
    int rows, cols;
    //#pragma omp parallel for shared(R1, R2, result) private(rows, cols)
    for (rows = 0; rows < 3; ++rows) {
        for (cols = 0; cols < 3; ++cols) {
            (*result)[rows][cols] = d * (*R)[rows][cols];
        }
    }
}

void rmul(const Rot* R1, const Rot* R2, Rot* result) {
    int rows, cols;
    //#pragma omp parallel for shared(R1, R2, result) private(rows, cols)
    for (rows = 0; rows < 3; ++rows) {
        for (cols = 0; cols < 3; ++cols) {
            (*result)[rows][cols] = (*R1)[rows][0] * (*R2)[0][cols] +
                                    (*R1)[rows][1] * (*R2)[1][cols] +
                                    (*R1)[rows][2] * (*R2)[2][cols];
        }
    }
}

void rprint(const Rot* R) {
    for (int i = 0; i < 3; ++i) {
        printf("|% .3f,% .3f,% .3f|\n", (*R)[i][0], (*R)[i][1], (*R)[i][2]);
    }
}