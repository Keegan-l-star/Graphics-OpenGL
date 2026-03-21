#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "Matrix.h"
#include "Vector.h"

template <int n>
class Circle: public Shape<n> {
    private:
        Vector<n> center;
        float radius;
        int resolution; // number of segments for the fan

    public:
        Circle(const Vector<n>& center, float radius, int resolution = 32);
        virtual Circle<n>& operator*=(const Matrix<n,n>&);
        virtual Circle<n>* operator*(const Matrix<n,n>&) const;
        virtual float* getPoints() const;
        virtual int getNumPoints() const;

        virtual void print() const;
        void zoom(int percent);
};

#include "Circle.cpp"

#endif /*CIRCLE_H*/