#version 400

in vec3 fragPos;
in vec3 normal;
in vec2 textPos;

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

#define MAX_SPOTLIGHTS 2
struct Spotlight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutoff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic;
};
uniform Spotlight spotlights[MAX_SPOTLIGHTS];
uniform int spotlightCount;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

vec3 CalcPointLight(PointLight light, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 viewDir);
vec3 CalcSpotlight(Spotlight light, vec3 viewDir);

uniform sampler2D textureUnit;
vec3 objectColor = vec3(0.385, 0.647, 0.812);

void main()
{
    vec3 result = material.ambient;
    vec3 viewDir = normalize(cameraPosition - fragPos);

    for (int i = 0; i < pointLightCount; i++)
    {
        result += CalcPointLight(pointLights[i], viewDir);
    }

    for (int i = 0; i < dirLightCount; i++)
    {
        result += CalcDirLight(dirLights[i], viewDir);
    }

    for (int i = 0; i < spotlightCount; i++)
    {
        result += CalcSpotlight(spotlights[i], viewDir);
    }

    fragColor = vec4(result, 1.0);
    vec4 textureColor = texture(textureUnit, textPos);
    fragColor *= textureColor;
}

vec3 CalcPointLight(PointLight light, vec3 viewDir)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }   

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));

    vec3 diffuse = material.diffuse * diff * light.color * objectColor;
    vec3 specular = material.specular * spec * light.color;

    return (diffuse + specular) * attenuation;
}

vec3 CalcDirLight(DirLight light, vec3 viewDir)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    } 

    vec3 diffuse = material.diffuse * diff * light.color * objectColor;
    vec3 specular = material.specular * spec * light.color;

    return diffuse + specular;
}

vec3 CalcSpotlight(Spotlight light, vec3 viewDir)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }   

    vec3 diffuse = material.diffuse * diff * light.color * objectColor;
    vec3 specular = material.specular * spec * light.color;

    return (diffuse + specular) * intensity * attenuation;
}
