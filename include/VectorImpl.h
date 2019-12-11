#ifndef WTF_VECTOR_IMPL_H_
#define WTF_VECTOR_IMPL_H_

#include "types/ScalarType.h"

#include <stdbool.h>

#define WTF_VEC_ONE_ARG_FUNC(name, a) _Generic((a),    \
    wtf_vec_t        : _wtf_vec_##name##_val,          \
    wtf_vec_t*       : _wtf_vec_##name##_ptr,          \
    const wtf_vec_t* : _wtf_vec_##name##_ptr)(a)

#define WTF_VEC_TWO_ARGS_FUNC(name, a1, a2) _Generic((a1),   \
    wtf_vec_t        : _wtf_vec_##name##_val,                \
    wtf_vec_t*       : _wtf_vec_##name##_ptr,                \
    const wtf_vec_t* : _wtf_vec_##name##_ptr)(a1, a2)

typedef union wtf_vec_t wtf_vec_t;

wtf_vec_t _wtf_vec_negated_val(wtf_vec_t v);
wtf_vec_t _wtf_vec_negated_ptr(const wtf_vec_t* v);

wtf_vec_t _wtf_vec_scaled_val(wtf_vec_t v, wtf_scalar_t s);
wtf_vec_t _wtf_vec_scaled_ptr(const wtf_vec_t* v, wtf_scalar_t s);

wtf_vec_t _wtf_vec_normalized_val(wtf_vec_t v);
wtf_vec_t _wtf_vec_normalized_ptr(const wtf_vec_t* v);

wtf_vec_t _wtf_vec_add_val(wtf_vec_t v1, wtf_vec_t v2);
wtf_vec_t _wtf_vec_add_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2);

wtf_vec_t _wtf_vec_subtract_val(wtf_vec_t v1, wtf_vec_t v2);
wtf_vec_t _wtf_vec_subtract_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2);

wtf_vec_t _wtf_vec_cross_val(wtf_vec_t v1, wtf_vec_t v2);
wtf_vec_t _wtf_vec_cross_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2);

wtf_scalar_t _wtf_vec_dot_val(wtf_vec_t v1, wtf_vec_t v2);
wtf_scalar_t _wtf_vec_dot_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2);

wtf_scalar_t _wtf_vec_norm_val(wtf_vec_t v);
wtf_scalar_t _wtf_vec_norm_ptr(const wtf_vec_t* v);

wtf_scalar_t _wtf_vec_squared_norm_val(wtf_vec_t v);
wtf_scalar_t _wtf_vec_squared_norm_ptr(const wtf_vec_t* v);

bool _wtf_vec_is_normalized_val(wtf_vec_t v);
bool _wtf_vec_is_normalized_ptr(const wtf_vec_t* v);

bool _wtf_vec_compare_val(wtf_vec_t v1, wtf_vec_t v2);
bool _wtf_vec_compare_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2);

void _wtf_vec_print_val(wtf_vec_t v);
void _wtf_vec_print_ptr(const wtf_vec_t* v);

#endif // WTF_VECTOR_IMPL_H_