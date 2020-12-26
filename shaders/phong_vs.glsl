#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float weights[4];

out vec3 fragNormal;
out vec2 fragTex;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

struct Bone{
    mat4 transform;
};

uniform Bone bones[4];
uniform int nb_bones;

void main() {

    float weightsum = 0;
    vec3 pos = vec3(0);

    for(int i = 0; i < nb_bones; i++){
        pos+= vec3(bones[i].transform * vec4(position,1.0)) * weights[i];
        weightsum += weights[i];
    }
    if(weightsum != 0)
        pos = pos/weightsum;
    else
        pos = position ;


    fragPos = vec3(model * vec4(pos, 1.0));
    fragNormal = normalize((transpose(inverse(mat3(model)))) * inormal);
    fragTex = aTexCoord;

    gl_Position = projection * view * vec4(fragPos, 1.0);
}