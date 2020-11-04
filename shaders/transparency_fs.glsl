#version 430 core
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 fragAlpha;
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTex;

#define NB_LIGHTS_MAX 32

struct Material {
    int nb_diffuseMap;
    int nb_specularMap;
    sampler2D diffuseMap;
    sampler2D specularMap;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Shadow{
    sampler2D shadowMap;
    mat4 lightSpaceMatrix;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    Shadow shadow;

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
//Shadow shadow;
};
uniform Material mat;
uniform PointLight point_light[10];
uniform SpotLight spot_light[32];
uniform int nb_pointLight;
uniform int nb_spotLight;
uniform vec3 viewPos;

struct concreteMaterial{
    vec3 diffuse;
    vec3 specular;
    float shininess;
}concreteMat;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float computeShadow(sampler2D shadowMap, mat4 lightSpaceMatrix, vec3 lightDir);
void main() {

    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 resultColor = vec3(0.0);
    concreteMat.diffuse = mat.diffuse;
    concreteMat.specular = mat.specular;
    concreteMat.shininess = mat.shininess;
    if(mat.nb_diffuseMap>0){ concreteMat.diffuse = vec3(texture(mat.diffuseMap, fragTex));}
    if(mat.nb_diffuseMap>0){ concreteMat.specular = vec3(texture(mat.specularMap, fragTex));}
    float alpha = 0.001f;
    for (int i = 0 ; i < nb_pointLight ; ++i) {
        resultColor += calcPointLight(point_light[i], normal, fragPos, viewDir);
    }
    for (int i = 0 ; i < nb_spotLight ; ++i) {
        resultColor += calcSpotLight(spot_light[i], normal, fragPos, viewDir);
    }

    fragColor = vec4(resultColor, alpha);
    fragAlpha = vec4(alpha);
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
    ambient = light.ambient * concreteMat.diffuse * attenuation;
    diffuse = light.diffuse * diff * concreteMat.diffuse * attenuation;
    specular = light.specular * spec * concreteMat.specular * attenuation;
    float shadow = computeShadow(light.shadow.shadowMap, light.shadow.lightSpaceMatrix, lightDir);
    return (1-shadow*0.5) * ambient + (1-shadow) * ( diffuse + specular);
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

   ambient = light.ambient * concreteMat.diffuse * attenuation;
   diffuse = light.diffuse * diff * concreteMat.diffuse * attenuation;
   specular = light.specular * spec * concreteMat.specular * attenuation;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
float computeShadow(sampler2D shadowMap, mat4 lightSpaceMatrix, vec3 lightDir){
    vec4 fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    float eps = max(0.05 * (1.0 - dot(fragNormal, lightDir)), 0.005);
    if (currentDepth > 1.0 - eps) return 0.0;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - eps > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;
}