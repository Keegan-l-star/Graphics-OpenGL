
template<int n>
Triangle<n>::Triangle(const Vector<n>& p1, const Vector<n>& p2, const Vector<n>& p3){
    this->p1=p1;
    this->p2=p2;
    this->p3=p3;
}

template<int n>
Triangle<n>::Triangle(const Triangle<n> &t){
    this->p1 = t.p1;
    this->p2 = t.p2;
    this->p3 = t.p3;
}

template<int n>
Triangle<n>& Triangle<n>::operator*=(const Matrix<n,n> &m){
    Matrix<n,1> hp1 = (Matrix<n,1>)p1;
    Matrix<n,1> hp2 = (Matrix<n,1>)p2;
    Matrix<n,1> hp3 = (Matrix<n,1>)p3;

    if (n == 3) {
        hp1[2][0] = 1.0f;
        hp2[2][0] = 1.0f;
        hp3[2][0] = 1.0f;
    }

    p1 = Vector<n>(m * hp1);
    p2 = Vector<n>(m * hp2);
    p3 = Vector<n>(m * hp3);

    if (n == 3) {
        p1[2] = 0.0f;
        p2[2] = 0.0f;
        p3[2] = 0.0f;
    }
    return *this;
}

template<int n>
Triangle<n>* Triangle<n>::operator*(const Matrix<n,n> &m) const{
    Triangle<n>* result=new Triangle<n>(*this);
    *result*=m;
    return result;
}

template<int n>
float* Triangle<n>::getPoints() const{
    float* result=new float[3*n];
    int total=0;
    for(int i=0;i<n;i++){
        result[i]=p1[i];
        total++;
    }
    for(int i=0;i<n;i++){
        result[total]=p2[i];
        total++;
    }
    for(int i=0;i<n;i++){
        result[total]=p3[i];
        total++;
    }
    return result;
}

template<int n>
int Triangle<n>::getNumPoints() const{
    return 3*n;
}

template<int n>
void Triangle<n>::zoom(int percent){
    float factor = percent / 100.0f;
    p1 = p1 * factor;
    p2 = p2 * factor;
    p3 = p3 * factor;
}

