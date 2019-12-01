#include "Vectors.h"
#include "MathUtils.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

void wtf_empty_vec(wtf_vec_t* v) {
    v->x = v->y = v->z = 0.0;
    v->is_normalized = false;
}

void wtf_versor_x(wtf_vec_t* v) {
    v->x = 1.0;
    v->y = v->z = 0.0;
    v->is_normalized = true;
}

void wtf_versor_y(wtf_vec_t* v) {
    v->y = 1.0;
    v->x = v->z = 0.0;
    v->is_normalized = true;
}

void wtf_versor_z(wtf_vec_t* v) {
    v->z = 1.0;
    v->x = v->y = 0.0;
    v->is_normalized = true;
}

void wtf_vec_from_array(wtf_vec_t* v, double (*a)[3]) {
    memcpy(v, a, 3 * sizeof(double));
    v->is_normalized = false;
}

void wtf_negate_vec(wtf_vec_t* v) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void wtf_scale_vec(wtf_vec_t* v, double k) {
    v->x = k * v->x;
    v->y = k * v->y;
    v->z = k * v->z;
    v->is_normalized = false;
}

int wtf_normalize_vec(wtf_vec_t* v) {
    if (v->is_normalized) {
        return 1;
    } else {
        double norm = wtf_vec_norm(v);
        if (norm > 0.0) {
            wtf_scale_vec(v, 1.0 / norm);
            v->is_normalized = true;
            return 0;
        } else {
            return -1;
        }
    }
}

void wtf_add_vec(wtf_vec_t* v1, const wtf_vec_t* v2) {
    v1->x = v1->x + v2->x;
    v1->y = v1->y + v2->y;
    v1->z = v1->z + v2->z;
    v1->is_normalized = false;
}

void wtf_subtract_vec(wtf_vec_t* v1, const wtf_vec_t* v2) {
    v1->x = v1->x - v2->x;
    v1->y = v1->y - v2->y;
    v1->z = v1->z - v2->z;
    v1->is_normalized = false;
}

void wtf_vec_cross(wtf_vec_t* v, const wtf_vec_t* v1, const wtf_vec_t* v2) {
    v->x = v1->y * v2->z - v1->z * v2->y;
    v->y = v1->z * v2->x - v1->x * v2->z;
    v->z = v1->x * v2->y - v1->y * v2->x;
    v->is_normalized = false;
}

double wtf_vec_dot(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

double wtf_vec_norm(const wtf_vec_t* v) {
    return (v->is_normalized) ? 1.0 : sqrt(wtf_vec_squared_norm(v));
}

double wtf_vec_squared_norm(const wtf_vec_t* v) {
    return (v->is_normalized) ? (1.0) : (v->x * v->x + v->y * v->y + v->z * v->z);
}

bool wtf_compare_vec(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return dcmp(v1->x, v2->x) && dcmp(v1->y, v2->y) && dcmp(v1->z, v2->z);
}

void wtf_print_vec(const wtf_vec_t* v) {
    printf("(% .3f,% .3f,% .3f)", v->x, v->y, v->z);
}