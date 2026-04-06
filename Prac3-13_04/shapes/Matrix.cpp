//#include "Matrix.h";

template<int n,int m>
Matrix<n,m>::Matrix(){
    arr=new float*[n];
    for(int i=0;i<n;i++){
        arr[i]=new float[m];
        for(int j=0;j<m;j++){
            arr[i][j]=(float)0.0;
        }
    }
}

template<int n,int m>
Matrix<n,m>::Matrix(float **arr){
    this->arr=arr;
}

template<int n,int m>
Matrix<n,m>::Matrix(const Matrix<n,m> &f){
    arr=new float*[n];
    for(int i=0;i<n;i++){
        arr[i]=new float[m];
        for(int j=0;j<m;j++){
            arr[i][j]=f[i][j];
        }
    }
}

template<int n,int m>
Matrix<n,m>::~Matrix(){
    for(int i=0;i<n;i++){
        delete[] arr[i];
    }
    delete[] arr;
}

template<int n,int m>
int Matrix<n,m>::getN() const{
    return n;
}

template<int n,int m>
int Matrix<n,m>::getM() const{
    return m;
}

template<int n,int m>
Matrix<n,m>& Matrix<n,m>::operator=(const Matrix<n,m> &f){
    if(this==&f){
        return *this;
    }
    for(int i=0;i<n;i++){
        delete[] arr[i];
    }
    delete[] arr;
    arr=new float*[n];
    for(int i=0;i<n;i++){
        arr[i]=new float[m];
        for(int j=0;j<m;j++){
            arr[i][j]=f.arr[i][j];
        }
    }
    return *this;
}

template<int n,int m>
template<int a>
Matrix<n,a> Matrix<n,m>::operator*(const Matrix<m,a> f) const{
    Matrix<n,a> result;//This is the new constructor with the new size 
    //arr[i][j]
    for (int i=0;i<n;i++){
        //arr[i][?]
        for(int j=0;j<a;j++){
            //f.arr[?][j]
            for(int k=0;k<m;k++){
                //k=?, eish this took me a long time looking and my notebook
                result[i][j]+=(arr[i][k]*f[k][j]);
            }
        }
    }
    return result;
}

template<int n,int m>
Matrix<n,m> Matrix<n,m>::operator*(const float s) const{
    Matrix<n,m> result;
    for(int i=0;i<n; i++){
        for(int j=0; j<m; j++){
            result[i][j]=arr[i][j]*s;
        }
    }
    return result;
}

template<int n,int m>
Matrix<n,m> Matrix<n,m>::operator+(const Matrix<n,m> b)const{
    Matrix<n,m> result;
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
            result[i][j]=arr[i][j]+b[i][j];
        }
    }
    return result;
}

template <int n,int m>
Matrix<m,n> Matrix<n,m>::operator~() const{
    Matrix<m,n> result;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            result[j][i]=arr[i][j];
        }
    }
    return result;
}

template<>
inline
float Matrix<1,1>::determinant() const{
    return arr[0][0];
}

template<>
inline
float Matrix<2,2>::determinant() const{
    return (arr[0][0]*arr[1][1])-(arr[0][1]*arr[1][0]);
}  

template<int n,int m>
inline
float Matrix<n,m>::determinant() const{
    if(n!=m){
        throw "Matrix is not square";
    }else{
        float result=0.0;
        for(int i=0;i<m;i++){
            result+=arr[0][i]*pow(-1,i)*submatrix(*this,0,i).determinant();
        }
        return result;
    }
}

template<int n, int m>
Matrix<n-1, m-1> submatrix(const Matrix<n, m>& mat, int ignrRow, int ignrCol) {
    Matrix<n-1, m-1> result;
    int resI = 0;
    for (int i = 0; i < n; i++) {
        if(i == ignrRow) {
            continue;
        }
        int resJ = 0;
        for (int j = 0; j < m; j++) {
            if(j == ignrCol) {
                continue;
            }
            result[resI][resJ] = mat[i][j];
            resJ++;
        }
        resI++;
    }
    return result;
}



    