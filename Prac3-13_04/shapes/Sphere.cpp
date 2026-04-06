
template<int n>
Sphere<n>::Sphere(){
    center = Vector<n>();
    radius = 1.0f;
    stacks = 16;
    slices = 32;
}

template<int n>
Sphere<n>::Sphere(const Vector<n>& c, float r, int s, int l){
    center = c;
    radius = r;
    stacks = (s>2)?s:16;
    slices = (l>2)?l:32;
}

template<int n>
Sphere<n>::Sphere(const Sphere<n>& other){
    this->center = other.center;
    this->radius = other.radius;
    this->stacks = other.stacks;
    this->slices = other.slices;
    {
        float* c = other.getColour();
        for (int i = 0; i < 4; ++i) this->colour[i] = c[i];
        delete[] c;
    }
}

template<int n>
Sphere<n>& Sphere<n>::operator*=(const Matrix<n,n>& m){
    Matrix<n,1> hc = (Matrix<n,1>)center;
    if (n >= 3) {
        hc[n-1][0] = 1.0f;  // Set homogeneous coordinate
    }
    Vector<n> newCenter = Vector<n>(m * hc);
    if (n >= 3) {
        newCenter[n-1] = 0.0f;  // Reset homogeneous coordinate for direction
    }
    center = newCenter;
    return *this;
}

template<int n>
Sphere<n>* Sphere<n>::operator*(const Matrix<n,n>& m) const{
    Sphere<n>* result = new Sphere<n>(*this);
    *result *= m;
    return result;
}

template<int n>
float* Sphere<n>::getPoints() const{
    // build triangle list for stacks x slices
    int tris = stacks * slices * 2; // two triangles per quad
    int verts = tris * 3;
    int totalFloats = verts * n;
    float* result = new float[totalFloats];
    int idx = 0;

    for (int s = 0; s < stacks; ++s){
        float phi1 = M_PI * ( (float)s / stacks - 0.5f );
        float phi2 = M_PI * ( (float)(s+1) / stacks - 0.5f );
        for (int t = 0; t < slices; ++t){
            float theta1 = 2.0f * M_PI * ( (float)t / slices );
            float theta2 = 2.0f * M_PI * ( (float)(t+1) / slices );

            this->pushVertex(result, idx, phi1, theta1);
            this->pushVertex(result, idx, phi2, theta1);
            this->pushVertex(result, idx, phi1, theta2);

            this->pushVertex(result, idx, phi1, theta2);
            this->pushVertex(result, idx, phi2, theta1);
            this->pushVertex(result, idx, phi2, theta2);
        }
    }
    return result;
}

template<int n>
void Sphere<n>::pushVertex(float* result, int &idx, float phi, float theta) const{
    float x = radius * cosf(phi) * cosf(theta) + center[0];
    float y = radius * cosf(phi) * sinf(theta) + center[1];
    float z = radius * sinf(phi) + center[2];
    if (n >= 1) result[idx++] = x;
    if (n >= 2) result[idx++] = y;
    if (n >= 3) result[idx++] = z;
    for (int k = 3; k < n; ++k) result[idx++] = center[k];
}

template<int n>
int Sphere<n>::getNumPoints() const{
    int tris = stacks * slices * 2;
    int verts = tris * 3;
    return verts * n;
}

template<int n>
void Sphere<n>::print() const{
    std::cout << "_ Sphere Center _" << std::endl; center.print();
    std::cout << "radius: " << radius << " stacks:" << stacks << " slices:" << slices << std::endl;
}

template<int n>
std::string Sphere<n>::fprint() const{
    std::ostringstream ss; ss << std::fixed << std::setprecision(6);
    ss << center[0] << ' ';
    if (n>1) ss << center[1] << ' ';
    if (n>2) ss << center[2] << ' ';
    ss << radius << ' ' << stacks << ' ' << slices << ' ';
    int r = (int)roundf(this->colour[0]*255.0f);
    int g = (int)roundf(this->colour[1]*255.0f);
    int b = (int)roundf(this->colour[2]*255.0f);
    ss << r << ' ' << g << ' ' << b << ' ' << this->colour[3];
    return ss.str();
}

template<int n>
void Sphere<n>::zoom(int percent){
    float factor = percent / 100.0f;
    radius *= factor;
}

template<int n>
void Sphere<n>::rotate(int degrees){
    // rotate center by matrix around origin
    *this *= rotz<n>(degrees);
}

template<int n>
void Sphere<n>::createGLBuffers(GLenum usage){
    Shape<n>::createGLBuffers(usage);

    // Build line indices for wireframe: every triangle's three edges
    int verts = getNumPoints() / n;
    int triangles = verts / 3;
    std::vector<GLuint> indices;
    indices.reserve(triangles * 6);
    for (int t = 0; t < triangles; ++t) {
        GLuint b = (GLuint)(t * 3);
        indices.push_back(b);
        indices.push_back(b + 1);
        indices.push_back(b + 1);
        indices.push_back(b + 2);
        indices.push_back(b + 2);
        indices.push_back(b);
    }
    if (!indices.empty()) this->setLineIndices(indices);
}

template<int n>
void Sphere<n>::updateGLBuffers(GLenum usage){
    Shape<n>::updateGLBuffers(usage);
}

template<int n>
GLenum Sphere<n>::glDrawMode() const{ return GL_TRIANGLES; }

template<int n>
void Sphere<n>::draw(bool wireframe){
    if (this->VAO == 0u) this->createGLBuffers();
    Shape<n>::draw(wireframe);
}
