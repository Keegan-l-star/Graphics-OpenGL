#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix.h"

#include <iostream>

template <int n>
class Shape{
    float color[4]={0.0f, 0.0f, 0.0f, 1.0f};
    public:
        virtual Shape& operator*=(const Matrix<n,n>&) =0;
        virtual Shape* operator*(const Matrix<n,n>&) const =0;
        virtual float* getPoints() const =0;
        virtual int getNumPoints() const =0;
        virtual void print() const =0;
        void setColour(int r, int g, int b, float a);
        float* getColour() const;
        virtual void zoom(int percent)=0; 
};
#include "Shape.cpp"

#endif /*SHAPE_H*/