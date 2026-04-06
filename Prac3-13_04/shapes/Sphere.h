#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Shape.h"

template<int n>
class Sphere : public Shape<n> {
public:
    Vector<n> center;
    float radius = 1.0f;
    int stacks = 16; // latitude
    int slices = 32; // longitude

    Sphere();
    Sphere(const Vector<n>& center, float radius, int stacks = 16, int slices = 32);
    Sphere(const Sphere& other);
    Sphere& operator*=(const Matrix<n,n>& m) override;
    Sphere* operator*(const Matrix<n,n>& m) const override;
    float* getPoints() const override;
    int getNumPoints() const override;
    void print() const override;
    std::string fprint() const override;
    void zoom(int percent) override;
    void rotate(int degrees) override;
    void createGLBuffers(GLenum usage = GL_STATIC_DRAW) override;
    void updateGLBuffers(GLenum usage = GL_DYNAMIC_DRAW) override;
    GLenum glDrawMode() const override;
    void draw(bool wireframe = false) override;
private:
    void pushVertex(float* result, int &idx, float phi, float theta) const;
};

#include "Sphere.cpp"

#endif // SPHERE_H
