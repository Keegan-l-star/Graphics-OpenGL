
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
    p1=Vector<n>(m*(Matrix<n,1>)p1);
    p2=Vector<n>(m*(Matrix<n,1>)p2);
    p3=Vector<n>(m*(Matrix<n,1>)p3);
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

