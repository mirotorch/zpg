#version 400 

in vec3 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

void main() 
{
    vec3 lightPosition = vec3(3.0, 5.0, 0.0);
    vec4 lightColor = vec4(0.0,0.0,0.0, 1.0);

    vec3 lightDir = normalize(lightPosition - worldPos);

    float diff = max(dot(normalize(worldNorm), lightDir), 0.0);
    vec4 ambient = vec4(0.1,0.1,0.1, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

    fragColor = diff * objectColor + ambient;
};