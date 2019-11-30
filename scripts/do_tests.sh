#!/bin/bash

echo "Performing tests"

echo "Math utilities tests:"
./tests/math_utils_test
echo ""

echo "Vectors tests:"
./tests/vectors_test
echo ""

echo "Quaternions tests:"
./tests/quaternions_test
echo ""

echo "Rotations tests:"
./tests/rotations_test
echo ""
