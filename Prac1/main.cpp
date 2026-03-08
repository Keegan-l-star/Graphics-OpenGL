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
    return 0;
}
