#include "Transformation.h"
#include "Matrix.h"
#include "Rotation.h"
#include "Vector.h"

#include "types/TransformationType.h"

wtf_tf_t wtf_tf_identity() {
    return (wtf_tf_t){.rotation = wtf_mat_eye(), .translation = wtf_vec_empty()};
}

wtf_tf_t wtf_tf_translate(const wtf_vec_t* v) {
    return (wtf_tf_t){.rotation = wtf_mat_eye(), .translation = *v};
}

wtf_tf_t wtf_tf_rotate(const wtf_rot_t* r) {
    return (wtf_tf_t){.rotation = *r, .translation = wtf_vec_empty()};
}

wtf_tf_t wtf_tf_from_to(const wtf_vec_t* from, const wtf_vec_t* to) {
    wtf_vec_t up = wtf_vec_versor_y();
    wtf_vec_t forward = wtf_vec_subtract(to, from);
    forward = wtf_vec_normalized(&forward);
    wtf_vec_t right = wtf_vec_cross(&up, &forward);
    right = wtf_vec_normalized(&right);
    up = wtf_vec_cross(&forward, &right);

    wtf_rot_t rotation = {.i = right, .j = up, .k = forward};
    rotation = wtf_mat_inversed(&rotation);

    return (wtf_tf_t){.rotation = rotation, .translation = *from};
}

wtf_tf_t wtf_tf_combine(const wtf_tf_t* t1, const wtf_tf_t* t2) {
    wtf_vec_t t = wtf_rot_rotate(&t1->rotation, &t2->translation);
    return (wtf_tf_t){
        .rotation = wtf_mat_multiply(&t1->rotation, &t2->rotation),
        .translation = wtf_vec_add(&t, &t2->translation),
    };
}

wtf_vec_t wtf_tf_apply(const wtf_tf_t* tf, const wtf_vec_t* v) {
    wtf_vec_t rotated = wtf_rot_rotate(&tf->rotation, v);
    return wtf_vec_add(&rotated, &tf->translation);
}