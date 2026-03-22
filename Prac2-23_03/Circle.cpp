template<int n>
Circle<n>::Circle(const Vector<n>& center, float radius, int resolution){
    this->center = center;
    this->radius = radius;
    if(resolution > 2 ){
        this->resolution = resolution;
    }else{
        this->resolution = 32;
    }
    this->angleOffset = 0.0f;
}

template <int n>
Circle<n>::Circle(const Circle<n> &two){
    this->center=two.center;
    this->radius=two.radius;
    this->resolution=two.resolution;
    {
        float* c = two.getColour();
        for (int i = 0; i < 4; ++i) this->colour[i] = c[i];
        delete[] c;
    }
    this->angleOffset = two.angleOffset;
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
        float a = (2.0f * M_PI * k) / resolution + angleOffset;
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
    float factor = percent / 100.0f;
    radius *= factor;
}

template<int n>
void Circle<n>::rotate(int degrees){
    // Advance the sampling offset so the polygon fan appears rotated.
    float delta = (float)degrees * (float)M_PI / 180.0f;
    angleOffset += delta;
    // keep angleOffset in reasonable range
    if (angleOffset > 2.0f * M_PI || angleOffset < -2.0f * M_PI) {
        angleOffset = fmodf(angleOffset, 2.0f * M_PI);
    }
    //std::cout << "Circle::rotate called: degrees=" << degrees << ", angleOffset=" << angleOffset << std::endl;
}


template<int n>
std::string Circle<n>::fprint() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6);
    // center
    for (int i = 0; i < n; ++i) ss << center[i] << ' ';
    ss << radius << ' ' << resolution << ' ' << angleOffset << ' ';
    int r = (int)roundf(this->colour[0]*255.0f);
    int g = (int)roundf(this->colour[1]*255.0f);
    int b = (int)roundf(this->colour[2]*255.0f);
    ss << r << ' ' << g << ' ' << b << ' ' << this->colour[3];
    return ss.str();
}

