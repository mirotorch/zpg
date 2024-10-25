#version 400 

in vec3 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

void main(void) 
{

    vec3 lightPosition = vec3(3.0, 5.0, 0.0);
    vec4 lightColor = vec4(0.0,0.0,0.0, 1.0);
    vec3 lightDir = normalize(lightPosition - worldPos);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * lightColor;

    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);



    float diff = max(dot(normalize(worldNorm), lightDir), 0.0);
    vec4 ambient = vec4(0.1,0.1,0.1, 1.0);

    fragColor = (diff + spec) * objectColor + ambient;
};