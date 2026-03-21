template<int n>
Circle<n>::Circle(const Vector<n>& center, float radius, int resolution){
    this->center = center;
    this->radius = radius;
    if(resolution > 2 ){
        this->resolution = resolution;
    }else{
        this->resolution = 32;
    }
}

template<int n>
Circle<n>& Circle<n>::operator*=(const Matrix<n,n>& m){
    Matrix<n,1> hc = (Matrix<n,1>)center;
    if (n == 3) {
        hc[2][0] = 1.0f;
    }
    center = Vector<n>(m * hc);
    if (n == 3) {
        center[2] = 0.0f;
    }
    return *this;
}

template<int n>
Circle<n>* Circle<n>::operator*(const Matrix<n,n>& m) const{
    Circle<n>* result=new Circle<n>(*this);
    *result*=m;
    return result;
}

template<int n>
float* Circle<n>::getPoints() const{
    int verts = resolution + 2;
    int totalFloats = verts * n;
    float* result = new float[totalFloats];

    // center vertex
    for (int i = 0; i < n; ++i) {
        result[i] = center[i];
    }

    for (int k = 0; k <= resolution; ++k) {
        float a = (2.0f * M_PI * k) / resolution;
        int vertIndex = k + 1; // +1 to skip center
        int base = vertIndex * n;
        if (n >= 2) {
            result[base + 0] = center[0] + cosf(a) * radius;
            result[base + 1] = center[1] + sinf(a) * radius;
        }
        for (int j = 2; j < n; ++j) {
            result[base + j] = center[j];
        }
    }

    return result;
}

template<int n>
int Circle<n>::getNumPoints() const{
    return (resolution + 2) * n;
}

template<int n>
void Circle<n>::print() const{
    std::cout << "_ Center _ " << std::endl;
    center.print();
    std::cout << "_ Radius _ " << std::endl;
    std::cout << radius << std::endl;
}

template<int n>
void Circle<n>::zoom(int percent){
    radius*percent;
}

