template <int n>
void Shape<n>::setColour(int r, int g, int b, float a){
    colour[0]=r/255.0f;
    colour[1]=g/255.0f;
    colour[2]=b/255.0f;
    colour[3]=a;
}

template <int n>
float* Shape<n>::getColour() const{
    float* result=new float[4];
    result[0]=colour[0];
    result[1]=colour[1];
    result[2]=colour[2];
    result[3]=colour[3];
    return result;
}



