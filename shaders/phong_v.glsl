#version 400
layout(location=0) in vec3 vp;  
layout(location=1) in vec3 vn;  

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 normal; 

void main() 
{
    fragPos = vec3(modelMatrix * vec4(vp, 1.0));
    
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    normal = normalize(normalMatrix * vn);

    gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);
}
