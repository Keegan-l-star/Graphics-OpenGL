
template <int n>
Square<n>::Square(const Vector<n>& center, float height, float width){
    tl=Vector<n>(center);
    tr=Vector<n>(center);
    br=Vector<n>(center);
    bl=Vector<n>(center);
    tl[0]-=width/2;
    tl[1]+=height/2;
    tr[0]+=width/2;
    tr[1]+=height/2;
    br[0]+=width/2;
    br[1]-=height/2;
    bl[0]-=width/2;
    bl[1]-=height/2;
}

template <int n>
Square<n>::Square(const Vector<n>& tl, const Vector<n>& tr, const Vector<n>& br, const Vector<n>& bl){
    this->tl=tl;
    this->tr=tr;
    this->br=br;
    this->bl=bl;
}

template <int n>
Square<n>::Square(const Square<n> &two){
    this->tl=two.tl;
    this->tr=two.tr;
    this->br=two.br;
    this->bl=two.bl;
}

template <int n>
Square<n>& Square<n>::operator*=(const Matrix<n,n> &m){
    Matrix<n,1> htl = (Matrix<n,1>)tl;
    Matrix<n,1> htr = (Matrix<n,1>)tr;
    Matrix<n,1> hbr = (Matrix<n,1>)br;
    Matrix<n,1> hbl = (Matrix<n,1>)bl;

    if (n == 3) {
        htl[2][0] = 1.0f;
        htr[2][0] = 1.0f;
        hbr[2][0] = 1.0f;
        hbl[2][0] = 1.0f;
    }

    tl = Vector<n>(m * htl);
    tr = Vector<n>(m * htr);
    br = Vector<n>(m * hbr);
    bl = Vector<n>(m * hbl);

    if (n == 3) {
        tl[2] = 0.0f;
        tr[2] = 0.0f;
        br[2] = 0.0f;
        bl[2] = 0.0f;
    }
    return *this;
}

template <int n>
Square<n>* Square<n>::operator*(const Matrix<n,n> &m) const{
    Square<n>* result=new Square<n>(*this);
    *result*=m;
    return result;
}

template <int n>
float* Square<n>::getPoints() const{
    float* result=new float[4*n];
    int total=0;
    for(int i=0;i<n;i++){
        result[i]=tl[i];
        total++;
    }
    for(int i=0;i<n;i++){
        result[total]=tr[i];
        total++;
    }
    for(int i=0;i<n;i++){
        result[total]=br[i];
        total++;
    }
    for(int i=0;i<n;i++){
        result[total]=bl[i];
        total++;
    }
    return result;
}

template <int n>
int Square<n>::getNumPoints() const{
    return 4*n;
}

template<int n>
void Square<n>::zoom(int percent){
    float factor = percent / 100.0f;
    tl = tl * factor;
    tr = tr * factor;
    br = br * factor;
    bl = bl * factor;
}
