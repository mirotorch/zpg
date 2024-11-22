#version 400

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 cameraPosition;

#define MAX_POINT_LIGHTS 4
struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;


#define MAX_DIR_LIGHTS 2
struct DirLight {
    vec3 direction;
    vec3 color;
};

uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform int dirLightCount;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

vec3 CalcPointLight(PointLight light, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 viewDir);


vec3 objectColor = vec3(0.385, 0.647, 0.812);

void main()
{
    vec3 result = vec3(0);
    vec3 viewDir = normalize(cameraPosition - fragPos);

    for (int i = 0; i < pointLightCount; i++)
    {
        result += CalcPointLight(pointLights[i], viewDir);
    }

    for (int i = 0; i < dirLightCount; i ++)
    {
        result += CalcDirLight(dirLights[i], viewDir);
    }

    fragColor = vec4(result, 1.0);
}


vec3 CalcPointLight(PointLight light, vec3 viewDir)
{
    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
  			     light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = material.ambient  * objectColor;
    vec3 diffuse  = material.diffuse  * diff * objectColor;
    vec3 specular = material.specular * spec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    if (diff <= 0.0) return ambient + diffuse;
    return (ambient + diffuse + specular);
}


vec3 CalcDirLight(DirLight light, vec3 viewDir)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = material.ambient  * objectColor;
    vec3 diffuse  = material.diffuse  * diff * objectColor;
    vec3 specular = material.specular * spec;
    if (diff <= 0.0) return ambient + diffuse;
    return (ambient + diffuse + specular);
}