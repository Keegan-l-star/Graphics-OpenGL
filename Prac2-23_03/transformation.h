#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include <cmath>

template<int n>
Matrix<n,n> roty(int m);

template<int n>
Matrix<n,n> rotx(int m);

template<int n>
Matrix<n,n> rotz(int m);

template<int n>
Matrix<n,n> shearx(int xy,int xz);

template<int n>
Matrix<n,n> sheary(int yx,int yz);

template<int n>
Matrix<n,n> shearz(int zx,int zy);

template<int n>
Matrix<n,n> translation(float x,float y,float z);

template<int n>
Matrix<n,n> scaling(int m);

#include "transformation.cpp"

#endif //TRANSFORMATION_H