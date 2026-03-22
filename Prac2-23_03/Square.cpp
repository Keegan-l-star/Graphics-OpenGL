

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
        {
            float* c = two.getColour();
            for (int i = 0; i < 4; ++i) this->colour[i] = c[i];
            delete[] c;
        }
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
    // compute centroid
    Vector<n> center;
    for (int i = 0; i < n; ++i) {
        center[i] = (tl[i] + tr[i] + br[i] + bl[i]) / 4.0f;
    }

    // translate to origin, scale, translate back
    *this *= translation<n>(-center[0], -center[1], 0.0f);
    *this *= scaling<n>(factor);
    *this *= translation<n>(center[0], center[1], 0.0f);
}

template<int n>
void Square<n>::rotate(int degrees){
    // compute centroid
    Vector<n> center;
    for (int i = 0; i < n; ++i) {
        center[i] = (tl[i] + tr[i] + br[i] + bl[i]) / 4.0f;
    }

    // rotate about centroid: translate -> rotate -> translate back
    *this *= translation<n>(-center[0], -center[1], 0.0f);
    *this *= rotz<n>(degrees);
    *this *= translation<n>(center[0], center[1], 0.0f);
}

template<int n>
std::string Square<n>::fprint() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6);
    float* pts = getPoints();
    for (int i = 0; i < 12; ++i) ss << pts[i] << ' ';
    delete[] pts;
    int r = (int)roundf(this->colour[0]*255.0f);
    int g = (int)roundf(this->colour[1]*255.0f);
    int b = (int)roundf(this->colour[2]*255.0f);
    ss << r << ' ' << g << ' ' << b << ' ' << this->colour[3];
    return ss.str();
}
