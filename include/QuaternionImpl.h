#ifndef WTF_QUATERNION_IMPL_H_
#define WTF_QUATERNION_IMPL_H_

#include "MacroUtils.h"
#include "TypesFwd.h"

wtf_quat_t _wtf_quat_pure_val(wtf_vec_t v);
wtf_quat_t _wtf_quat_pure_ptr(const wtf_vec_t* v);

wtf_quat_t _wtf_quat_rotor_val(wtf_vec_t axis, wtf_scalar_t angle);
wtf_quat_t _wtf_quat_rotor_ptr(const wtf_vec_t* axis, wtf_scalar_t angle);

wtf_quat_t _wtf_quat_conjugate_val(wtf_quat_t q);
wtf_quat_t _wtf_quat_conjugate_ptr(const wtf_quat_t* q);

wtf_quat_t _wtf_quat_scaled_val(wtf_quat_t q, wtf_scalar_t s);
wtf_quat_t _wtf_quat_scaled_ptr(const wtf_quat_t* q, wtf_scalar_t s);

wtf_quat_t _wtf_quat_normalized_val(wtf_quat_t q);
wtf_quat_t _wtf_quat_normalized_ptr(const wtf_quat_t* q);

wtf_quat_t _wtf_quat_inversed_val(wtf_quat_t q);
wtf_quat_t _wtf_quat_inversed_ptr(const wtf_quat_t* q);

wtf_quat_t _wtf_quat_add_val(wtf_quat_t q1, wtf_quat_t q2);
wtf_quat_t _wtf_quat_add_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2);

wtf_quat_t _wtf_quat_subtract_val(wtf_quat_t q1, wtf_quat_t q2);
wtf_quat_t _wtf_quat_subtract_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2);

wtf_quat_t _wtf_quat_multiply_val(wtf_quat_t q1, wtf_quat_t q2);
wtf_quat_t _wtf_quat_multiply_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2);

wtf_quat_t _wtf_quat_divide_val(wtf_quat_t q1, wtf_quat_t q2);
wtf_quat_t _wtf_quat_divide_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2);

wtf_vec_t _wtf_quat_rotate_val(wtf_quat_t q, wtf_vec_t v);
wtf_vec_t _wtf_quat_rotate_ptr(const wtf_quat_t* q, const wtf_vec_t* v);

wtf_scalar_t _wtf_quat_norm_val(wtf_quat_t q);
wtf_scalar_t _wtf_quat_norm_ptr(const wtf_quat_t* q);

wtf_scalar_t _wtf_quat_squared_norm_val(wtf_quat_t q);
wtf_scalar_t _wtf_quat_squared_norm_ptr(const wtf_quat_t* q);

bool MUST_USE _wtf_quat_is_normalized_val(wtf_quat_t q);
bool MUST_USE _wtf_quat_is_normalized_ptr(const wtf_quat_t* q);

bool MUST_USE _wtf_quat_is_pure_val(wtf_quat_t q);
bool MUST_USE _wtf_quat_is_pure_ptr(const wtf_quat_t* q);

bool MUST_USE _wtf_quat_is_real_val(wtf_quat_t q);
bool MUST_USE _wtf_quat_is_real_ptr(const wtf_quat_t* q);

bool MUST_USE _wtf_quat_compare_val(wtf_quat_t q1, wtf_quat_t q2);
bool MUST_USE _wtf_quat_compare_ptr(const wtf_quat_t* q1, const wtf_quat_t* q2);

void _wtf_quat_print_val(wtf_quat_t q);
void _wtf_quat_print_ptr(const wtf_quat_t* q);

#endif // WTF_QUATERNION_IMPL_H_