template <int n>
Vector<n>::Vector()
{
    arr = new float[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = (float)0.0;
    }
}

template <int n>
Vector<n>::Vector(std::initializer_list<float> list){
    arr=new float[n];
    int i=0;
    for(float element:list){
        if(i>=n){
            return;
        }
        arr[i]=element;
        i++;
    }
    if(i<n){
        for(;i<n;i++){
            arr[i]=(float)0.0;
        }
    }
}

template <int n>
Vector<n>::Vector(float *arr){
    this->arr=arr;
}

template <int n>
Vector<n>::~Vector(){
    delete[] arr;
}

template <int n>
Vector<n>::Vector(const Vector<n> &v){
    arr=new float[n];
    for(int i=0;i<n;i++){
        arr[i]=v.arr[i];
    }
}

template <int n>
Vector<n>::Vector(const Matrix<n,1> &m){
    arr=new float[n];
    for(int i=0;i<n;i++){
        arr[i]=m[i][0];
    }
}

template <int n>
Vector<n>& Vector<n>::operator=(const Vector<n> &v){
    if(this==&v){
        return *this;
    }
    delete[] arr;
    arr=new float[n];
    for(int i=0;i<n;i++){
        arr[i]=v.arr[i];
    }
    return *this;
}

template <int n>
Vector<n> Vector<n>::operator+(const Vector<n> v) const{
    Vector<n> result;
    for(int i=0;i<n;i++){
        result.arr[i]=arr[i]+v.arr[i];
    }
    return result;
}

template <int n>
Vector<n> Vector<n>::operator-(const Vector<n> v) const{
    Vector<n> result;
    for(int i=0;i<n;i++){
        result.arr[i]=arr[i]-v.arr[i];
    }
    return result;
}

template <int n>
int Vector<n>::getN() const{
    return n;
}

template <int n>
Vector<n>::operator Matrix<n,1>() const{
    Matrix<n,1> result;
    for(int i=0;i<n;i++){
        result[i][0]=arr[i];
    }
    return result;
}

template <int n>
Vector<n> Vector<n>::unitVector() const{
    float mag=magnitude();
    if(mag==0){
        throw "Invalid unit vector";
    }
    Vector<n> result;
    for(int i=0;i<n;i++){
        result.arr[i]=arr[i]/mag;//divides all entries of the vector by the magnitude that is how
        //the unit vector is calculated.
    }
    return result;
}

template <int n>
float Vector<n>::magnitude() const{
    float sum=0.0;
    for(int i=0;i<n;i++){
        sum+=arr[i]*arr[i];
    }
    return sqrt(sum);
}

template <int n>
Vector<3> Vector<n>::crossProduct(const Vector<3> v) const{
    Vector<3> result;
    result[0]=(arr[1]*v.arr[2])-(arr[2]*v.arr[1]);
    result[1]=(arr[2]*v.arr[0])-(arr[0]*v.arr[2]);
    result[2]=(arr[0]*v.arr[1])-(arr[1]*v.arr[0]);
    return result;
}

template <int n>
Vector<n> Vector<n>::operator*(const float scalar) const{
    Vector<n> result;
    for(int i=0;i<n;i++){
        result.arr[i]=arr[i]*scalar;
    }
    return result;
}

template <int n>
float Vector<n>::operator*(const Vector<n> v) const{
    float result=0.0;
    for(int i=0;i<n;i++){
        result+=arr[i]*v.arr[i];
    }
    return result;
}