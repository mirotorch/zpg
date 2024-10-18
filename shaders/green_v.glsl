#version 330 core
layout(location=0) in vec3 vp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 positionMatrix;
void main() 
{
    gl_Position = viewMatrix * positionMatrix * modelMatrix * vec4(vp, 1.0);
};
