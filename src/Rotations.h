#ifndef ROTATIONS_H_
#define ROTATIONS_H_

#include "Vectors.h"
#include "Quaternions.h"

// Rotate vector v with quaternion q
Vect rotate(const Vect* v, const Quat* q);

#endif // ROTATIONS_H_