#include "Matrix.h"
#include "Vector.h"
#include "Shape.h"
#include "Triangle.h"
#include "Square.h"
#include <cmath>

#include <iostream>

#include <sstream>

using namespace std;
int main(int argc, char const *argv[])
{
    /*
    cout << "========== VECTOR TESTS ==========" << endl;
    
    // Create vectors
    Vector<3> v1{1, 2, 3};
    Vector<3> v2{4, 5, 6};
    
    cout << "Vector v1: \n";
    v1.print();
    cout << "Vector v2: \n";
    v2.print();
    
    // Vector operations
    Vector<3> v_sum = v1 + v2;
    cout << "v1 + v2: \n";
    v_sum.print();
    
    Vector<3> v_diff = v1 - v2;
    cout << "v1 - v2: \n";
    v_diff.print();
    
    Vector<3> v_scaled = v1 * (float)2.0;
    cout << "v1 * 2: \n";
    v_scaled.print();
    
    float dot = v1 * v2;
    cout << "v1 dot v2 = " << dot << endl;
    
    cout << "v1 magnitude = " << v1.magnitude() << endl;
    cout << "v1 unit vector: \n";
    v1.unitVector().print();
    
    cout << endl << "========== MATRIX TESTS ==========" << endl;
    
    // Create 2x2 matrix
    Matrix<2,2> m1;
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;
    
    cout << "Matrix m1: \n" << endl;
    m1.print();
    
    // Test matrix multiplication
    Vector<2> vec{1, 1};
    Matrix<2,1> vec_matrix = (Matrix<2,1>)vec;
    cout << "\nVector as matrix: \n" << endl;
    vec_matrix.print();

    Vector<2> result_vec{2,3};

    Matrix<2,1> row_Mat = (Matrix<2,1>)result_vec;
    cout << "\nRow Matrix: \n" << endl;
    row_Mat.print();

    cout<< "\nm1 * vec_matrix: \n" << endl;
    Matrix<2,1> m_vec_result = m1 * vec_matrix;
    m_vec_result.print();

    cout << "\nm1 * 2: \n" << endl;
    Matrix<2,2> m_scaled = m1 * (float)2.0;
    m_scaled.print();

    cout<<"\nm1 + m1: \n" << endl;
    Matrix<2,2> m_sum = m1 + m1;
    m_sum.print();

    cout<< "\nTranspose of m1: \n" << endl;
    Matrix<2,2> m_transpose = ~m1;
    m_transpose.print();

    cout<< "Determinant of m1: " << m1.determinant() << endl;



    
    cout << endl << "========== TRIANGLE TESTS ==========" << endl;
    
    // Create triangle
    Vector<3> p1{0, 0, 0};
    Vector<3> p2{1, 0, 0};
    Vector<3> p3{0, 1, 0};
    
    Triangle<3> t1(p1, p2, p3);
    cout << "Triangle t1: \n" << endl;
    t1.print();
    
    // Copy constructor
    Triangle<3> t2(t1);
    cout << "Triangle t2 (copy of t1): \n" << endl;
    t2.print();
    
    // Get points
    float* points = t1.getPoints();
    cout << "Triangle points array: \n";
    for(int i = 0; i < 9; i++) {
        cout << points[i] << " ";
    }
    cout << endl;
    delete[] points;
    
    cout << endl << "========== SQUARE TESTS ==========" << endl;
    
    // Create square
    Vector<3> tl{0, 1, 0};
    Vector<3> tr{1, 1, 0};
    Vector<3> br{1, 0, 0};
    Vector<3> bl{0, 0, 0};
    
    Square<3> s1(tl, tr, br, bl);
    cout << "Square s1: \n" << endl;
    s1.print();
    
    // Copy constructor
    Square<3> s2(s1);
    cout << "Square s2 (copy of s1): \n" << endl;
    s2.print();
    
    // Get points
    float* sq_points = s1.getPoints();
    cout << "Square points array: \n";
    for(int i = 0; i < 12; i++) {
        cout << sq_points[i] << " ";
    }
    cout << endl;
    delete[] sq_points;
    
    cout << endl << "========== TRANSFORMATION TESTS ==========" << endl;
    
    // Create transformation matrix (scale by 2)
    Matrix<3,3> scale;
    scale[0][0] = 2; scale[0][1] = 0; scale[0][2] = 0;
    scale[1][0] = 0; scale[1][1] = 2; scale[1][2] = 0;
    scale[2][0] = 0; scale[2][1] = 0; scale[2][2] = 2;
    
    cout << "Scale matrix: \n" << endl;
    scale.print();
    
    // Transform triangle
    Triangle<3>* t_scaled = t1 * scale;
    cout << "Scaled triangle: \n" << endl;
    t_scaled->print();
    
    // Transform square
    Square<3>* s_scaled = s1 * scale;
    cout << "Scaled square: \n" << endl;
    s_scaled->print();

    cout<< endl<<"========= Determinant Tests ==========" << endl;
    Matrix<3,3> m2;
    m2[0][0]=5; m2[0][1]=9; m2[0][2]=-4;
    m2[1][0]=-6; m2[1][1]=-8; m2[1][2]=-2;
    m2[2][0]=9; m2[2][1]=-5; m2[2][2]=4;

    cout<< "Matrix m2: \n" << endl;
    m2.print();
    
    cout<< "Determinant of m2: " << m2.determinant() << endl;   
    cout << endl << "========== TEST COMPLETE ==========" << endl;

    */

    /*

    //Create 3D triangle
    Vector<3> A{5, 7, 1};
    Vector<3> B{9, 7, 4};
    Vector<3> C{2, 2, 10};

    Triangle<3> t1(A, B, C);
    cout << "Triangle t1: \n" << endl;

    Vector<3> circle_centre{10, 10, 9};
    float rad = 1.9f;

    Vector<3> ray_origin{8,0,6};
    Vector<3> ray_direction{0.14,0.95,-0.27};

    //Triangle intersection test
    Vector<3> edge1 = B - A;
    std::cout << "AB: " << std::endl;
    edge1.print();
    Vector<3> edge2 = C - A;
    std::cout << "AC: " << std::endl;
    edge2.print();
    Vector<3> n = edge1.crossProduct(edge2);
    std::cout << "n: " << std::endl;
    n.print();

    //Plane intersection test
    float top= n*(A- ray_origin);
    float bottom = n*ray_direction;
    float t = top/bottom;
    std::cout << "t: " << t << std::endl;   

    //Intersection point
    Vector<3> P = ray_origin + (ray_direction*t);
    std::cout << "Intersection point P: " << std::endl;
    P.print();

    //Direction toward centre:
    std::cout << "Sphere ray direction: " << std::endl;
    Vector<3> dir_to_centre = circle_centre - ray_origin;
    dir_to_centre.print();

    //Number of intersections for ray from P toward circle centre:
    Vector<3> holder1 = P - circle_centre;
    float a_q = dir_to_centre * dir_to_centre;
    float b_q = 2.0f * (holder1 * dir_to_centre);
    float c_q = (holder1 * holder1) - (rad * rad);

    float discriminant = (b_q * b_q) - (4.0f * a_q * c_q);
    const float EPS = 1e-6f;
    int intersections = 0;

    if (discriminant > EPS)
    {
        float sqrtDisc = std::sqrt(discriminant);
        float t0 = (-b_q - sqrtDisc) / (2.0f * a_q);
        float t1 = (-b_q + sqrtDisc) / (2.0f * a_q);

        if (t0 >= 0.0f)
        {
            intersections++;
        }
        if (t1 >= 0.0f)
        {
            intersections++;
        }
    }
    else if (std::fabs(discriminant) <= EPS)
    {
        float t_tangent = -b_q / (2.0f * a_q);
        if (t_tangent >= 0.0f)
        {
            intersections = 1;
        }
    }

    std::cout << "Number of intersections: " << intersections << std::endl;

    // Colour compositing example: T is in front of S
    Vector<3> T_colour{0.6f, 0.4f, 0.4f};
    Vector<3> S_colour{0.6f, 0, 1};
    float alpha_T = 0.2f;
    Vector<3> seen_colour = (T_colour * alpha_T) + (S_colour * (1.0f - alpha_T));

    std::cout << "Seen colour (RGB): " << std::endl;
    seen_colour.print();
    

    Vector<3> a{0.2,0.8,0};
    Vector<3> b{-0.1,0.1,0};
    Vector<3> c{0.3,0.6,0};
    Vector<3> Light_source{1.8,1.7,1.5};

    //Normal
    Vector<3> result_n = (b - a).crossProduct(c - a);
    std::cout << "Normal vector: " << std::endl;
    result_n.print();

    Vector<3> VECTOR_R= Light_source - a;
    float scalar_r= VECTOR_R.magnitude();
    std::cout << "Scalar r: " << scalar_r << std::endl;


    std::cout<<"Normalise l:"<<std::endl;
    std::cout<<"Before normalisation: "<<std::endl;
    VECTOR_R.print();
    VECTOR_R = VECTOR_R * (1.0f / scalar_r);
    std::cout<<"After normalisation: "<<std::endl;
    VECTOR_R.print();

    std::cout<<"n dot l: "<<std::endl;
    std::cout<<result_n * VECTOR_R<<std::endl;


    float p= 8;
    float value = std::pow(std::max(0.0f, result_n * VECTOR_R / (scalar_r * scalar_r)), p);

    std::cout << "Final form: " << value << std::endl;

    */

    /*
    std::cout<<"=========Transformations and shaders========="<<std::endl;
    int angle=284;
    Vector<3> point{4,4,9};
    Vector<3> T={1,4,2};

    Vector<3> axisP1{1,4,2};
    Vector<3> axisP2{8,8,10};

    std::cout<<"Directional vector of rotation axis: "<<std::endl;
    Vector<3> axisDir = axisP2 - axisP1;
    axisDir.print();

    std::cout<<"Normalise directional vector: "<<std::endl;
    float axisLength = axisDir.magnitude();
    std::cout<<"Axis length: "<<axisLength<<std::endl;
    Vector<3> axisUnit = axisDir * (1.0f / axisLength);
    std::cout<<"\nAxis unit vector: "<<std::endl;
    axisUnit.print();

    std::cout<<"\nCentre of the object: "<<std::endl;
    
    T.print();

    std::cout<<"\nTranslation matricx to move centre to origin: "<<std::endl;
    Matrix<4,4> MT;
    MT[0][0] = 1; MT[0][1] = 0; MT[0][2] = 0; MT[0][3] = -T[0];
    MT[1][0] = 0; MT[1][1] = 1; MT[1][2] = 0; MT[1][3] = -T[1];
    MT[2][0] = 0; MT[2][1] = 0; MT[2][2] = 1; MT[2][3] = -T[2];
    MT[3][0] = 0; MT[3][1] = 0; MT[3][2] = 0; MT[3][3] = 1;
    MT.print();

    std::cout<<"\nlength of Projection when x=0"<<std::endl;
    float squared= axisLength*axisLength;
    float projLength = sqrt(((axisDir[1]*axisDir[1])/(squared))+((axisDir[2]*axisDir[2])/(squared)));
    std::cout<<projLength<<std::endl;

    std::cout<<"\nRotation matrix around arbitrary axis: "<<std::endl;
    float radian = angle * M_PI / 180.0f;

    float c = cos(radian);
    float s = sin(radian);
    float nc = cos(-radian);
    float ns = sin(-radian);

    Matrix<4,4> RY;
    RY[0][0] = projLength; RY[0][1] = 0; RY[0][2] = axisUnit[0]; RY[0][3] = 0;
    RY[1][0] = 0; RY[1][1] = 1; RY[1][2] = 0; RY[1][3] = 0;
    RY[2][0] = -axisUnit[0]; RY[2][1] = 0; RY[2][2] = projLength; RY[2][3] = 0;
    RY[3][0] = 0; RY[3][1] = 0; RY[3][2] = 0; RY[3][3] = 1;

    Matrix<4,4> RY_inv;
    RY_inv[0][0] = projLength; RY_inv[0][1] = 0; RY_inv[0][2] = -axisUnit[0]; RY_inv[0][3] = 0;
    RY_inv[1][0] = 0; RY_inv[1][1] = 1; RY_inv[1][2] = 0; RY_inv[1][3] = 0;
    RY_inv[2][0] = axisUnit[0]; RY_inv[2][1] = 0; RY_inv[2][2] = projLength; RY_inv[2][3] = 0;
    RY_inv[3][0] = 0; RY_inv[3][1] = 0; RY_inv[3][2] = 0; RY_inv[3][3] = 1;

    float cosX = axisUnit[2] / projLength;
    float sinX = axisUnit[1] / projLength;

    Matrix<4,4> RX;
    RX[0][0] = 1; RX[0][1] = 0; RX[0][2] = 0; RX[0][3] = 0;
    RX[1][0] = 0; RX[1][1] = cosX; RX[1][2] = -sinX; RX[1][3] = 0;
    RX[2][0] = 0; RX[2][1] = sinX; RX[2][2] = cosX; RX[2][3] = 0;
    RX[3][0] = 0; RX[3][1] = 0; RX[3][2] = 0; RX[3][3] = 1;

    std::cout<<"final R_x(theta_x)\n";
    RX.print();
    std::cout<<"\n the opp\n";
    

    Matrix<4,4> RX_inv;
    RX_inv[0][0] = 1; RX_inv[0][1] = 0; RX_inv[0][2] = 0; RX_inv[0][3] = 0;
    RX_inv[1][0] = 0; RX_inv[1][1] = cosX; RX_inv[1][2] = sinX; RX_inv[1][3] = 0;
    RX_inv[2][0] = 0; RX_inv[2][1] = -sinX; RX_inv[2][2] = cosX; RX_inv[2][3] = 0;
    RX_inv[3][0] = 0; RX_inv[3][1] = 0; RX_inv[3][2] = 0; RX_inv[3][3] = 1;
    RX_inv.print();
    std::cout<<"\n";

    std::cout<<"\n";
    Matrix<4,4> RZ;
    RZ[0][0] = c; RZ[0][1] = -s; RZ[0][2] = 0; RZ[0][3] = 0;
    RZ[1][0] = s; RZ[1][1] = c; RZ[1][2] = 0; RZ[1][3] = 0;
    RZ[2][0] = 0; RZ[2][1] = 0; RZ[2][2] = 1; RZ[2][3] = 0;
    RZ[3][0] = 0; RZ[3][1] = 0; RZ[3][2] = 0; RZ[3][3] = 1;

    Matrix<4,4> MTT;
    MTT[0][0] = 1; MTT[0][1] = 0; MTT[0][2] = 0; MTT[0][3] = T[0];
    MTT[1][0] = 0; MTT[1][1] = 1; MTT[1][2] = 0; MTT[1][3] = T[1];
    MTT[2][0] = 0; MTT[2][1] = 0; MTT[2][2] = 1; MTT[2][3] = T[2];
    MTT[3][0] = 0; MTT[3][1] = 0; MTT[3][2] = 0; MTT[3][3] = 1;

    Matrix<4,4> R = MTT * RX_inv * RY_inv * RZ * RY * RX * MT;
    R.print();

    
    float scale_x=0.5;
    float scale_y=0.4f;
    float scale_z=0.9f;
    std::cout<<"\nTranslation matrix for scaling: "<<scale_x<<" units on x axis"<<scale_y<<" units on y axis"<<scale_z<<" units on z axis"<<std::endl;
    Matrix<4,4> scaling;
    scaling[0][0] = scale_x; scaling[0][1] = 0; scaling[0][2] = 0; scaling[0][3] = 0;
    scaling[1][0] = 0; scaling[1][1] = scale_y; scaling[1][2] = 0; scaling[1][3] = 0;
    scaling[2][0] = 0; scaling[2][1] = 0; scaling[2][2] = scale_z; scaling[2][3] = 0;
    scaling[3][0] = 0; scaling[3][1] = 0; scaling[3][2] = 0; scaling[3][3] = 1;
    scaling.print();

    int degrees=103;
    float radians = degrees * M_PI / 180.0f;
    std::cout<<"\nTranslation matrix for rotating about the y: "<<degrees<<" degrees"<<std::endl;
    Matrix<4,4> rotY;
    rotY[0][0] = cos(radians); rotY[0][1] = 0; rotY[0][2] = sin(radians); rotY[0][3] = 0;
    rotY[1][0] = 0; rotY[1][1] = 1; rotY[1][2] = 0; rotY[1][3] = 0;
    rotY[2][0] = -sin(radians); rotY[2][1] = 0; rotY[2][2] = cos(radians); rotY[2][3] = 0;
    rotY[3][0] = 0; rotY[3][1] = 0; rotY[3][2] = 0; rotY[3][3] = 1;
    rotY.print();

    std::cout<<"\nRotation matric for rotating about the z: "<<degrees<<" degrees"<<std::endl;
    Matrix<4,4> R_Z;
    R_Z[0][0] = cos(radians); R_Z[0][1] = -sin(radians); R_Z[0][2] = 0; R_Z[0][3] = 0;
    R_Z[1][0] = sin(radians); R_Z[1][1] = cos(radians); R_Z[1][2] = 0; R_Z[1][3] = 0;
    R_Z[2][0] = 0; R_Z[2][1] = 0; R_Z[2][2] = 1; R_Z[2][3] = 0;
    R_Z[3][0] = 0; R_Z[3][1] = 0; R_Z[3][2] = 0; R_Z[3][3] = 1;
    R_Z.print();

    std::cout<<"\nRotation matric for rotating about the x: "<<degrees<<" degrees"<<std::endl;  
    Matrix<4,4> R_X;
    R_X[0][0] = 1; R_X[0][1] = 0; R_X[0][2] = 0; R_X[0][3] = 0;
    R_X[1][0] = 0; R_X[1][1] = cos(radians); R_X[1][2] = -sin(radians); R_X[1][3] = 0;
    R_X[2][0] = 0; R_X[2][1] = sin(radians); R_X[2][2] = cos(radians); R_X[2][3] = 0;
    R_X[3][0] = 0; R_X[3][1] = 0; R_X[3][2] = 0; R_X[3][3] = 1;
    R_X.print();

    float trans_x=0.8f;
    float trans_y=-0.1f;
    float trans_z=-0.6f;
    std::cout<<"\nTranslation matrix for translating: "<<trans_x<<" units on x axis"<<trans_y<<" units on y axis"<<trans_z<<" units on z axis"<<std::endl;
    Matrix<4,4> translation;
    translation[0][0] = 1; translation[0][1] = 0; translation[0][2] = 0; translation[0][3] = trans_x;
    translation[1][0] = 0; translation[1][1] = 1; translation[1][2] = 0; translation[1][3] = trans_y;
    translation[2][0] = 0; translation[2][1] = 0; translation[2][2] = 1; translation[2][3] = trans_z;
    translation[3][0] = 0; translation[3][1] = 0; translation[3][2] = 0; translation[3][3] = 1;
    translation.print();
    */

    
    double t=0;
    double theta,n,f;
    std::cout<<"\nWhat is theta?";
    std::cin>>theta;
    std::cout<<"\nWhat is n?";
    std::cin>>n;
    std::cout<<"\nWhat is the far plane?";
    std::cin>>f;
    t=n*tan((theta/2.0)*(M_PI/180.00));
    t=round(t*100.00)/100.0;
    std::cout<<"\nThe t:"<<t<<std::endl;
    double width,height;
    std::cout<<"\nEnter width?";
    std::cin>>width;
    std::cout<<"\nEnter height?";
    std::cin>>height;
    double r=t*(width/height);
    std::cout<<"\nThe r: "<<r<<std::endl;
    std::cout<<"\n The l: "<<-r<<std::endl;
    std::cout<<"\n The b: "<<-t<<std::endl;
    Matrix<4,4> Mp;
    Mp[0][0]=n;  Mp[1][0]=0; Mp[2][0]=0; Mp[3][0]=0;
    Mp[0][1]=0; Mp[1][1]=n; Mp[2][1]=0; Mp[3][1]=0;
    Mp[0][2]=0; Mp[1][2]=0; Mp[2][2]=n+f; Mp[2][3]=-n*f;
    Mp[0][3]=0; Mp[1][3]=0; Mp[3][2]=1; Mp[3][3]=0;

    std::cout<<"\nPerspective Matrix: \n";
    Mp.print();


    Matrix<4,4> Mortho;
    Mortho[0][0]=2/(r-(-r)); Mortho[1][0]=0; Mortho[2][0]=0; Mortho[3][0]=-(r+(-r))/(r-(-r));
    Mortho[0][1]=0; Mortho[1][1]=2/(t-(-t)); Mortho[2][1]=0; Mortho[3][1]=-(t+(-t))/(t-(-t));
    Mortho[0][2]=0; Mortho[1][2]=0; Mortho[2][2]=2/(n-f); Mortho[2][3]=-(n+f)/(n-f);
    Mortho[0][3]=0; Mortho[1][0]=0; Mortho[3][2]=0; Mortho[3][3]=1;

    std::cout<<"\nOrthographic Projection Matrix: \n";
    Mortho.print();

    Matrix<4,4> Mper;

    Mper[0][0]=n/(r); Mper[1][0]=0; Mper[2][0]=0; Mper[3][0]=0;
    Mper[0][1]=0; Mper[1][1]=n/t; Mper[2][1]=0; Mper[3][1]=0;
    Mper[0][2]=0; Mper[1][2]=0; Mper[2][2]=(n+f)/(n-f); Mper[2][3]=2*n*f/(f-n);
    Mper[0][3]=0; Mper[1][0]=0; Mper[3][2]=1; Mper[3][3]=0;


    std::cout<<"\nPerspective Projection Matrix: \n";
    Mper.print();
    
    /*
    float scrw,scrh,w,h,d,z;
    std::cout<<"\nThe screen resoultion width: ";
    std::cin>>scrw;
    std::cout<<"\nThe screen resoultion height: ";
    std::cin>>scrh;
    std::cout<<"\nView volume wide: ";
    std::cin>>w;
    std::cout<<"\nView volume high: ";
    std::cin>>h;
    std::cout<<"\nView volume deep: ";
    std::cin>>d;
    std::cout<<"\nThe view volume is centred at a distance of : ";
    std::cin>>z;
    float camx,camy,camz,upx,upy,upz;
    std::cout<<"\ncamx :";
    std::cin>>camx;
    std::cout<<"\ncamy :";
    std::cin>>camy;
    std::cout<<"\ncamz :";
    std::cin>>camz;
    std::cout<<"\nupx ";
    std::cin>>upx;
    std::cout<<"\nupy: ";
    std::cin>>upy;
    std::cout<<"\nupz: ";
    std::cin>>upz;

    Vector<3> target={0,0,0};
    Vector<3> e={camx,camy,camz};
    Vector<3> worldUp={upx,upy,upz};

    Vector<3> g = {target[0] - e[0], target[1] - e[1], target[2]- e[2]};
    Vector<3> ng=g.unitVector();

    std::cout<<"\n The Normalized g: \n";
    ng.print();


    Vector<3> w_vec = {-ng[0], -ng[1], -ng[2]};
    std::cout<<"\n The Normalized w: \n";
    w_vec.print();

    Vector<3> u= worldUp.crossProduct(w_vec).unitVector();
    std::cout<<"\n The Normalized u: \n";
    u.print();
    
    Vector<3> v= w_vec.crossProduct(u);
    std::cout<<"\n The Normalized v: \n";
    v.print();

    std::cout << "\nBasis vectors calculated.";

    // 3. INVERSE CAMERA MATRIX (M_cam^-1)
    Matrix<4,4> Mcam_inv;
    // Rotation (Rows of Mcam_inv are the basis vectors u, v, w)
    Mcam_inv[0][0] = u[0];   Mcam_inv[1][0] = u[1];   Mcam_inv[2][0] = u[2];
    Mcam_inv[0][1] = v[0];   Mcam_inv[1][1] = v[1];   Mcam_inv[2][1] = v[2];
    Mcam_inv[0][2] = w_vec[0]; Mcam_inv[1][2] = w_vec[1]; Mcam_inv[2][2] = w_vec[2];

    // Translation (The dot product fix)
    Mcam_inv[0][3] = -(u[0]*e[0] + u[1]*e[1] + u[2]*e[2]);     // -u · e
    Mcam_inv[1][3] = -(v[0]*e[0] + v[1]*e[1] + v[2]*e[2]);     // -v · e
    Mcam_inv[2][3] = -(w_vec[0]*e[0] + w_vec[1]*e[1] + w_vec[2]*e[2]); // -w · e

    Mcam_inv[3][0] = 0; Mcam_inv[3][1] = 0; Mcam_inv[3][2] = 0; Mcam_inv[3][3] = 1;

    // 4. VIEW VOLUME BOUNDS (l, r, t, b, n, f)
    double r_val = w / 2.0;
    double l_val = -r_val;
    double t_val = h / 2.0;
    double b_val = -t_val;
    // n and f are distances along the -z axis
    double n_val = -z + (d / 2.0); 
    double f_val = -z - (d / 2.0);
    

    // 5. Orthographic Matrix
    Matrix<4,4> Mortho;
    Mortho[0][0] = 2.0 / (r_val - l_val);
    Mortho[1][1] = 2.0 / (t_val - b_val);
    Mortho[2][2] = 2.0 / (n_val - f_val);
    Mortho[0][3] = -(r_val + l_val) / (r_val - l_val);
    Mortho[1][3] = -(t_val + b_val) / (t_val - b_val);
    Mortho[2][3] = -(n_val + f_val) / (n_val - f_val);
    Mortho[3][3] = 1.0;



    // 6. Viewport Matrix
    Matrix<4,4> Mvp;
    Mvp[0][0] = scrw / 2.0;
    Mvp[1][1] = scrh / 2.0;
    Mvp[2][2] = 1.0;
    Mvp[0][3] = (scrw - 1.0) / 2.0;
    Mvp[1][3] = (scrh - 1.0) / 2.0;
    Mvp[3][3] = 1.0;

    std::cout << "--- INVERSE CAMERA MATRIX ---\n"; Mcam_inv.print();
    std::cout << "\nr: " << r_val << " l: " << l_val << " t: " << t_val << " b: " << b_val;
    std::cout << "\nn: " << n_val << " f: " << f_val << "\n";
    std::cout << "\n--- ORTHOGRAPHIC MATRIX ---\n"; Mortho.print();
    std::cout << "\n--- VIEWPORT MATRIX ---\n"; Mvp.print();
    */
    return 0;
}
