#include "light.h"

light::light(){
    for (int i = 0; i < 4; ++i){
        this->color[i] = 0.0f;
        this->dir[i] = 0.0f;
    } 

}

light::light(Vector<4> col, Vector<4> dir){ //Deep copy time.
    for (int i = 0; i < 4; ++i){
        this->color[i] = col[i];
        this->dir[i] = dir[i];
    } 

}

void light::setColor(Vector<4> col){
    for (int i = 0; i < 4; ++i){
        this->color[i] = col[i];
    } 
}

pointLight::pointLight():light(){
    intensity=0.0f;
    range=0.0f;
}

pointLight::pointLight(Vector<4> pos, Vector<4> col, float intensity, float range):light(col,pos){
    this->intensity=intensity;
    this->range=range;
}

Vector<4> pointLight::calculateLighting(const Vector<4>& pointPos, const Vector<4>& normal, const Vector<4>& material) const {
    // Implements pseudocode: E = max(0, n . l) * i / r^2 ; return k * E
    Vector<4> p = this->dir; // light position
    Vector<4> iCol = this->color; // light colour
    Vector<4> L = p - pointPos; // p - x
    float distSq = L * L;

    // If outside effective range return ambient-only scaled by material
    if (range > 0.0f && distSq > (range * range)) {
        Vector<4> ambientOnly;
        const float ambient = 0.005f; // lowered ambient
        for (int j = 0; j < 3; ++j) ambientOnly[j] = material[j] * ambient * material[3];
        ambientOnly[3] = material[3];
        return ambientOnly;
    }

    float dist = std::sqrt(distSq);
    Vector<4> ldir = (dist > 0.0f) ? L.unitVector() : Vector<4>{0.0f,0.0f,0.0f,0.0f};

    float ndotl = normal[0]*ldir[0] + normal[1]*ldir[1] + normal[2]*ldir[2];
    ndotl = std::max(0.0f, ndotl);

    // Use true inverse-square attenuation (1 / r^2). Guard against zero distance.
    float atten = 0.0f;
    const float eps = 1e-6f;
    atten = intensity / (std::max(distSq, eps));

    Vector<4> E;
    for (int j = 0; j < 3; ++j) E[j] = iCol[j] * (ndotl * atten);

    Vector<4> result;
    // Reduce ambient so attenuation dominates at distance; incorporate material alpha
    const float ambient = 0.005f;
    for (int j = 0; j < 3; ++j) {
        float val = material[j] * E[j] + material[j] * ambient;
        // scale by material alpha so transparent materials contribute less
        val *= material[3];
        if (val > 1.0f) val = 1.0f;
        if (val < 0.0f) val = 0.0f;
        result[j] = val;
    }
    result[3] = material[3];
    return result;
}


void pointLight::setPosition(Vector<4> pos){
    for (int i = 0; i < 4; ++i){
        this->dir[i] = pos[i];
    }
}

void pointLight::setIntensity(float i){
    this->intensity=i;
}

