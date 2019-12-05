#include "Quaternion.h"
#include "MathUtils.h"
#include "Vector.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

wtf_quat_t wtf_empty_quat() {
    return (wtf_quat_t){
        .s = 0.0,
        .v = wtf_empty_vec(),
    };
}

wtf_quat_t wtf_pure_quat(const wtf_vec_t* v) {
    return (wtf_quat_t){
        .s = 0.0,
        .v = *v,
    };
}

wtf_quat_t wtf_real_quat(wtf_scalar_t s) {
    return (wtf_quat_t){
        .s = s,
        .v = wtf_empty_vec(),
    };
}

wtf_quat_t wtf_rotor_quat(const wtf_vec_t* axis, wtf_scalar_t angle) {
    assert(wtf_vec_is_normalized(axis) && "Using non-normalized axis for quaternion rotor");

    return (wtf_quat_t){
        .s = cos(angle / 2.0),
        .v = wtf_vec_scaled(axis, sin(angle / 2.0)),
    };
}

wtf_quat_t wtf_quat_conjugate(const wtf_quat_t* q) {
    return (wtf_quat_t){
        .s = q->s,
        .v = wtf_vec_negated(&(q->v)),
    };
}

wtf_quat_t wtf_quat_scaled(const wtf_quat_t* q, wtf_scalar_t k) {
    return (wtf_quat_t){
        .s = q->s * k,
        .v = wtf_vec_scaled(&(q->v), k),
    };
}

wtf_quat_t wtf_quat_normalized(const wtf_quat_t* q) {
    assert(wtf_quat_squared_norm(q) > 0 && "Trying to normalize a zero-length quaternion");

    return wtf_quat_scaled(q, 1.0 / wtf_quat_norm(q));
}

wtf_quat_t wtf_quat_inversed(const wtf_quat_t* q) {
    assert(wtf_quat_squared_norm(q) > 0 && "Trying to inverse a zero-length quaternion");
    
    wtf_quat_t qc = wtf_quat_conjugate(q);
    return wtf_quat_scaled(&qc, 1.0 / wtf_quat_squared_norm(q));
}

wtf_quat_t wtf_quat_add(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return (wtf_quat_t){
        .s = q1->s + q2->s,
        .v = wtf_vec_add(&q1->v, &q2->v),
    };
}

wtf_quat_t wtf_quat_subtract(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return (wtf_quat_t){
        .s = q1->s - q2->s,
        .v = wtf_vec_subtract(&q1->v, &q2->v),
    };
}

wtf_quat_t wtf_quat_multiply(const wtf_quat_t* q1, const wtf_quat_t* q2) {
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

wtf_quat_t wtf_quat_divide(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    assert(wtf_quat_squared_norm(q2) > 0 && "Trying to divide by a zero-length quaternion");

    wtf_quat_t q2i = wtf_quat_inversed(q2);
    return wtf_quat_multiply(q1, &q2i);
}

wtf_vec_t wtf_quat_rotate(const wtf_quat_t* q, const wtf_vec_t* v) {
    assert(wtf_quat_is_normalized(q) && "Using non-unit quaternion for rotation");

    // v' = q * v * q'
    wtf_quat_t qv = wtf_pure_quat(v);
    wtf_quat_t q_inv = wtf_quat_conjugate(q); // For unit quat. inverse is its conjugate.
    wtf_quat_t result = wtf_quat_multiply(q, &qv);
    return wtf_quat_multiply(&result, &q_inv).v;
}

wtf_scalar_t wtf_quat_norm(const wtf_quat_t* q) {
    return sqrt(wtf_quat_squared_norm(q));
}

wtf_scalar_t wtf_quat_squared_norm(const wtf_quat_t* q) {
    return q->s * q->s + wtf_vec_squared_norm(&q->v);
}

bool wtf_quat_is_normalized(const wtf_quat_t* q) {
    return wtf_dcmp(wtf_quat_squared_norm(q), 1.0);
}

bool wtf_quat_is_pure(const wtf_quat_t* q) {
    return wtf_dcmp(q->w, 0.0);
}

bool wtf_quat_is_real(const wtf_quat_t* q) {
    return wtf_dcmp(wtf_vec_squared_norm(&q->v), 0.0);
}

bool wtf_compare_quat(const wtf_quat_t* q1, const wtf_quat_t* q2) {
    return wtf_dcmp(q1->s, q2->s) && wtf_compare_vec(&q1->v, &q2->v);
}

void wtf_print_quat(const wtf_quat_t* q) {
    printf("(%.3f, ", q->s);
    wtf_print_vec(&q->v);
    printf(")");
}