#version 400
layout(location=0) in vec3 vp;  
layout(location=1) in vec3 vn;  
layout(location=2) in vec2 tp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 normal; 
out vec2 textPos;

void main() 
{
    fragPos = vec3(modelMatrix * vec4(vp, 1.0));
    textPos = tp;
    
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    normal = normalize(normalMatrix * vn);

    gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);
}
