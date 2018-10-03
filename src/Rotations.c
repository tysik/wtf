#include "Rotations.h"

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