#ifndef CYLINDER_H
#define CYLINDER_H

#include <sstream>
#include <iomanip>
#include <cmath>

#include "Shape.h"
#include "Matrix.h"
#include "Vector.h"

template <int n>
class Cylinder: public Shape<n> {
    private:
        Vector<n> center;
        float radius;
        float height;
        int resolution; // number of segments around the circle
        float angleOffset = 0.0f; // radians offset for sampling
        int axis = 2; // 0 = x, 1 = y, 2 = z (which axis the cylinder's central axis runs along)
        Vector<n> basisU;  // First perpendicular basis vector for circular cross-section
        Vector<n> basisV;  // Second perpendicular basis vector for circular cross-section

    public:
        Cylinder();
        Cylinder(const Vector<n>& center, float radius, float height, int resolution = 32, int axis = 2);
        // Construct from two circle centres (c1 and c2 are centres of the two circular faces)
        Cylinder(const Vector<n>& c1, const Vector<n>& c2, float radius, int resolution = 32);
        Cylinder(const Cylinder<n>&);
        virtual Cylinder<n>& operator*=(const Matrix<n,n>&);
        virtual Cylinder<n>* operator*(const Matrix<n,n>&) const;
        virtual float* getPoints() const;
        virtual int getNumPoints() const;
        virtual float* getTexCoords() const;
        virtual int getNumTexCoords() const;
        virtual float* getNormals() const;
        virtual int getNumNormals() const;
        // Normal helpers
        Vector<n> normalAtAngle(float angle) const; // normal for side at given angle (radians)
        Vector<n> normalAtPoint(const Vector<n>& p) const; // normal for arbitrary point on cylinder

        virtual void print() const;
        virtual std::string fprint() const;
        void zoom(int percent);
        void rotate(int degrees);
        // Change resolution (number of segments around the circle)
        void setResolution(int r);
        int getResolution() const;
        virtual GLenum glDrawMode() const override;
        virtual void draw(bool wireframe = false) override;
        virtual void createGLBuffers(GLenum usage = GL_STATIC_DRAW) override;
};

#include "Cylinder.cpp"

#endif /*CYLINDER_H*/
