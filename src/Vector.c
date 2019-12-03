#include "Vector.h"
#include "MathUtils.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

wtf_vec_t wtf_empty_vec() {
    return (wtf_vec_t){.x = 0.0, .y = 0.0, .z = 0.0};
}

wtf_vec_t wtf_versor_x() {
    return (wtf_vec_t){.x = 1.0, .y = 0.0, .z = 0.0};
}

wtf_vec_t wtf_versor_y() {
    return (wtf_vec_t){.x = 0.0, .y = 1.0, .z = 0.0};
}

wtf_vec_t wtf_versor_z() {
    return (wtf_vec_t){.x = 0.0, .y = 0.0, .z = 1.0};
}

wtf_vec_t wtf_custom_vec(wtf_scalar_t x, wtf_scalar_t y, wtf_scalar_t z) {
    return (wtf_vec_t){.x = x, .y = y, .z = z};
}

wtf_vec_t wtf_vec_negated(const wtf_vec_t* v) {
    return (wtf_vec_t){
        .x = -v->x,
        .y = -v->y,
        .z = -v->z,
    };
}

wtf_vec_t wtf_vec_scaled(const wtf_vec_t* v, wtf_scalar_t k) {
    return (wtf_vec_t){
        .x = k * v->x,
        .y = k * v->y,
        .z = k * v->z,
    };
}

wtf_vec_t wtf_vec_normalized(const wtf_vec_t* v) {
    assert(wtf_vec_squared_norm(v) > 0 && "Trying to normalize a zero-length vector");
    return wtf_vec_scaled(v, 1.0 / wtf_vec_norm(v));
}

wtf_vec_t wtf_vec_add(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_vec_t){
        .x = v1->x + v2->x,
        .y = v1->y + v2->y,
        .z = v1->z + v2->z,
    };
}

wtf_vec_t wtf_vec_subtract(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_vec_t){
        .x = v1->x - v2->x,
        .y = v1->y - v2->y,
        .z = v1->z - v2->z,
    };
}

wtf_vec_t wtf_vec_cross(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_vec_t){
        .x = v1->y * v2->z - v1->z * v2->y,
        .y = v1->z * v2->x - v1->x * v2->z,
        .z = v1->x * v2->y - v1->y * v2->x,
    };
}

wtf_scalar_t wtf_vec_dot(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

wtf_scalar_t wtf_vec_norm(const wtf_vec_t* v) {
    return sqrt(wtf_vec_squared_norm(v));
}

wtf_scalar_t wtf_vec_squared_norm(const wtf_vec_t* v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

bool wtf_vec_is_normalized(const wtf_vec_t* v) {
    return wtf_dcmp(wtf_vec_squared_norm(v), 1.0);
}

bool wtf_compare_vec(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return wtf_dcmp(v1->x, v2->x) && wtf_dcmp(v1->y, v2->y) && wtf_dcmp(v1->z, v2->z);
}

void wtf_print_vec(const wtf_vec_t* v) {
    printf("[%.3f,% .3f,% .3f]", v->x, v->y, v->z);
}