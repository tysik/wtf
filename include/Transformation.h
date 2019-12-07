#ifndef WTF_TRANSFORMATION_H_
#define WTF_TRANSFORMATION_H

#include "types/ScalarType.h"
#include "types/TransformationType.h"
#include "types/VectorType.h"

wtf_tf_t wtf_identity();
wtf_tf_t wtf_scale(wtf_scalar_t s);
wtf_tf_t wtf_scale_v(const wtf_vec_t* v);
wtf_tf_t wtf_translate(const wtf_vec_t* v);
wtf_tf_t wtf_rotate(const wtf_rot_t* r);
wtf_tf_t wtf_shear(const wtf_vec_t* v);
wtf_tf_t wtf_perspective(wtf_scalar_t angle);

wtf_tf_t wtf_combine_tfs(const wtf_tf_t* t1, const wtf_tf_t* t2);
wtf_vec_t wtf_apply_tf(const wtf_tf_t* t, const wtf_vec_t* v);

#endif // WTF_TRANSFORMATION_H_