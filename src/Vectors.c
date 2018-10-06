#include "Vectors.h"
#include "MathUtils.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

void vempty(Vect* v) {
    v->x = v->y = v->z = 0.0;
    v->is_normalized = false;
}

void vversorX(Vect* v) {
    v->x = 1.0;
    v->y = v->z = 0.0;
    v->is_normalized = true;
}

void vversorY(Vect* v) {
    v->y = 1.0;
    v->x = v->z = 0.0;
    v->is_normalized = true;
}

void vversorZ(Vect* v) {
    v->z = 1.0;
    v->x = v->y = 0.0;
    v->is_normalized = true;
}

void vfromArray(Vect* v, double (*a)[3]) {
    memcpy(v, a, 3 * sizeof(double));
    v->is_normalized = false;
}

void vnegate(Vect* v) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void vscale(Vect* v, double k) {
    v->x = k * v->x;
    v->y = k * v->y;
    v->z = k * v->z;
    v->is_normalized = false;
}

int vnormalize(Vect* v) {
    if (v->is_normalized) {
        return 1;
    } else {
        double norm = vnorm(v);
        if (norm > 0.0) {
            vscale(v, 1.0 / norm);
            v->is_normalized = true;
            return 0;
        } else {
            return -1;
        }
    }
}

void vadd(Vect* v1, const Vect* v2) {
    v1->x = v1->x + v2->x;
    v1->y = v1->y + v2->y;
    v1->z = v1->z + v2->z;
    v1->is_normalized = false;
}

void vsub(Vect* v1, const Vect* v2) {
    v1->x = v1->x - v2->x;
    v1->y = v1->y - v2->y;
    v1->z = v1->z - v2->z;
    v1->is_normalized = false;
}

void vcross(Vect* v, const Vect* v1, const Vect* v2) {
    v->x = v1->y * v2->z - v1->z * v2->y;
    v->y = v1->z * v2->x - v1->x * v2->z;
    v->z = v1->x * v2->y - v1->y * v2->x;
    v->is_normalized = false;
}

double vdot(const Vect* v1, const Vect* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

double vnorm(const Vect* v) {
    return (v->is_normalized) ? 1.0 : sqrt(vnormSquared(v));
}

double vnormSquared(const Vect* v) {
    return (v->is_normalized) ? (1.0) : (v->x * v->x + v->y * v->y + v->z * v->z);
}

bool vcmp(const Vect* v1, const Vect* v2) {
    return dcmp(v1->x, v2->x) && dcmp(v1->y, v2->y) && dcmp(v1->z, v2->z);
}

void vprint(const Vect* v) {
    printf("(% .3f,% .3f,% .3f)", v->x, v->y, v->z);
}