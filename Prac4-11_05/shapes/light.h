#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"
#include <algorithm>
#include <cmath>

class light{
    protected:
        Vector<4> color;
        Vector<4> dir;
    public:
        light();
        light(Vector<4> col, Vector<4> dir);
        virtual Vector<4> calculateLighting(const Vector<4>& pointPos, const Vector<4>& normal, const Vector<4>& material) const =0;
        void setColor(Vector<4> col);

};

class pointLight:public light{
    protected:
        float intensity;
        float range;
    public:
        pointLight();
        pointLight(Vector<4> pos, Vector<4> col, float intensity, float range);
        Vector<4> calculateLighting(const Vector<4>& pointPos, const Vector<4>& normal, const Vector<4>& material) const;
        void setPosition(Vector<4> pos);
        void setIntensity(float i);
};
#endif