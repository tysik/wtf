#ifndef WTF_TRANSFORMATIONS_H_
#define WTF_TRANSFORMATIONS_H_

#include "Vectors.h"
#include "Rotations.h"

typedef double Trans[4][4];

void ttranslation(Trans* t, const wtf_vec_t* v);

void tscale(Trans* t, const wtf_vec_t* s);

void trotation(Trans* t, const Rot* r);

void tconcat(Trans* t, const Trans* t_lhs, const Trans* t_rhs);
//void tmul()

void ttransform(const Trans* t, wtf_vec_t* points[], unsigned int num);

#endif // WTF_TRANSFORMATIONS_H_