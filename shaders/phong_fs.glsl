#version 410
layout (location = 0) out vec4 fragColor;
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTex;

#define NB_LIGHTS_MAX 32

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight point_light[NB_LIGHTS_MAX];
uniform SpotLight spot_light[NB_LIGHTS_MAX];
uniform int nb_pointLight;
uniform int nb_spotLight;
uniform vec3 viewPos;
uniform bool objectIsTextured;

uniform Material mat;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {

    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 resultColor = vec3(0.0);

    for (int i = 0 ; i < nb_pointLight ; ++i) {
        resultColor += calcPointLight(point_light[i], normal, fragPos, viewDir);
    }
    for (int i = 0 ; i < nb_spotLight ; ++i) {
        resultColor += calcSpotLight(spot_light[i], normal, fragPos, viewDir);
    }

    fragColor = vec4(resultColor, 1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    if(objectIsTextured){
        ambient = light.ambient * vec3(texture(mat.diffuse, fragTex)) * attenuation;
        diffuse = light.diffuse * diff * vec3(texture(mat.diffuse, fragTex)) * attenuation;
        specular = light.specular * spec * vec3(texture(mat.specular, fragTex)) * attenuation;
    }
    else{
        ambient = light.ambient  * attenuation;
        diffuse = light.diffuse  * diff * attenuation;
        specular = light.specular  * spec * attenuation;
    }


    return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    if(objectIsTextured){
        ambient = light.ambient * vec3(texture(mat.diffuse, fragTex));
        diffuse = light.diffuse * diff * vec3(texture(mat.diffuse, fragTex));
        specular = light.specular * spec * vec3(texture(mat.specular, fragTex));
    }
    else{
        ambient = light.ambient;
        diffuse = light.diffuse * diff;
        specular = light.specular * spec;
    }
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}