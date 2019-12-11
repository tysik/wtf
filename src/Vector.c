#include "Vector.h"
#include "MathUtils.h"
#include "VectorImpl.h"

#include "types/VectorType.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
// TODO: #include <immintrin.h>

wtf_vec_t wtf_vec_empty() {
    return (wtf_vec_t){.x = 0.0, .y = 0.0, .z = 0.0};
}

wtf_vec_t wtf_vec_versor_x() {
    return (wtf_vec_t){.x = 1.0, .y = 0.0, .z = 0.0};
}

wtf_vec_t wtf_vec_versor_y() {
    return (wtf_vec_t){.x = 0.0, .y = 1.0, .z = 0.0};
}

wtf_vec_t wtf_vec_versor_z() {
    return (wtf_vec_t){.x = 0.0, .y = 0.0, .z = 1.0};
}

wtf_vec_t wtf_vec_custom(wtf_scalar_t x, wtf_scalar_t y, wtf_scalar_t z) {
    return (wtf_vec_t){.x = x, .y = y, .z = z};
}

wtf_vec_t _wtf_vec_negated_val(wtf_vec_t v) {
    return (wtf_vec_t){.x = -v.x, .y = -v.y, .z = -v.z};
}

wtf_vec_t _wtf_vec_negated_ptr(const wtf_vec_t* v) {
    return (wtf_vec_t){.x = -v->x, .y = -v->y, .z = -v->z};
}

wtf_vec_t _wtf_vec_scaled_val(wtf_vec_t v, wtf_scalar_t s) {
    return (wtf_vec_t){.x = s * v.x, .y = s * v.y, .z = s * v.z};
}

wtf_vec_t _wtf_vec_scaled_ptr(const wtf_vec_t* v, wtf_scalar_t s) {
    return (wtf_vec_t){.x = s * v->x, .y = s * v->y, .z = s * v->z};
}

wtf_vec_t _wtf_vec_normalized_val(wtf_vec_t v) {
    assert(wtf_vec_squared_norm(v) > 0 && "Trying to normalize a zero-length vector");

    return wtf_vec_scaled(v, 1.0 / wtf_vec_norm(v));
}

wtf_vec_t _wtf_vec_normalized_ptr(const wtf_vec_t* v) {
    assert(wtf_vec_squared_norm(v) > 0 && "Trying to normalize a zero-length vector");

    return wtf_vec_scaled(v, 1.0 / wtf_vec_norm(v));
}

wtf_vec_t _wtf_vec_add_val(wtf_vec_t v1, wtf_vec_t v2) {
    return (wtf_vec_t){
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
        .z = v1.z + v2.z,
    };
}

wtf_vec_t _wtf_vec_add_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_vec_t){
        .x = v1->x + v2->x,
        .y = v1->y + v2->y,
        .z = v1->z + v2->z,
    };
}

wtf_vec_t _wtf_vec_subtract_val(wtf_vec_t v1, wtf_vec_t v2) {
    return (wtf_vec_t){
        .x = v1.x - v2.x,
        .y = v1.y - v2.y,
        .z = v1.z - v2.z,
    };
}

wtf_vec_t _wtf_vec_subtract_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_vec_t){
        .x = v1->x - v2->x,
        .y = v1->y - v2->y,
        .z = v1->z - v2->z,
    };
}

wtf_vec_t _wtf_vec_cross_val(wtf_vec_t v1, wtf_vec_t v2) {
    return (wtf_vec_t){
        .x = v1.y * v2.z - v1.z * v2.y,
        .y = v1.z * v2.x - v1.x * v2.z,
        .z = v1.x * v2.y - v1.y * v2.x,
    };
}

wtf_vec_t _wtf_vec_cross_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return (wtf_vec_t){
        .x = v1->y * v2->z - v1->z * v2->y,
        .y = v1->z * v2->x - v1->x * v2->z,
        .z = v1->x * v2->y - v1->y * v2->x,
    };
}

wtf_scalar_t _wtf_vec_dot_val(wtf_vec_t v1, wtf_vec_t v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

wtf_scalar_t _wtf_vec_dot_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

wtf_scalar_t _wtf_vec_norm_val(wtf_vec_t v) {
    return sqrt(wtf_vec_squared_norm(v));
}

wtf_scalar_t _wtf_vec_norm_ptr(const wtf_vec_t* v) {
    return sqrt(wtf_vec_squared_norm(v));
}

wtf_scalar_t _wtf_vec_squared_norm_val(wtf_vec_t v) {
    return wtf_vec_dot(v, v);
}

wtf_scalar_t _wtf_vec_squared_norm_ptr(const wtf_vec_t* v) {
    return wtf_vec_dot(v, v);
}

bool _wtf_vec_is_normalized_val(wtf_vec_t v) {
    return wtf_dcmp(wtf_vec_squared_norm(v), 1.0);
}

bool _wtf_vec_is_normalized_ptr(const wtf_vec_t* v) {
    return wtf_dcmp(wtf_vec_squared_norm(v), 1.0);
}

bool _wtf_vec_compare_val(wtf_vec_t v1, wtf_vec_t v2) {
    return wtf_dcmp(v1.x, v2.x) && wtf_dcmp(v1.y, v2.y) && wtf_dcmp(v1.z, v2.z);
}

bool _wtf_vec_compare_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2) {
    return wtf_dcmp(v1->x, v2->x) && wtf_dcmp(v1->y, v2->y) && wtf_dcmp(v1->z, v2->z);
}

void _wtf_vec_print_val(wtf_vec_t v) {
    printf("[%.3f,% .3f,% .3f]", v.x, v.y, v.z);
}

void _wtf_vec_print_ptr(const wtf_vec_t* v) {
    printf("[%.3f,% .3f,% .3f]", v->x, v->y, v->z);
}