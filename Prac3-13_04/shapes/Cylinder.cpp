
template<int n>
Cylinder<n>::Cylinder(const Vector<n>& center, float radius, float height, int resolution, int axis){
    this->center = center;
    this->radius = radius;
    this->height = height;
    if(resolution > 2 ) this->resolution = resolution;
    else this->resolution = 32;
    this->angleOffset = 0.0f;
    this->axis = axis;
    
    for (int i = 0; i < n; ++i) {
        this->basisU[i] = 0.0f;
        this->basisV[i] = 0.0f;
    }
    
    if (axis == 0) {
        this->basisU[1] = 1.0f;
        this->basisV[2] = 1.0f;
    } else if (axis == 1) {
        this->basisU[0] = 1.0f;
        this->basisV[2] = 1.0f;
    } else {
        this->basisU[0] = 1.0f;
        this->basisV[1] = 1.0f;
    }
}

template<int n>
Cylinder<n>::Cylinder(const Vector<n>& c1, const Vector<n>& c2, float radius, int resolution){
    this->center = Vector<n>();
    for (int i = 0; i < n; ++i) this->center[i] = (c1[i] + c2[i]) / 2.0f;
    
    Vector<n> axisDir;
    float distSq = 0.0f;
    for (int i = 0; i < n; ++i) {
        axisDir[i] = c2[i] - c1[i];
        distSq += axisDir[i] * axisDir[i];
    }
    this->height = sqrtf(distSq);
    
    float invLen = (distSq > 0) ? 1.0f / sqrtf(distSq) : 1.0f;
    for (int i = 0; i < n; ++i) axisDir[i] *= invLen;
    

    int best = 0; 
    float bestv = fabsf(c2[0] - c1[0]);
    for (int i = 1; i < n; ++i) {
        float v = fabsf(c2[i] - c1[i]);
        if (v > bestv) { best = i; bestv = v; }
    }
    this->axis = best;
    
    Vector<n> temp;
    for (int i = 0; i < n; ++i) temp[i] = 0.0f;
    if (fabsf(axisDir[0]) < 0.9f) {
        temp[0] = 1.0f;
    } else {
        temp[1] = 1.0f;
    }
    
    this->basisU = Vector<n>();
    for (int i = 0; i < n; ++i) this->basisU[i] = 0.0f;
    if (n >= 3) {
        this->basisU[0] = axisDir[1] * temp[2] - axisDir[2] * temp[1];
        this->basisU[1] = axisDir[2] * temp[0] - axisDir[0] * temp[2];
        this->basisU[2] = axisDir[0] * temp[1] - axisDir[1] * temp[0];
    }
    float ulenSq = 0.0f;
    for (int i = 0; i < n; ++i) ulenSq += this->basisU[i] * this->basisU[i];
    float uinvLen = (ulenSq > 0) ? 1.0f / sqrtf(ulenSq) : 1.0f;
    for (int i = 0; i < n; ++i) this->basisU[i] *= uinvLen;
    
    this->basisV = Vector<n>();
    for (int i = 0; i < n; ++i) this->basisV[i] = 0.0f;
    if (n >= 3) {
        this->basisV[0] = axisDir[1] * this->basisU[2] - axisDir[2] * this->basisU[1];
        this->basisV[1] = axisDir[2] * this->basisU[0] - axisDir[0] * this->basisU[2];
        this->basisV[2] = axisDir[0] * this->basisU[1] - axisDir[1] * this->basisU[0];
    }
    
    this->radius = radius;
    if(resolution > 2 ) this->resolution = resolution;
    else this->resolution = 32;
    this->angleOffset = 0.0f;
}

template<int n>
Cylinder<n>::Cylinder(){
    center = Vector<n>();
    radius = 1.0f;
    height = 1.0f;
    resolution = 32;
    angleOffset = 0.0f;
    this->axis = 2;
    for (int i = 0; i < n; ++i) {
        this->basisU[i] = 0.0f;
        this->basisV[i] = 0.0f;
    }
    this->basisU[0] = 1.0f;
    this->basisV[1] = 1.0f;
}

template<int n>
Cylinder<n>::Cylinder(const Cylinder<n> &two){
    this->center=two.center;
    this->radius=two.radius;
    this->height=two.height;
    this->resolution=two.resolution;
    {
        float* c = two.getColour();
        for (int i = 0; i < 4; ++i) this->colour[i] = c[i];
        delete[] c;
    }
    this->angleOffset = two.angleOffset;
    this->axis = two.axis;
    this->basisU = two.basisU;
    this->basisV = two.basisV;
}

template<int n>
Cylinder<n>& Cylinder<n>::operator*=(const Matrix<n,n>& m){
    Matrix<n,1> hc = (Matrix<n,1>)center;
    if (n >= 3) {
        hc[n-1][0] = 1.0f;
    }
    Matrix<n,1> newCenterMat = m * hc;
    Vector<n> newCenter = Vector<n>(newCenterMat);
    if (n >= 3) {
        newCenter[n-1] = 0.0f;
    }

    Matrix<n,1> basisUMat = (Matrix<n,1>)this->basisU;
    Matrix<n,1> basisVMat = (Matrix<n,1>)this->basisV;
    Vector<n> newBasisU = Vector<n>(m * basisUMat);
    Vector<n> newBasisV = Vector<n>(m * basisVMat);
    

    float uLen = 0.0f, vLen = 0.0f;
    for (int i = 0; i < n; ++i) {
        uLen += newBasisU[i] * newBasisU[i];
        vLen += newBasisV[i] * newBasisV[i];
    }
    uLen = sqrtf(uLen);
    vLen = sqrtf(vLen);
    if (uLen > 0.0f) for (int i = 0; i < n; ++i) newBasisU[i] /= uLen;
    if (vLen > 0.0f) for (int i = 0; i < n; ++i) newBasisV[i] /= vLen;
    
    this->basisU = newBasisU;
    this->basisV = newBasisV;

    int iA = 0, iB = 1;
    if (this->axis == 0) { iA = 1; iB = 2; }
    else if (this->axis == 1) { iA = 0; iB = 2; }
    else { iA = 0; iB = 1; }

    Vector<n> offset;
    for (int i = 0; i < n; ++i) offset[i] = 0.0f;
    offset[iA] = radius;

    Matrix<n,1> pMat = (Matrix<n,1>)(center + offset);
    if (n >= 3) {
        pMat[n-1][0] = 1.0f;
    }
    Vector<n> newP = Vector<n>(m * pMat);
    if (n >= 3) {
        newP[n-1] = 0.0f;
    }
    Vector<n> transformedVec;
    for (int i = 0; i < n; ++i) transformedVec[i] = newP[i] - newCenter[i];

    float delta = 0.0f;
    if (n > 1) delta = atan2f(transformedVec[iB], transformedVec[iA]);
    angleOffset += delta;

    center = newCenter;
    return *this;
}

template<int n>
Cylinder<n>* Cylinder<n>::operator*(const Matrix<n,n>& m) const{
    Cylinder<n>* result=new Cylinder<n>(*this);
    *result*=m;
    return result;
}

template<int n>
float* Cylinder<n>::getPoints() const{
    int capVerts = 1 + (resolution + 1);
    int sideVerts = 2 * (resolution + 1);
    int totalVerts = capVerts + capVerts + sideVerts;
    int totalFloats = totalVerts * n;
    float* result = new float[totalFloats];
    
    Vector<n> axisDir;
    for (int i = 0; i < n; ++i) axisDir[i] = 0.0f;
    if (n >= 3) {
        axisDir[0] = this->basisU[1] * this->basisV[2] - this->basisU[2] * this->basisV[1];
        axisDir[1] = this->basisU[2] * this->basisV[0] - this->basisU[0] * this->basisV[2];
        axisDir[2] = this->basisU[0] * this->basisV[1] - this->basisU[1] * this->basisV[0];
    }
    
    Vector<n> topCenter, bottomCenter;
    for (int i = 0; i < n; ++i) {
        topCenter[i] = center[i] + axisDir[i] * height / 2.0f;
        bottomCenter[i] = center[i] - axisDir[i] * height / 2.0f;
    }
    
    int idx = 0;
    

    for (int j = 0; j < n; ++j) {
        result[idx++] = topCenter[j];
    }
    
    for (int k = 0; k <= resolution; ++k) {
        float a = (2.0f * M_PI * k) / resolution + angleOffset;
        float ca = cosf(a);
        float sa = sinf(a);
        
        for (int j = 0; j < n; ++j) {
            float uComp = this->basisU[j] * ca;
            float vComp = this->basisV[j] * sa;
            result[idx++] = topCenter[j] + radius * (uComp + vComp);
        }
    }
    
    for (int j = 0; j < n; ++j) {
        result[idx++] = bottomCenter[j];
    }
    

    for (int k = resolution; k >= 0; --k) {
        float a = (2.0f * M_PI * k) / resolution + angleOffset;
        float ca = cosf(a);
        float sa = sinf(a);
        
        for (int j = 0; j < n; ++j) {
            float uComp = this->basisU[j] * ca;
            float vComp = this->basisV[j] * sa;
            result[idx++] = bottomCenter[j] + radius * (uComp + vComp);
        }
    }
    

    for (int k = 0; k <= resolution; ++k) {
        float a = (2.0f * M_PI * k) / resolution + angleOffset;
        float ca = cosf(a);
        float sa = sinf(a);
        
        for (int j = 0; j < n; ++j) {
            float uComp = this->basisU[j] * ca;
            float vComp = this->basisV[j] * sa;
            result[idx++] = topCenter[j] + radius * (uComp + vComp);
        }
        
        for (int j = 0; j < n; ++j) {
            float uComp = this->basisU[j] * ca;
            float vComp = this->basisV[j] * sa;
            result[idx++] = bottomCenter[j] + radius * (uComp + vComp);
        }
    }

    return result;
}

template<int n>
int Cylinder<n>::getNumPoints() const{
    int capVerts = 1 + (resolution + 1);
    int sideVerts = 2 * (resolution + 1);
    int totalVerts = capVerts + capVerts + sideVerts;
    return totalVerts * n;
}

template<int n>
void Cylinder<n>::draw(bool wireframe){
    if (this->VAO == 0u) this->createGLBuffers();

    int capVerts = 1 + (resolution + 1);
    int sideVerts = 2 * (resolution + 1);
    
    glBindVertexArray(this->VAO);
    glDisableVertexAttribArray(1);
    glVertexAttrib4f(1, this->colour[0], this->colour[1], this->colour[2], this->colour[3]);
    
    if (wireframe && this->EBO != 0u && this->lineIndexCount > 0) {
        glDrawElements(GL_LINES, this->lineIndexCount, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLE_FAN, 0, capVerts);
        glDrawArrays(GL_TRIANGLE_FAN, capVerts, capVerts);
        glDrawArrays(GL_TRIANGLE_STRIP, 2 * capVerts, sideVerts);
    }
    
    glBindVertexArray(0);
}

template<int n>
void Cylinder<n>::createGLBuffers(GLenum usage){
    Shape<n>::createGLBuffers(usage);
    
    int capVerts = 1 + (resolution + 1);
    int topCapCenter = 0;
    int topCapPerimStart = 1;
    int bottomCapCenter = capVerts;
    int bottomCapPerimStart = capVerts + 1;
    int sideStart = 2 * capVerts;

    std::vector<GLuint> indices;
    

    for (int k = 0; k <= resolution; ++k) {
        indices.push_back(static_cast<GLuint>(topCapCenter));
        indices.push_back(static_cast<GLuint>(topCapPerimStart + k));
    }
    
    for (int k = 0; k < resolution; ++k) {
        indices.push_back(static_cast<GLuint>(topCapPerimStart + k));
        indices.push_back(static_cast<GLuint>(topCapPerimStart + k + 1));
    }
    indices.push_back(static_cast<GLuint>(topCapPerimStart + resolution));
    indices.push_back(static_cast<GLuint>(topCapPerimStart));
    

    for (int k = 0; k <= resolution; ++k) {
        indices.push_back(static_cast<GLuint>(bottomCapCenter));
        indices.push_back(static_cast<GLuint>(bottomCapPerimStart + k));
    }
    
    for (int k = 0; k < resolution; ++k) {
        indices.push_back(static_cast<GLuint>(bottomCapPerimStart + k));
        indices.push_back(static_cast<GLuint>(bottomCapPerimStart + k + 1));
    }
    indices.push_back(static_cast<GLuint>(bottomCapPerimStart + resolution));
    indices.push_back(static_cast<GLuint>(bottomCapPerimStart));
    

    for (int k = 0; k < resolution; ++k) {
        GLuint topIdx = static_cast<GLuint>(sideStart + 2 * k);
        GLuint botIdx = static_cast<GLuint>(sideStart + 2 * k + 1);
        indices.push_back(topIdx);
        indices.push_back(botIdx);
    }
    
    this->setLineIndices(indices);
}

template<int n>
GLenum Cylinder<n>::glDrawMode() const {
    return GL_TRIANGLE_STRIP;
}

template<int n>
void Cylinder<n>::print() const{
    std::cout << "_ Center _ " << std::endl;
    center.print();
    std::cout << "_ Radius _ " << std::endl;
    std::cout << radius << std::endl;
    std::cout << "_ Height _ " << std::endl;
    std::cout << height << std::endl;
}

template<int n>
void Cylinder<n>::zoom(int percent){
    float factor = percent / 100.0f;
    radius *= factor;
    height *= factor;
}

template<int n>
void Cylinder<n>::rotate(int degrees){
    float delta = (float)degrees * (float)M_PI / 180.0f;
    angleOffset += delta;
    if (angleOffset > 2.0f * M_PI || angleOffset < -2.0f * M_PI) {
        angleOffset = fmodf(angleOffset, 2.0f * M_PI);
    }
}

template<int n>
std::string Cylinder<n>::fprint() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6);
    for (int i = 0; i < n; ++i) ss << center[i] << ' ';
    ss << radius << ' ' << height << ' ' << resolution << ' ' << angleOffset << ' ';
    int r = (int)roundf(this->colour[0]*255.0f);
    int g = (int)roundf(this->colour[1]*255.0f);
    int b = (int)roundf(this->colour[2]*255.0f);
    ss << r << ' ' << g << ' ' << b << ' ' << this->colour[3];
    return ss.str();
}
