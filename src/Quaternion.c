#include "Quaternion.h"
#include "MathUtils.h"
#include "QuaternionImpl.h"
#include "Vector.h"

#include "types/QuaternionType.h"
#include "types/VectorType.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

wtf_quat_t wtf_quat_empty() {
    return (wtf_quat_t){
        .s = 0.0,
        .v = wtf_vec_empty(),
    };
}

wtf_quat_t _wtf_quat_pure_val(wtf_vec_t v) {
    return (wtf_quat_t){
        .s = 0.0,
        .v = v,
    };
}

wtf_quat_t _wtf_quat_pure_ptr(const wtf_vec_t* v) {
    return (wtf_quat_t){
        .s = 0.0,
        .v = *v,
    };
}

wtf_quat_t wtf_quat_real(wtf_scalar_t s) {
    return (wtf_quat_t){
        .s = s,
        .v = wtf_vec_empty(),
    };
}

wtf_quat_t _wtf_quat_rotor_val(wtf_vec_t axis, wtf_scalar_t angle) {
    assert(wtf_vec_is_normalized(axis) && "Using non-normalized axis for quaternion rotor");

    return (wtf_quat_t){
        .s = cos(angle / 2.0),
        .v = wtf_vec_scaled(axis, sin(angle / 2.0)),
    };
}

wtf_quat_t _wtf_quat_rotor_ptr(const wtf_vec_t* axis, wtf_scalar_t angle) {
    assert(wtf_vec_is_normalized(axis) && "Using non-normalized axis for quaternion rotor");

    return (wtf_quat_t){
        .s = cos(angle / 2.0),
        .v = wtf_vec_scaled(axis, sin(angle / 2.0)),
    };
}

wtf_quat_t _wtf_quat_conjugate_val(wtf_quat_t q) {
    return (wtf_quat_t){
        .s = q.s,
        .v = wtf_vec_negated(q.v),
    };
}

wtf_quat_t _wtf_quat_conjugate_ptr(const wtf_quat_t* q) {
    return (wtf_quat_t){
        .s = q->s,
        .v = wtf_vec_negated(&q->v),
    };
}

wtf_quat_t _wtf_quat_scaled_val(wtf_quat_t q, wtf_scalar_t s) {
    return (wtf_quat_t){
        .s = q.s * s,
        .v = wtf_vec_scaled(q.v, s),
    };
}

wtf_quat_t _wtf_quat_scaled_ptr(const wtf_quat_t* q, wtf_scalar_t s) {
    return (wtf_quat_t){
        .s = q->s * s,
        .v = wtf_vec_scaled(&q->v, s),
    };
}

wtf_quat_t _wtf_quat_normalized_val(wtf_quat_t q) {
    assert(wtf_quat_squared_norm(q) > 0 && "Trying to normalize a zero-length quaternion");

    return wtf_quat_scaled(q, 1.0 / wtf_quat_norm(q));
}

wtf_quat_t _wtf_quat_normalized_ptr(const wtf_quat_t* q) {
    assert(wtf_quat_squared_norm(q) > 0 && "Trying to normalize a zero-length quaternion");

    return wtf_quat_scaled(q, 1.0 / wtf_quat_norm(q));
}

wtf_quat_t _wtf_quat_inversed_val(wtf_quat_t q) {
    assert(wtf_quat_squared_norm(q) > 0 && "Trying to inverse a zero-length quaternion");

    return wtf_quat_scaled(wtf_quat_conjugate(q), 1.0 / wtf_quat_squared_norm(q));
}

wtf_quat_t _wtf_quat_inversed_ptr(const wtf_quat_t* q) {
    assert(wtf_quat_squared_norm(q) > 0 && "Trying to inverse a zero-length quaternion");

    wtf_quat_t qc = wtf_quat_conjugate(q);
    return wtf_quat_scaled(&qc, 1.0 / wtf_quat_squared_norm(q));
}

wtf_quat_t _wtf_quat_add_val(wtf_quat_t q1, wtf_quat_t q2) {
    return (wtf_quat_t){
        .s = q1.s + q2.s,
        .v = wtf_vec_add(q1.v, q2.v),
    };
}

wtf_quat_t _wtf_quat_add_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return (wtf_quat_t){
        .s = q1->s + q2->s,
        .v = wtf_vec_add(&q1->v, &q2->v),
    };
}

wtf_quat_t _wtf_quat_subtract_val(wtf_quat_t q1, wtf_quat_t q2) {
    return (wtf_quat_t){
        .s = q1.s - q2.s,
        .v = wtf_vec_subtract(q1.v, q2.v),
    };
}

wtf_quat_t _wtf_quat_subtract_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return (wtf_quat_t){
        .s = q1->s - q2->s,
        .v = wtf_vec_subtract(&q1->v, &q2->v),
    };
}

wtf_quat_t _wtf_quat_multiply_val(wtf_quat_t q1, wtf_quat_t q2) {
    // q1 * q2 = [s1, v1] * [s2, v2] =
    // [s1 * s2 - dot(v1,v2), s1 * v2 + s2 * v1 + cross(v1,v2)]
    return (wtf_quat_t){
        .s = q1.s * q2.s - wtf_vec_dot(q1.v, q2.v),
        .v = wtf_vec_add(wtf_vec_add(wtf_vec_scaled(q1.v, q2.s), wtf_vec_scaled(q2.v, q1.s)),
                         wtf_vec_cross(q1.v, q2.v))};
}

wtf_quat_t _wtf_quat_multiply_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    // q1 * q2 = [s1, v1] * [s2, v2] =
    // [s1 * s2 - dot(v1,v2), s1 * v2 + s2 * v1 + cross(v1,v2)]
    wtf_quat_t result;
    wtf_vec_t v1 = wtf_vec_scaled(&q1->v, q2->s);
    wtf_vec_t v2 = wtf_vec_scaled(&q2->v, q1->s);
    wtf_vec_t cross = wtf_vec_cross(&q1->v, &q2->v);

    result.s = q1->s * q2->s - wtf_vec_dot(&q1->v, &q2->v);
    result.v = wtf_vec_add(&v1, &v2);
    result.v = wtf_vec_add(&result.v, &cross);

    return result;
}

wtf_quat_t _wtf_quat_divide_val(wtf_quat_t q1, wtf_quat_t q2) {
    assert(wtf_quat_squared_norm(q2) > 0 && "Trying to divide by a zero-length quaternion");

    return wtf_quat_multiply(q1, wtf_quat_inversed(q2));
}

wtf_quat_t _wtf_quat_divide_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    assert(wtf_quat_squared_norm(q2) > 0 && "Trying to divide by a zero-length quaternion");

    wtf_quat_t q2i = wtf_quat_inversed(q2);
    return wtf_quat_multiply(q1, &q2i);
}

wtf_vec_t _wtf_quat_rotate_val(wtf_quat_t q, wtf_vec_t v) {
    assert(wtf_quat_is_normalized(q) && "Using non-unit quaternion for rotation");

    // For unit quat. inverse is its conjugate.
    // v' = q * v * q*
    return wtf_quat_multiply(wtf_quat_multiply(q, wtf_quat_pure(v)), wtf_quat_conjugate(q)).v;
}

wtf_vec_t _wtf_quat_rotate_ptr(const wtf_quat_t* q, const wtf_vec_t* v) {
    assert(wtf_quat_is_normalized(q) && "Using non-unit quaternion for rotation");

    // For unit quat. inverse is its conjugate.
    // v' = q * v * q*
    wtf_quat_t qv = wtf_quat_pure(v);
    wtf_quat_t q_inv = wtf_quat_conjugate(q);
    wtf_quat_t result = wtf_quat_multiply(q, &qv);
    return wtf_quat_multiply(&result, &q_inv).v;
}

wtf_scalar_t _wtf_quat_norm_val(wtf_quat_t q) {
    return sqrt(wtf_quat_squared_norm(q));
}

wtf_scalar_t _wtf_quat_norm_ptr(const wtf_quat_t* q) {
    return sqrt(wtf_quat_squared_norm(q));
}

wtf_scalar_t _wtf_quat_squared_norm_val(wtf_quat_t q) {
    return q.s * q.s + wtf_vec_squared_norm(q.v);
}

wtf_scalar_t _wtf_quat_squared_norm_ptr(const wtf_quat_t* q) {
    return q->s * q->s + wtf_vec_squared_norm(&q->v);
}

bool _wtf_quat_is_normalized_val(wtf_quat_t q) {
    return wtf_dcmp(wtf_quat_squared_norm(q), 1.0);
}

bool _wtf_quat_is_normalized_ptr(const wtf_quat_t* q) {
    return wtf_dcmp(wtf_quat_squared_norm(q), 1.0);
}

bool _wtf_quat_is_pure_val(wtf_quat_t q) {
    return wtf_dcmp(q.w, 0.0);
}

bool _wtf_quat_is_pure_ptr(const wtf_quat_t* q) {
    return wtf_dcmp(q->w, 0.0);
}

bool _wtf_quat_is_real_val(wtf_quat_t q) {
    return wtf_dcmp(wtf_vec_squared_norm(q.v), 0.0);
}

bool _wtf_quat_is_real_ptr(const wtf_quat_t* q) {
    return wtf_dcmp(wtf_vec_squared_norm(&q->v), 0.0);
}

bool _wtf_quat_compare_val(wtf_quat_t q1, wtf_quat_t q2) {
    return wtf_dcmp(q1.s, q2.s) && wtf_vec_compare(q1.v, q2.v);
}

bool _wtf_quat_compare_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return wtf_dcmp(q1->s, q2->s) && wtf_vec_compare(&q1->v, &q2->v);
}

void _wtf_quat_print_val(wtf_quat_t q) {
    printf("(%.3f, ", q.s);
    wtf_vec_print(&q.v);
    printf(")");
}

void _wtf_quat_print_ptr(const wtf_quat_t* q) {
    printf("(%.3f, ", q->s);
    wtf_vec_print(&q->v);
    printf(")");
}