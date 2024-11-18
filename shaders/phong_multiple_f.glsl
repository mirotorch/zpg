#version 400

in vec3 fragPos;
in vec3 normal; 

out vec4 fragColor;

uniform vec3 cameraPosition;

#define MAX_LIGHTS 4

struct Light {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[MAX_LIGHTS];
uniform int lightCount;

void main()
{
    vec3 objectColor = vec3(0.385, 0.647, 0.812);
    vec3 ambientStrength = vec3(0.1);  
    vec3 result = vec3(0);

    for (int i = 0; i < lightCount; i++)
    {
        vec3 lightPosition = lights[i].position;
        vec3 lightColor = lights[i].color;

        vec3 ambient = ambientStrength * lightColor;

        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(lightPosition - fragPos);

        if (dot(norm, lightDir) < 0.0) {
            norm = vec3(0);  
        }

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        float specularStrength = 0.5;
        vec3 viewDir = normalize(cameraPosition - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;

        float distance = length(lightPosition - fragPos.xyz);
        float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

        result += (ambient + diffuse + specular) * attenuation;
    }

    fragColor = vec4(result * objectColor, 1.0);
}
