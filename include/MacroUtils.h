#ifndef WTF_MACRO_UTILS_H_
#define WTF_MACRO_UTILS_H_

#include "TypesFwd.h"

#define MUST_USE __attribute__((warn_unused_result))

#define WTF_ONE_ARG_VEC_FUNC(name, a) _Generic((a),    \
    wtf_vec_t        : _wtf_vec_##name##_val,          \
    wtf_vec_t*       : _wtf_vec_##name##_ptr,          \
    const wtf_vec_t* : _wtf_vec_##name##_ptr)(a)

#define WTF_TWO_ARGS_VEC_FUNC(name, a1, a2) _Generic((a1),   \
    wtf_vec_t        : _wtf_vec_##name##_val,                \
    wtf_vec_t*       : _wtf_vec_##name##_ptr,                \
    const wtf_vec_t* : _wtf_vec_##name##_ptr)(a1, a2)

#define WTF_ONE_ARG_QUAT_FUNC(name, a) _Generic((a),     \
    wtf_quat_t        : _wtf_quat_##name##_val,          \
    wtf_quat_t*       : _wtf_quat_##name##_ptr,          \
    const wtf_quat_t* : _wtf_quat_##name##_ptr)(a)

#define WTF_TWO_ARGS_QUAT_FUNC(name, a1, a2) _Generic((a1),    \
    wtf_quat_t        : _wtf_quat_##name##_val,                \
    wtf_quat_t*       : _wtf_quat_##name##_ptr,                \
    const wtf_quat_t* : _wtf_quat_##name##_ptr)(a1, a2)

#define WTF_ONE_VEC_ARG_QUAT_FUNC(name, a) _Generic((a),    \
    wtf_vec_t        : _wtf_quat_##name##_val,              \
    wtf_vec_t*       : _wtf_quat_##name##_ptr,              \
    const wtf_vec_t* : _wtf_quat_##name##_ptr)(a)

#define WTF_TWO_VEC_ARG_QUAT_FUNC(name, a1, a2) _Generic((a1),   \
    wtf_vec_t        : _wtf_quat_##name##_val,                   \
    wtf_vec_t*       : _wtf_quat_##name##_ptr,                   \
    const wtf_vec_t* : _wtf_quat_##name##_ptr)(a1, a2)

#endif // WTF_MACRO_UTILS_H_