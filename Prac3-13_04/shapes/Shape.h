#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix.h"

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

template <int n>
class Shape{
    protected:
        float colour[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLuint VAO = 0u;
        GLuint VBO = 0u;
        GLuint EBO = 0u;
        int vertexCount = 0; // number of vertices (not floats)
        int lineIndexCount = 0;
    public:
        virtual Shape& operator*=(const Matrix<n,n>&) =0;
        virtual Shape* operator*(const Matrix<n,n>&) const =0;
        virtual float* getPoints() const =0;
        virtual int getNumPoints() const =0;
        virtual void print() const =0;
        virtual std::string fprint() const = 0;
        virtual void setColour(int r, int g, int b, float a=1.0f);
        float* getColour() const;
        virtual void zoom(int percent)=0;
        virtual void rotate(int degrees)=0;
        virtual void createGLBuffers(GLenum usage = GL_STATIC_DRAW);
        virtual void updateGLBuffers(GLenum usage = GL_DYNAMIC_DRAW);
        void setLineIndices(const std::vector<GLuint>& indices);
        void deleteGLBuffers();
        virtual GLenum glDrawMode() const = 0;
        virtual void draw(bool wireframe = false) = 0;
        Shape() = default;
            // Safe copy/move semantics: copies do NOT duplicate GL handles.
        Shape(const Shape& other);
        Shape& operator=(const Shape& other);
        Shape(Shape&& other) noexcept;
        Shape& operator=(Shape&& other) noexcept;
        virtual ~Shape();
};
#include "Shape.cpp"

#endif /*SHAPE_H*/