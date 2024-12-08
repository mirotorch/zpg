#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube textureUnit;

void main()
{    
    FragColor = texture(textureUnit, TexCoords);
}
