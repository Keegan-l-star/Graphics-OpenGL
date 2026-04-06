template<int n>
SquarePyramid<n>::SquarePyramid(){
    base = new Square<n>();
    for (int i = 0; i < 4; ++i) {
        Vector<n> corner = base->getPoints()[i * n];
        sides[i] = new Triangle<n>(corner, corner, corner);
    }
}

template<int n>
SquarePyramid<n>::SquarePyramid(const Vector<n>& baseCenter, float baseSize, float height, int axis){
    base = new Square<n>(baseCenter, baseSize, axis);
    
    Vector<n> axisDir;
    for (int i = 0; i < n; ++i) axisDir[i] = 0.0f;
    if (axis == 0) axisDir[0] = 1.0f;
    else if (axis == 1) axisDir[1] = 1.0f;
    else axisDir[2] = 1.0f;
    
    Vector<n> apex;
    for (int i = 0; i < n; ++i) {
        apex[i] = baseCenter[i] + axisDir[i] * height;
    }
    
    float* basePts = base->getPoints();
    int numFloats = base->getNumPoints();
    int numVerts = numFloats / n;
    
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        Vector<n> v0, v1;
        for (int j = 0; j < n; ++j) {
            v0[j] = basePts[i * n + j];
            v1[j] = basePts[next * n + j];
        }
        sides[i] = new Triangle<n>(v0, v1, apex);
    }
    delete[] basePts;
}

template<int n>
SquarePyramid<n>::SquarePyramid(const Vector<n>& apex, const Vector<n>& baseCenter, float baseSize){
    base = new Square<n>(baseCenter, baseSize);
    
    float* basePts = base->getPoints();
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        Vector<n> v0, v1;
        for (int j = 0; j < n; ++j) {
            v0[j] = basePts[i * n + j];
            v1[j] = basePts[next * n + j];
        }
        sides[i] = new Triangle<n>(v0, v1, apex);
    }
    delete[] basePts;
}

template<int n>
SquarePyramid<n>::SquarePyramid(const Square<n>& baseSquare, const Vector<n>& apex){
    base = new Square<n>(baseSquare);
    
    float* basePts = base->getPoints();
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        Vector<n> v0, v1;
        for (int j = 0; j < n; ++j) {
            v0[j] = basePts[i * n + j];
            v1[j] = basePts[next * n + j];
        }
        sides[i] = new Triangle<n>(v0, v1, apex);
    }
    delete[] basePts;
}

template<int n>
SquarePyramid<n>::SquarePyramid(const SquarePyramid<n>& other){
    base = new Square<n>(*other.base);
    for (int i = 0; i < 4; ++i) {
        sides[i] = new Triangle<n>(*other.sides[i]);
    }
    
    float* c = other.getColour();
    for (int i = 0; i < 4; ++i) this->colour[i] = c[i];
    delete[] c;
}

template<int n>
SquarePyramid<n>::~SquarePyramid(){
    delete base;
    for (int i = 0; i < 4; ++i) {
        delete sides[i];
    }
}

template<int n>
SquarePyramid<n>& SquarePyramid<n>::operator*=(const Matrix<n,n>& m){
    *base *= m;
    for (int i = 0; i < 4; ++i) {
        *sides[i] *= m;
    }
    return *this;
}

template<int n>
SquarePyramid<n>* SquarePyramid<n>::operator*(const Matrix<n,n>& m) const{
    SquarePyramid<n>* result = new SquarePyramid<n>(*this);
    *result *= m;
    return result;
}

template<int n>
float* SquarePyramid<n>::getPoints() const{
    float* basePts = base->getPoints();
    int baseCount = base->getNumPoints();
    
    int totalCount = baseCount;
    for (int i = 0; i < 4; ++i) {
        totalCount += sides[i]->getNumPoints();
    }
    
    float* result = new float[totalCount];
    int idx = 0;
    
    for (int i = 0; i < baseCount; ++i) {
        result[idx++] = basePts[i];
    }
    delete[] basePts;
    
    for (int i = 0; i < 4; ++i) {
        float* sidePts = sides[i]->getPoints();
        int sideCount = sides[i]->getNumPoints();
        for (int j = 0; j < sideCount; ++j) {
            result[idx++] = sidePts[j];
        }
        delete[] sidePts;
    }
    
    return result;
}

template<int n>
int SquarePyramid<n>::getNumPoints() const{
    int total = base->getNumPoints();
    for (int i = 0; i < 4; ++i) {
        total += sides[i]->getNumPoints();
    }
    return total;
}

template<int n>
void SquarePyramid<n>::draw(bool wireframe){
    base->draw(wireframe);
    for (int i = 0; i < 4; ++i) {
        sides[i]->draw(wireframe);
    }
}

template<int n>
void SquarePyramid<n>::createGLBuffers(GLenum usage){
    base->createGLBuffers(usage);
    for (int i = 0; i < 4; ++i) {
        sides[i]->createGLBuffers(usage);
    }
}

template<int n>
GLenum SquarePyramid<n>::glDrawMode() const{
    return GL_TRIANGLES;
}

template<int n>
void SquarePyramid<n>::print() const{
    std::cout << "SquarePyramid:" << std::endl;
    base->print();
    for (int i = 0; i < 4; ++i) {
        std::cout << "Side " << i << ":" << std::endl;
        sides[i]->print();
    }
}

template<int n>
void SquarePyramid<n>::zoom(int percent){
    base->zoom(percent);
    for (int i = 0; i < 4; ++i) {
        sides[i]->zoom(percent);
    }
}

template<int n>
void SquarePyramid<n>::rotate(int degrees){
    base->rotate(degrees);
    for (int i = 0; i < 4; ++i) {
        sides[i]->rotate(degrees);
    }
}

template<int n>
std::string SquarePyramid<n>::fprint() const{
    std::ostringstream ss;
    ss << "SquarePyramid[" << base->fprint();
    for (int i = 0; i < 4; ++i) {
        ss << " Side" << i << "[" << sides[i]->fprint() << "]";
    }
    ss << "]";
    return ss.str();
}
