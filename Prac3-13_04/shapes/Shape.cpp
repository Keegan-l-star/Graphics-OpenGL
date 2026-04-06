template <int n>
void Shape<n>::setColour(int r, int g, int b, float a){
    colour[0]=r/255.0f;
    colour[1]=g/255.0f;
    colour[2]=b/255.0f;
    colour[3]=a;
}

template <int n>
float* Shape<n>::getColour() const{
    float* result = new float[4];
    result[0] = colour[0];
    result[1] = colour[1];
    result[2] = colour[2];
    result[3] = colour[3];
    return result;
}

template <int n>
Shape<n>::Shape(const Shape& other) {
    for (int i = 0; i < 4; ++i) this->colour[i] = other.colour[i];

    VAO = 0u; VBO = 0u; EBO = 0u;
    vertexCount = other.vertexCount;
    lineIndexCount = 0;
}

template <int n>
Shape<n>& Shape<n>::operator=(const Shape& other) {
    if (this != &other) {

        deleteGLBuffers();
        for (int i = 0; i < 4; ++i) this->colour[i] = other.colour[i];
        VAO = 0u; VBO = 0u; EBO = 0u;
        vertexCount = other.vertexCount;
        lineIndexCount = 0;
    }
    return *this;
}

template <int n>
Shape<n>::Shape(Shape&& other) noexcept {
    for (int i = 0; i < 4; ++i) this->colour[i] = other.colour[i];
    // steal GL handles
    VAO = other.VAO; VBO = other.VBO; EBO = other.EBO;
    vertexCount = other.vertexCount;
    lineIndexCount = other.lineIndexCount;
    other.VAO = other.VBO = other.EBO = 0u;
    other.vertexCount = 0;
    other.lineIndexCount = 0;
}

template <int n>
Shape<n>& Shape<n>::operator=(Shape&& other) noexcept {
    if (this != &other) {
        deleteGLBuffers();
        for (int i = 0; i < 4; ++i) this->colour[i] = other.colour[i];
        VAO = other.VAO; VBO = other.VBO; EBO = other.EBO;
        vertexCount = other.vertexCount;
        lineIndexCount = other.lineIndexCount;
        other.VAO = other.VBO = other.EBO = 0u;
        other.vertexCount = 0;
        other.lineIndexCount = 0;
    }
    return *this;
}

template <int n>
void Shape<n>::createGLBuffers(GLenum usage){
    if (VAO == 0u) glGenVertexArrays(1, &VAO);
    if (VBO == 0u) glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float* pts = getPoints();
    int numFloats = getNumPoints();
    // Validate vertex data for NaN/Inf to catch corrupt transforms early
    for (int i = 0; i < numFloats; ++i) {
        if (!std::isfinite(pts[i])) {
            std::cerr << "Shape::createGLBuffers(): invalid vertex data (NaN/Inf) at index " << i << "\n";
            delete[] pts;
            return;
        }
    }
    int verts = 0;
    if (n > 0) verts = numFloats / n;

    glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), pts, usage);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, n * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    delete[] pts;
    vertexCount = verts;

    glBindVertexArray(0);
}

template <int n>
void Shape<n>::updateGLBuffers(GLenum usage){
    if (VBO == 0u) return;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float* pts = getPoints();
    int numFloats = getNumPoints();
    // Validate vertex data before uploading
    for (int i = 0; i < numFloats; ++i) {
        if (!std::isfinite(pts[i])) {
            std::cerr << "Shape::updateGLBuffers(): invalid vertex data (NaN/Inf) at index " << i << "\n";
            delete[] pts;
            return;
        }
    }
    glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), nullptr, usage);
    glBufferSubData(GL_ARRAY_BUFFER, 0, numFloats * sizeof(float), pts);
    delete[] pts;
}

template <int n>
void Shape<n>::deleteGLBuffers(){
    if (EBO != 0u) { glDeleteBuffers(1, &EBO); EBO = 0u; }
    if (VBO != 0u) { glDeleteBuffers(1, &VBO); VBO = 0u; }
    if (VAO != 0u) { glDeleteVertexArrays(1, &VAO); VAO = 0u; }
    vertexCount = 0;
}

template <int n>
void Shape<n>::setLineIndices(const std::vector<GLuint>& indices) {
    if (VAO == 0u) return;
    
    if (EBO == 0u) glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    
    lineIndexCount =indices.size();
    glBindVertexArray(0);
}

template <int n>
void Shape<n>::draw(bool wireframe){
    if (VAO == 0u){
        return;
    }
    glBindVertexArray(VAO);
    glDisableVertexAttribArray(1);
    glVertexAttrib4f(1, colour[0], colour[1], colour[2], colour[3]);
    
    if (wireframe && EBO != 0u && lineIndexCount > 0) {
        glDrawElements(GL_LINES, lineIndexCount, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(glDrawMode(), 0, vertexCount);
    }
    
    glBindVertexArray(0);
}

template <int n>
Shape<n>::~Shape() {
    deleteGLBuffers();
}




