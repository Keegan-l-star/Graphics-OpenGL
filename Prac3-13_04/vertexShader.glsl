#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
out vec4 fragmentColor;

void main(){
    gl_Position = vertexPosition_modelspace;
    fragmentColor = vertexColor;
}

