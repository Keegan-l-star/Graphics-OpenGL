template <int n>
void Shape<n>::setColour(int r, int g, int b, float a){
    color[0]=r/255.0f;
    color[1]=g/255.0f;
    color[2]=b/255.0f;
    color[3]=a;
}

template <int n>
float* Shape<n>::getColour() const{
    float* result=new float[4];
    result[0]=color[0];
    result[1]=color[1];
    result[2]=color[2];
    result[3]=color[3];
    return result;
}



