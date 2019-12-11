#ifndef WTF_VECTOR_IMPL_H_
#define WTF_VECTOR_IMPL_H_

#include "TypesFwd.h"
#include "MacroUtils.h"

#include <stdbool.h>

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

bool MUST_USE _wtf_vec_is_normalized_val(wtf_vec_t v);
bool MUST_USE _wtf_vec_is_normalized_ptr(const wtf_vec_t* v);

bool MUST_USE _wtf_vec_compare_val(wtf_vec_t v1, wtf_vec_t v2);
bool MUST_USE _wtf_vec_compare_ptr(const wtf_vec_t* v1, const wtf_vec_t* v2);

void _wtf_vec_print_val(wtf_vec_t v);
void _wtf_vec_print_ptr(const wtf_vec_t* v);

#endif // WTF_VECTOR_IMPL_H_