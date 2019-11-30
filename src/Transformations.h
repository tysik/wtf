#ifndef CTF_TRANSFORMATIONS_H_
#define CTF_TRANSFORMATIONS_H_

#include "Vectors.h"
#include "Rotations.h"

typedef double Trans[4][4];

void ttranslation(Trans* t, const Vect* v);

void tscale(Trans* t, const Vect* s);

void trotation(Trans* t, const Rot* r);

void tconcat(Trans* t, const Trans* t_lhs, const Trans* t_rhs);
//void tmul()

void ttransform(const Trans* t, Vect* points[], unsigned int num);

#endif // CTF_TRANSFORMATIONS_H_