#include "Rotations.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reye(Rot* r) {
    // int rows, cols;
    // for (rows = 0; rows < 3; ++rows) {
    //     for (cols = rows + 1; cols < 3; ++cols) {
    //         (*r)[rows][cols] = 0.0;
    //         (*r)[cols][rows] = 0.0;
    //     }
    //     (*r)[rows][rows] = 1.0;
    // }
    memset(r, 0, sizeof(Rot));
    (*r)[0][0] = (*r)[1][1] = (*r)[2][2] = 1.0;
}

void rrotX(Rot* r, double theta) {
    reye(r);
    (*r)[1][1] = (*r)[2][2] = cos(theta);
    (*r)[1][2] = (*r)[2][1] = sin(theta);
    (*r)[1][2] *= -1.0;
}

void rrotY(Rot* r, double theta) {
    reye(r);
    (*r)[0][0] = (*r)[2][2] = cos(theta);
    (*r)[0][2] = (*r)[2][0] = sin(theta);
    (*r)[2][0] *= -1.0;
}

void rrotZ(Rot* r, double theta) {
    reye(r);
    (*r)[0][0] = (*r)[1][1] = cos(theta);
    (*r)[0][1] = (*r)[1][0] = sin(theta);
    (*r)[0][1] *= -1.0;
}

void rfromQuat(Rot* r, const Quat* q) {
    assert(q->is_normalized && "Non-unit quaternion");

    // Diagonal
    (*r)[0][0] = q->w * q->w + q->i * q->i - 0.5;
    (*r)[1][1] = q->w * q->w + q->j * q->j - 0.5;
    (*r)[2][2] = q->w * q->w + q->k * q->k - 0.5;

    // Upper triange
    (*r)[0][1] = q->i * q->j - q->w * q->k;
    (*r)[0][2] = q->w * q->j + q->i * q->k;
    (*r)[1][2] = q->j * q->k - q->w * q->i;

    // Lower triangle
    (*r)[1][0] = q->w * q->k + q->i * q->j;
    (*r)[2][0] = q->i * q->k - q->w * q->j;
    (*r)[2][1] = q->w * q->i + q->j * q->k;

    rscale(r, 2.0);
}

void rtoQuat(Quat* q, const Rot* r) {
    // double trace = (*r)[0][0] + (*r)[1][1] + (*r)[2][2];
    // q->w = sqrt(trace + 1.0) / 2.0;
    // q->i =
}

void rrand(Rot* R) {
    int rows, cols;
    for (rows = 0; rows < 3; ++rows) {
        for (cols = 0; cols < 3; ++cols) {
            (*R)[rows][cols] = (double)rand() / (double)(RAND_MAX);
        }
    }
}

void rscale(Rot* r, double k) {
    int rows, cols;
    for (rows = 0; rows < 3; ++rows) {
        for (cols = 0; cols < 3; ++cols) {
            (*r)[rows][cols] = k * (*r)[rows][cols];
        }
    }
}

void rmul(Rot* r, const Rot* r1, const Rot* r2) {
    int rows, cols;
    for (rows = 0; rows < 3; ++rows) {
        for (cols = 0; cols < 3; ++cols) {
            (*r)[rows][cols] = (*r1)[rows][0] * (*r2)[0][cols] + (*r1)[rows][1] * (*r2)[1][cols] +
                               (*r1)[rows][2] * (*r2)[2][cols];
        }
    }
}

void rprint(const Rot* r) {
    for (int i = 0; i < 3; ++i) {
        printf("|% .3f,% .3f,% .3f|\n", (*r)[i][0], (*r)[i][1], (*r)[i][2]);
    }
}