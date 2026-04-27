#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono> 
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "shader.hpp"

#include "shapes/Square.h"
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Circle.h"
#include "shapes/Cone.h"
#include "shapes/TriangularPrism.h"
#include "shapes/Vector.h"
#include "shapes/transformation.h"
#include "shapes/SquarePyramid.h"
#include "shapes/Sphere.h"


#include "Figure.h"
#include "Shape3D.h"

using namespace std;

// Global wireframe toggle
bool wireframeMode = false;
unsigned int rotationSpeed=0;
vector<Object*> scene;

void key_listener(GLFWwindow* window, int key, int scancode, int action, int mods){
    const int STEP = 5;
    const float MOVE_STEP = 0.05f;
    if(key==GLFW_KEY_ENTER && action==GLFW_PRESS){
        wireframeMode=!wireframeMode;
        //std::cout<<"Enter was pressed"<<std::endl;
    } else if((key == GLFW_KEY_KP_ADD || (key == GLFW_KEY_EQUAL && (mods & GLFW_MOD_SHIFT))) && action==GLFW_PRESS){
        rotationSpeed++;
    } else if((key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS ) && action==GLFW_PRESS){
        if(rotationSpeed<=0){
            rotationSpeed=0;
        }else{
            rotationSpeed--;
        }
    } else if(action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) {
            for (Object* o : scene){
                o->rotateX(STEP);
            } 
        } else if (key == GLFW_KEY_S) {
            for (Object* o : scene){
                o->rotateX(-STEP);
            }
        } else if (key == GLFW_KEY_A) {
            for (Object* o : scene){
                o->rotateY(STEP);
            }
        } else if (key == GLFW_KEY_D) {
            for (Object* o : scene){
                o->rotateY(-STEP);
            }
        } else if (key == GLFW_KEY_E) {
            for (Object* o : scene){
                o->rotateZ(STEP);
            }
        } else if (key == GLFW_KEY_Q) {
            for (Object* o : scene){
                o->rotateZ(-STEP);
            }
        } else if (key == GLFW_KEY_I) {
            for (Object* o : scene) {
                o->move(0.0f, MOVE_STEP, 0.0f);
            }
        } else if (key == GLFW_KEY_K) {
            for (Object* o : scene) {
                o->move(0.0f, -MOVE_STEP, 0.0f);
            }
        } else if (key == GLFW_KEY_L) {
            for (Object* o : scene) {
                o->move(MOVE_STEP, 0.0f, 0.0f);
            }
        } else if (key == GLFW_KEY_J) {
            for (Object* o : scene) {
                o->move(-MOVE_STEP, 0.0f, 0.0f);
            }
        } else if (key == GLFW_KEY_O) {
            for (Object* o : scene) {
                o->move(0.0f, 0.0f, MOVE_STEP);
            }
        } else if (key == GLFW_KEY_U) {
            for (Object* o : scene) {
                o->move(0.0f, 0.0f, -MOVE_STEP);
            }
        }
    }
}


const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1000, 1000, "u24594522", NULL, NULL);
    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    startUpGLEW();
    return window;
}

int main()
{
    GLFWwindow *window;
    try
    {
        window = setUp();
    }
    catch (const char *e)
    {
        cout << e << endl;
        throw;
    }
// Add code Here:
    GLuint programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
    if (programID == 0) { std::cerr << "Failed to load shaders" << std::endl; glfwTerminate(); return 1; }
    glEnable(GL_DEPTH_TEST);
    glUseProgram(programID);
    GLint modelLoc = glGetUniformLocation(programID, "model");

    auto setAttribcolour = [](float r, float g, float b, float a) {
        glDisableVertexAttribArray(1);
        glVertexAttrib4f(1, r, g, b, a);
    };
    glClearColor(0.1f,0.1f,0.1f,1.0f);


    //Creation of the 3D objcts starts here:
    {

        // Creation of the cylinder- rotor
     //Make this the one that starts closer to the viewr
    float rotorR= 0.02f;
    float alignedx = 0.0f;
    float alignedy = 0.0f;
    float centreZ= 0.45f;

        //This is the centre the blades rotate around
    Vector<4> c1={alignedx, alignedy, centreZ+0.001f, 1.0f};
    Vector<4> c2={alignedx, alignedy, (centreZ+0.075f), 1.0f};
    Vector<4> rotorCenter = {(c1[0]+c2[0])/2.0f, (c1[1]+c2[1])/2.0f, (c1[2]+c2[2])/2.0f, 1.0f};
    float rotorHeight = fabsf(c2[2] - c1[2]);
    Cylinder<4> rotor = Cylinder(rotorCenter, rotorR, rotorHeight, 9, 2);  // axis=2 for Z-axis
    rotor.setColour(154, 154, 154, 1.0f);
    rotor.createGLBuffers();

    // Creation of the cone - rotor end
    Vector<4> apex1={alignedx,alignedy, (centreZ-0.045f), 1.0f};
    Cone<4> cone={apex1, c1, rotorR, 9};
    cone.setColour(0,0,100, 1.0f);
    cone.createGLBuffers();

        

    float sailTLx=0.38f;
    float sailTLy=sailTLx+0.02f;

    float sail2TLx=-0.38f;
    float sail2TLy=-(sail2TLx)-0.02f;
        //
    Vector<4> startTL={sailTLx, sailTLy, centreZ,1.0f};
    Vector<4> startTR={sailTLy, sailTLx, centreZ,1.0f};
    Vector<4> startBL={-sailTLy, -sailTLx, centreZ,1.0f};
    Vector<4> startBR={ -sailTLx,-sailTLy , centreZ,1.0f}; 

    //Square(const Vector<n>& tl, const Vector<n>& tr, const Vector<n>& br, const Vector<n>& bl);
    Square<4> start=Square(startTL,startTR, startBR, startBL);

        //farther rectangle to viewer :-0.025f
    Vector<4> startTL2={sailTLx, sailTLy, centreZ+0.025f,1.0f};
    Vector<4> startTR2={sailTLy, sailTLx, centreZ+0.025f,1.0f};
    Vector<4> startBL2={-sailTLy, -sailTLx, centreZ+0.025f,1.0f};
    Vector<4> startBR2={-sailTLx,-sailTLy, centreZ+0.025f,1.0f}; 

    Square<4> start2=Square(startTL2,startTR2 , startBR2, startBL2);

    Cube<4> first=Cube(start,start2);
    first.setColour(90,90, 90, 1.0f);
    first.createGLBuffers();

    Vector<4> TL={sail2TLx, sail2TLy, centreZ,1.0f};
    Vector<4> TR={sail2TLy, sail2TLx, centreZ,1.0f};
    Vector<4> BL={-sail2TLy, -sail2TLx, centreZ,1.0f};
    Vector<4> BR={-sail2TLx, -sail2TLy, centreZ,1.0f}; 

    Square<4> sailarm3_0=Square(TL,TR, BR,BL);

        //farther rectangle to viewer :+0.025f
    Vector<4> TL2={sail2TLx, sail2TLy, centreZ+0.025f,1.0f};
    Vector<4> TR2={sail2TLy, sail2TLx,  centreZ+0.025f,1.0f};
    Vector<4> BL2={-sail2TLy, -sail2TLx, centreZ+0.025f,1.0f};
    Vector<4> BR2={-sail2TLx, -sail2TLy, centreZ+0.025f,1.0f}; 

    Square<4> sailarm4_0=Square(TL2,TR2, BR2,BL2);

    Cube<4> rotorArm2=Cube(sailarm3_0,sailarm4_0);
    rotorArm2.setColour(90,90, 90, 1.0f);
    rotorArm2.createGLBuffers();

    float dif=0.3f;

    // Left x value (at TL)
    float sail_left_x = sailTLx;
    float sail_left_y_top = sailTLy;
    float sail_left_x_bot = sail_left_x-dif; 
    float sail_left_y_bot = sail_left_x_bot + 0.02f;  // offset for bottom line
    
    
    // Right x value (extend past TR)
    float sail_right_x_top = sail_left_x + 0.15f;
    float sail_right_y_top = -(sail_right_x_top) + (sail2TLy-(-(sailTLx)-0.02f));
    float sail_right_y_bot = -(sail_right_x_top-dif) + (sail_left_y_bot-(-(sail_left_x_bot)-0.02f));

    Square<4> sailA_front(
        {sail_left_x, sail_left_y_top,centreZ - 0.025f, 1.0f }, //TL
        {sail_right_x_top, sail_right_y_top, centreZ - 0.025f, 1.0f},// TR
        {sail_right_x_top-dif,sail_right_y_bot, centreZ - 0.025f, 1.0f }, //BR
        {sail_left_x_bot, sail_left_y_bot,centreZ - 0.025f , 1.0f}// BL
    );  

    Square<4> sailA_back(
        {sail_left_x, sail_left_y_top,centreZ, 1.0f }, //TL
        {sail_right_x_top, sail_right_y_top, centreZ , 1.0f},// TR
        {sail_right_x_top-dif,sail_right_y_bot, centreZ , 1.0f }, //BR
        {sail_left_x_bot, sail_left_y_bot,centreZ, 1.0f}// BL
    );
    
    Cube<4> sailA(sailA_front, sailA_back);
    sailA.setColour(200, 66, 40, 1.0f);
    sailA.createGLBuffers();

    //TL,TR,BL,BR
    Square<4> sailB_front(
        {-sail_left_x, -sail_left_y_top,centreZ - 0.025f, 1.0f }, //TL
        {-sail_right_x_top, -sail_right_y_top, centreZ - 0.025f, 1.0f},// TR
        {-(sail_right_x_top-dif),-sail_right_y_bot, centreZ - 0.025f, 1.0f }, //BR
        {-sail_left_x_bot, -sail_left_y_bot,centreZ - 0.025f , 1.0f}// BL
    );  
    

    Square<4> sailB_back(
        {-sail_left_x,-sail_left_y_top,centreZ, 1.0f }, //TL
        {-sail_right_x_top, -sail_right_y_top,centreZ , 1.0f},// TR
        {-(sail_right_x_top-dif),-sail_right_y_bot , centreZ , 1.0f }, //BR
        {-sail_left_x_bot,-sail_left_y_bot, centreZ, 1.0f}// BL
    );
  
    Cube<4> sailB(sailB_front, sailB_back);
    sailB.setColour(200, 66, 40, 1.0f);
    sailB.createGLBuffers();
    
    // SailC using sail2TLx and sail2TLy (opposite arm, same pattern as sailA)
    
    float sail_left_xc = sail2TLx;
    float sail_left_y_topc = sail2TLy;
    float sail_left_x_botc = sail_left_xc+dif;
    float sail_left_y_botc = -(sail_left_x_botc)-0.02f;

    float sail_right_x_topc = sail_left_xc + 0.15f;
    float sail_right_y_topc = (sail_right_x_topc) + (sailTLy - ((sail2TLx)+0.02f));
    float sail_right_y_botc = (sail_right_x_topc + dif) + (sail_left_y_botc - ((sail_left_x_botc)+0.02f));
    
     // SailD - opposite of sailC
    Square<4> sailD_front(
        {sail_left_xc, sail_left_y_topc, centreZ - 0.025f, 1.0f},
        {sail_right_x_topc, sail_right_y_topc, centreZ - 0.025f, 1.0f},
        {sail_right_x_topc + dif, sail_right_y_botc, centreZ - 0.025f, 1.0f},
        {sail_left_x_botc, sail_left_y_botc, centreZ - 0.025f, 1.0f}
    );

    //sailD_front.print();
    
    Square<4> sailD_back(
        {sail_left_xc, sail_left_y_topc, centreZ, 1.0f},
        {sail_right_x_topc, sail_right_y_topc, centreZ, 1.0f},
        {sail_right_x_topc + dif, sail_right_y_botc, centreZ, 1.0f},
        {sail_left_x_botc, sail_left_y_botc, centreZ, 1.0f}
    );
    
    Square<4> sailC_front(
        {-sail_left_xc, -sail_left_y_topc, centreZ - 0.025f, 1.0f},
        {-sail_right_x_topc, -sail_right_y_topc, centreZ - 0.025f, 1.0f},
        {-(sail_right_x_topc + dif), -sail_right_y_botc, centreZ - 0.025f, 1.0f},
        {-sail_left_x_botc, -sail_left_y_botc, centreZ - 0.025f, 1.0f}
    );
    
    Square<4> sailC_back(
        {-sail_left_xc, -sail_left_y_topc, centreZ, 1.0f},
        {-sail_right_x_topc, -sail_right_y_topc, centreZ, 1.0f},
        {-(sail_right_x_topc + dif), -sail_right_y_botc, centreZ, 1.0f},
        {-sail_left_x_botc, -sail_left_y_botc, centreZ, 1.0f}
    );
    
    Cube<4> sailC(sailC_front, sailC_back);
    sailC.setColour(200, 66, 40, 1.0f);
    sailC.createGLBuffers();
    
   
    Cube<4> sailD(sailD_front, sailD_back);
    sailD.setColour(200, 66, 40, 1.0f);
    sailD.createGLBuffers();

    float bottomgrassIRx=-0.7f;
    float bottomgrassORx=-0.8f;
    float bottomgrassy=-0.8f;
    float dif2=0.8f;
    Square<4> barriersLC(
        {bottomgrassORx,bottomgrassy+0.35f,centreZ-dif2,1.0f},//TL
        {bottomgrassIRx,bottomgrassy+0.35f,centreZ-dif2,1.0f},//TR
        {bottomgrassIRx,bottomgrassy,centreZ-dif2,1.0f},///BR
        {bottomgrassORx,bottomgrassy,centreZ-dif2,1.0f}//BL
        
    );

    Square<4> barriersLF(
        {bottomgrassORx,bottomgrassy+0.35f,centreZ+dif2,1.0f},//TL
        {bottomgrassIRx,bottomgrassy+0.35f,centreZ+dif2,1.0f},//TR
        {bottomgrassIRx,bottomgrassy,centreZ+dif2,1.0f},///BR
        {bottomgrassORx,bottomgrassy,centreZ+dif2,1.0f}//BL
        
    );

    Cube<4> barrrierL(barriersLC,barriersLF);

    float newZ=centreZ+dif2;

    Square<4> barriersLRC(
        {bottomgrassORx,bottomgrassy+0.6f,newZ+dif2,1.0f},//TL
        {bottomgrassIRx,bottomgrassy+0.6f,newZ+dif2,1.0f},//TR
        {bottomgrassIRx,bottomgrassy,newZ+dif2,1.0f},///BR
        {bottomgrassORx,bottomgrassy,newZ+dif2,1.0f}//BL
        
    );

    Square<4> barriersLRF(
        {bottomgrassORx,bottomgrassy+0.35f,newZ,1.0f},//TL
        {bottomgrassIRx,bottomgrassy+0.35f,newZ,1.0f},//TR
        {bottomgrassIRx,bottomgrassy,newZ,1.0f},///BR
        {bottomgrassORx,bottomgrassy,newZ,1.0f}//BL
        
    );

    Cube<4> barrrierLR(barriersLRC,barriersLRF);

    Square<4> barriersRRC(
        {-bottomgrassORx,bottomgrassy+0.6f,newZ+dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.6f,newZ+dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,newZ+dif2,1.0f},///BR
        {-bottomgrassORx,bottomgrassy,newZ+dif2,1.0f}//BL
        
    );

    Square<4> barriersRRF(
        {-bottomgrassORx,bottomgrassy+0.35f,newZ,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.35f,newZ,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,newZ,1.0f},///BR
        {-bottomgrassORx,bottomgrassy,newZ,1.0f}//BL
        
    );

    Cube<4> barrrierRR(barriersRRC,barriersRRF);


    Square<4> barriersOC(
        {-bottomgrassORx,bottomgrassy+0.6f,newZ+dif2,1.0f},//TL
        {bottomgrassORx,bottomgrassy+0.6f,newZ+dif2,1.0f},//TR
        {bottomgrassORx,bottomgrassy,newZ+dif2,1.0f},///BR
        {-bottomgrassORx,bottomgrassy,newZ+dif2,1.0f}//BL
        
    );

    Square<4> barriersOF(
        {-bottomgrassORx,bottomgrassy+0.6f,newZ+dif2+0.35f,1.0f},//TL
        {bottomgrassORx,bottomgrassy+0.6f,newZ+dif2+0.35f,1.0f},//TR
        {bottomgrassORx,bottomgrassy,newZ+dif2+0.35f,1.0f},///BR
        {-bottomgrassORx,bottomgrassy,newZ+dif2+0.35f,1.0f}//BL
        
    );

    Cube<4> barrriersO(barriersOF,barriersOC);




    Square<4> barriersRC(
        {-bottomgrassORx,bottomgrassy+0.35f,centreZ-dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.35f,centreZ-dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,centreZ-dif2,1.0f},///BR
        {-bottomgrassORx,bottomgrassy,centreZ-dif2,1.0f}//BL
        
    );

    Square<4> barriersRF(
        {-bottomgrassORx,bottomgrassy+0.35f,centreZ+dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.35f,centreZ+dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,centreZ+dif2,1.0f},///BR
        {-bottomgrassORx,bottomgrassy,centreZ+dif2,1.0f}//BL
        
    );

    Cube<4> barrrierR(barriersRC,barriersRF);

    Square<4> sgf(
        {bottomgrassIRx,bottomgrassy+0.45f,newZ+dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.45f,newZ+dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,newZ+dif2,1.0f},///BR
        {bottomgrassIRx,bottomgrassy,newZ+dif2,1.0f}//BL
    );

    Square<4> sgc(
        {bottomgrassIRx,bottomgrassy+0.2f,newZ,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.2f,newZ,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,newZ,1.0f},///BR
        {bottomgrassIRx,bottomgrassy,newZ,1.0f}//BL
    );

    Cube<4> sGrass(sgc,sgf);

    Vector<4> h1={0, bottomgrassy+0.21f, centreZ+dif2-0.1f, 1.0f};
    Vector<4> h2={0, bottomgrassy+0.12f, centreZ+dif2-0.1f, 1.0f};
    Cylinder<4> hole = Cylinder(h1,h2, 0.04f,9);
    hole.setColour(50, 50, 54, 1.0f);
    hole.createGLBuffers();

    Square<4> mtc(
        {bottomgrassIRx,bottomgrassy+0.210f,centreZ-dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.210f,centreZ-dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy+0.2f,centreZ-dif2,1.0f},///BR
        {bottomgrassIRx,bottomgrassy+0.2f,centreZ-dif2,1.0f}//BL
    );

    Square<4> mtf(
        {bottomgrassIRx,bottomgrassy+0.210f,centreZ-dif2+0.3f,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.210f,centreZ-dif2+0.3f,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy+0.2f,centreZ-dif2+0.3f,1.0f},///BR
        {bottomgrassIRx,bottomgrassy+0.2f,centreZ-dif2+0.3f,1.0f}//BL
    );

    Cube<4> mat(mtc,mtf);

    mat.setColour(76,153,0,1.0f);

    float startObZ=centreZ-dif2+0.3f+0.1f;
    float offset=0.05f;
    float len=0.025f;

    Square<4> ob1c(
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.25f,startObZ+offset+len,1.0f},//TL
        {(-bottomgrassIRx),bottomgrassy+0.25f,startObZ+len,1.0f},//TR
        {(-bottomgrassIRx),bottomgrassy+0.2f,startObZ+len,1.0f},///BR
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.2f,startObZ+offset+len,1.0f}//BL
    );

    Square<4> ob1f(
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.25f,startObZ+offset,1.0f},//TL
        {(-bottomgrassIRx),bottomgrassy+0.25f,startObZ,1.0f},//TR
        {(-bottomgrassIRx),bottomgrassy+0.2f,startObZ,1.0f},///BR
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.2f,startObZ+offset,1.0f}//BL
    );

    Cube<4> ob1(ob1c,ob1f);

    ob1.setColour(255,255,255,1.0f);

    Square<4> ob2c(
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.25f,startObZ+offset+len,1.0f},//TL
        {(-bottomgrassIRx),bottomgrassy+0.25f,startObZ+2*len+2*offset,1.0f},//TR
        {(-bottomgrassIRx),bottomgrassy+0.2f,startObZ+2*len+2*offset,1.0f},///BR
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.2f,startObZ+offset+len,1.0f}//BL
    );

    Square<4> ob2f(
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.25f,startObZ+offset+len+len,1.0f},//TL
        {(-bottomgrassIRx),bottomgrassy+0.25f,startObZ+2*len+2*offset+len,1.0f},//TR
        {(-bottomgrassIRx),bottomgrassy+0.2f,startObZ+2*len+2*offset+len,1.0f},///BR
        {(-bottomgrassIRx)-0.2f,bottomgrassy+0.2f,startObZ+offset+len+len,1.0f}//BL
    );

    Cube<4> ob2(ob2c,ob2f);

    ob2.setColour(255,255,255,1.0f);

    float wmf=centreZ+0.075f;
    float wmb=wmf+0.255f;

    Square<4> legLC(
        {bottomgrassIRx+0.1f,bottomgrassy+0.35f,wmf,1.0f},
        {bottomgrassIRx+0.25f,bottomgrassy+0.35f,wmf,1.0f},
        {bottomgrassIRx+0.25f,bottomgrassy+0.2f,wmf,1.0f},
        {bottomgrassIRx+0.1f,bottomgrassy+0.2f,wmf,1.0f}
    );

    Square<4> legLF(
        {bottomgrassIRx+0.1f,bottomgrassy+0.35f,wmb,1.0f},
        {bottomgrassIRx+0.25f,bottomgrassy+0.35f,wmb,1.0f},
        {bottomgrassIRx+0.25f,bottomgrassy+0.2f,wmb,1.0f},
        {bottomgrassIRx+0.1f,bottomgrassy+0.2f,wmb,1.0f}
    );

    Cube<4> legL(legLC,legLF);

    Square<4> legRC(
        {-(bottomgrassIRx+0.1f),bottomgrassy+0.35f,wmf,1.0f},
        {-(bottomgrassIRx+0.25f),bottomgrassy+0.35f,wmf,1.0f},
        {-(bottomgrassIRx+0.25f),bottomgrassy+0.2f,wmf,1.0f},
        {-(bottomgrassIRx+0.1f),bottomgrassy+0.2f,wmf,1.0f}
    );

    Square<4> legRF(
        {-(bottomgrassIRx+0.1f),bottomgrassy+0.35f,wmb,1.0f},
        {-(bottomgrassIRx+0.25f),bottomgrassy+0.35f,wmb,1.0f},
        {-(bottomgrassIRx+0.25f),bottomgrassy+0.2f,wmb,1.0f},
        {-(bottomgrassIRx+0.1f),bottomgrassy+0.2f,wmb,1.0f}
    );

    Cube<4> legR(legRC,legRF);
    float theXB=bottomgrassIRx+0.05f;
    float theXT=theXB+0.1f;
    float theYB=bottomgrassy+0.35f;
    float theYT=bottomgrassy+0.5f;
    float diff=theYT-theYB;
    float diffx=theXT-theXB;
    Square<4> wmBF1(
        {theXT,theYT,wmf,1.0f},
        {-theXT,theYT,wmf,1.0f},
        {-(theXB),theYB,wmf,1.0f},
        {theXB,theYB,wmf,1.0f}
    );

    Square<4> wmBB1(
        {theXT,theYT,wmb,1.0f},
        {-theXT,theYT,wmb,1.0f},
        {-theXB,theYB,wmb,1.0f},
        {theXB,theYB,wmb,1.0f}
    );

    Cube<4> wmB1(wmBF1,wmBB1);

    theYB=theYT;
    theYT+=diff;
    theXB=theXT+0.005f;
    theXT=theXB+diffx;

    Square<4> wmBF2(
        {theXT,theYT,wmf,1.0f},
        {-theXT,theYT,wmf,1.0f},
        {-(theXB),theYB,wmf,1.0f},
        {theXB,theYB,wmf,1.0f}
    );

    Square<4> wmBB2(
        {theXT,theYT,wmb,1.0f},
        {-theXT,theYT,wmb,1.0f},
        {-theXB,theYB,wmb,1.0f},
        {theXB,theYB,wmb,1.0f}
    );

    Cube<4> wmB2(wmBF2,wmBB2);

    theYB=theYT;
    theYT+=diff;
    theXB=theXT+0.005f;
    theXT=theXB+diffx;

    Square<4> wmBF3(
        {theXT,theYT,wmf,1.0f},
        {-theXT,theYT,wmf,1.0f},
        {-(theXB),theYB,wmf,1.0f},
        {theXB,theYB,wmf,1.0f}
    );

    Square<4> wmBB3(
        {theXT,theYT,wmb,1.0f},
        {-theXT,theYT,wmb,1.0f},
        {-theXB,theYB,wmb,1.0f},
        {theXB,theYB,wmb,1.0f}
    );

    Cube<4> wmB3(wmBF3,wmBB3);

    theYB=theYT;
    theYT+=diff;
    theXB=theXT+0.005f;
    theXT=theXB+diffx;

    Square<4> wmBF4(
        {theXT,theYT,wmf,1.0f},
        {-theXT,theYT,wmf,1.0f},
        {-(theXB),theYB,wmf,1.0f},
        {theXB,theYB,wmf,1.0f}
    );

    Square<4> wmBB4(
        {theXT,theYT,wmb,1.0f},
        {-theXT,theYT,wmb,1.0f},
        {-theXB,theYB,wmb,1.0f},
        {theXB,theYB,wmb,1.0f}
    );

    Cube<4> wmB4(wmBF4,wmBB4);

    theYB=theYT;
    theYT+=diff+0.15f;
    theXB=theXT+0.005f;
    theXT=theXB;

    Square<4> wmBF5(
        {theXT,theYT,wmf,1.0f},
        {-theXT,theYT,wmf,1.0f},
        {-(theXB),theYB,wmf,1.0f},
        {theXB,theYB,wmf,1.0f}
    );

    Square<4> wmBB5(
        {theXT,theYT,wmb,1.0f},
        {-theXT,theYT,wmb,1.0f},
        {-theXB,theYB,wmb,1.0f},
        {theXB,theYB,wmb,1.0f}
    );

    Cube<4> wmB5(wmBF5,wmBB5);
    // std::cout<<"The top y: "<<theYT<<" The top x "<<theXT<<std::endl;

    Sphere<4> ball({0.0f, -0.565f,centreZ-dif2+0.1f}, 0.025f,6, 8);

    theXT-=0.001f;
    Square<4> base(

    
    {-theXT,theYT,wmf,1.0f},
    
    {theXT,theYT,wmf,1.0f},
    {theXT,theYT,wmb,1.0f},
    {-theXT,theYT,wmb,1.0f}
    
    );
    float apexZ=(wmb+wmf)/2;


    Vector<4> TriApex{0.0f,theYT+0.5f,apexZ,1.0f};

    SquarePyramid<4> roof(base,TriApex);

     Square<4> bgf(
        {bottomgrassIRx,bottomgrassy+0.2f,centreZ-dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.2f,centreZ-dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,centreZ-dif2,1.0f},///BR
        {bottomgrassIRx,bottomgrassy,centreZ-dif2,1.0f}//BL
    );

    Square<4> bgc(
        {bottomgrassIRx,bottomgrassy+0.2f,centreZ+dif2,1.0f},//TL
        {-bottomgrassIRx,bottomgrassy+0.2f,centreZ+dif2,1.0f},//TR
        {-bottomgrassIRx,bottomgrassy,centreZ+dif2,1.0f},///BR
        {bottomgrassIRx,bottomgrassy,centreZ+dif2,1.0f}//BL
    );

    Cube<4> bGrass(bgc,bgf);


    dif2=0.3f;

    bottomgrassORx-=0.15f;

    Square<4> LPC(
        {bottomgrassORx-0.35f,bottomgrassy+0.35f,centreZ-dif2,1.0f},//TL
        {bottomgrassORx,bottomgrassy+0.35f,centreZ-dif2,1.0f},//TR
        {bottomgrassORx,bottomgrassy,centreZ-dif2,1.0f},///BR
        {bottomgrassORx-0.35f,bottomgrassy,centreZ-dif2,1.0f}//BL
        
    );

    Square<4> LPF(
        {bottomgrassORx-0.35f,bottomgrassy+0.35f,centreZ+dif2,1.0f},//TL
        {bottomgrassORx,bottomgrassy+0.35f,centreZ+dif2,1.0f},//TR
        {bottomgrassORx,bottomgrassy,centreZ+dif2,1.0f},///BR
        {bottomgrassORx-0.35f,bottomgrassy,centreZ+dif2,1.0f}//BL
        
    );

    Cube<4> LPot(LPF,LPC);
    LPot.setColour(140, 87, 34);

    Square<4> LLC(
        {bottomgrassORx-0.35f+0.015F,bottomgrassy+0.60f,centreZ-dif2+0.01F,1.0f},//TL
        {bottomgrassORx-0.015F,bottomgrassy+0.60f,centreZ-dif2+0.01F,1.0f},//TR
        {bottomgrassORx-0.015F,bottomgrassy+0.35f,centreZ-dif2+0.01F,1.0f},///BR
        {bottomgrassORx-0.35f+0.015F,bottomgrassy+0.35f,centreZ-dif2+0.01F,1.0f}//BL
        
    );

    Square<4> LLF(
        {bottomgrassORx-0.35f+0.015F,bottomgrassy+0.60f,centreZ+dif2-0.01F,1.0f},//TL
        {bottomgrassORx-0.015F,bottomgrassy+0.60f,centreZ+dif2-0.01F,1.0f},//TR
        {bottomgrassORx-0.015F,bottomgrassy+0.35f,centreZ+dif2-0.01F,1.0f},///BR
        {bottomgrassORx-0.35f+0.015F,bottomgrassy+0.35f,centreZ+dif2-0.01F,1.0f}//BL
        
    );

    Cube<4> LLeaf(LLF,LLC);
    LLeaf.setColour(3, 92, 15);

    Square<4> RLC(
        {-(bottomgrassORx-0.35f+0.015F),bottomgrassy+0.60f,centreZ-dif2+0.01F,1.0f},//TL
        {-(bottomgrassORx-0.015F),bottomgrassy+0.60f,centreZ-dif2+0.01F,1.0f},//TR
        {-(bottomgrassORx-0.015F),bottomgrassy+0.35f,centreZ-dif2+0.01F,1.0f},///BR
        {-(bottomgrassORx-0.35f+0.015F),bottomgrassy+0.35f,centreZ-dif2+0.01F,1.0f}//BL
    );

    Square<4> RLF(
        {-(bottomgrassORx-0.35f+0.015F),bottomgrassy+0.60f,centreZ+dif2-0.01F,1.0f},//TL
        {-(bottomgrassORx-0.015F),bottomgrassy+0.60f,centreZ+dif2-0.01F,1.0f},//TR
        {-(bottomgrassORx-0.015F),bottomgrassy+0.35f,centreZ+dif2-0.01F,1.0f},///BR
        {-(bottomgrassORx-0.35f+0.015F),bottomgrassy+0.35f,centreZ+dif2-0.01F,1.0f}//BL
        
    );

    Cube<4> RLeaf(RLF,RLC);
    RLeaf.setColour(3, 92, 15);

    Square<4> RPC(
        {-(bottomgrassORx-0.35f),bottomgrassy+0.35f,centreZ-dif2,1.0f},//TL
        {-(bottomgrassORx),bottomgrassy+0.35f,centreZ-dif2,1.0f},//TR
        {-(bottomgrassORx),bottomgrassy,centreZ-dif2,1.0f},///BR
        {-(bottomgrassORx-0.35f),bottomgrassy,centreZ-dif2,1.0f}//BL
        
    );

    Square<4> RPF(
        {-(bottomgrassORx-0.35f),bottomgrassy+0.35f,centreZ+dif2,1.0f},//TL
        {-(bottomgrassORx),bottomgrassy+0.35f,centreZ+dif2,1.0f},//TR
        {-(bottomgrassORx),bottomgrassy,centreZ+dif2,1.0f},///BR
        {-(bottomgrassORx-0.35f),bottomgrassy,centreZ+dif2,1.0f}//BL
        
    );

    Cube<4> RPot(RPF,RPC);
    RPot.setColour(140, 87, 34);



    Figure blades=Figure();
    blades.setRotationAxis(alignedx,alignedy,(centreZ+0.05f),alignedx,alignedy, (centreZ-0.05f));
    blades.addShape(&sailD);
    blades.addShape(&sailC);
    blades.addShape(&sailA);
    blades.addShape(&sailB);
    blades.setShapeColour(120,120,120, 1.0f );
    blades.addShape(&rotorArm2);
    blades.addShape(&first);
    blades.addShape(&cone);
    blades.addShape(&rotor);

    blades.move( 0.0f,0.275f, 0.0f);

    Figure barriers=Figure();
    barriers.addShape(&barrrierL);
    barriers.addShape(&barrrierLR);
    barriers.addShape(&barrrierR);
    barriers.addShape(&barrrierRR);
    barriers.addShape(&barrriersO);

    barriers.setShapeColour(160,80,30,1.0f);
    barriers.addShape(&ob1);
    barriers.addShape(&ob2);

    Figure grass=Figure();
    grass.addShape(&bGrass);
    grass.addShape(&sGrass);

    grass.setShapeColour(0,204,0,1.0f);
    grass.addShape(&mat);
    grass.addShape(&hole);


    Figure windmill=Figure();
    windmill.addShape(&legL);
    windmill.addShape(&legR);
    windmill.addShape(&wmB1);
    windmill.addShape(&wmB2);
    windmill.addShape(&wmB3);
    windmill.addShape(&wmB4);
    windmill.addShape(&wmB5);
    windmill.addShape(&roof);

    windmill.setShapeColour(153,0,0,1.0f);


    ball.setColour(255,255,255,1.0f);
    Shape3D golfBall(&ball);

    Figure decor=Figure();
    decor.addShape(&LPot);
    decor.addShape(&RPot);
    decor.addShape(&LLeaf);
    decor.addShape(&RLeaf);

    
    scene.push_back(&golfBall);
    scene.push_back(&grass);
    scene.push_back(&barriers);
    scene.push_back(&blades);
    scene.push_back(&windmill);
    scene.push_back(&decor);
    


    glfwSetKeyCallback(window,key_listener);
    do{ 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        if(rotationSpeed==0){

        }else{
            blades.rotate(rotationSpeed);
        }

        for(Object* s:scene){
            s->draw(wireframeMode);
        }
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

    } // end scene scope: stack objects and their GL buffers are destroyed here

    // Delete shader program and shutdown GLFW (GL context still valid for cleanup)
    glDeleteProgram(programID);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
