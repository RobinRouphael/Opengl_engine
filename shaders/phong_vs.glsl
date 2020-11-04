#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragNormal;
out vec2 fragTex;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragPos = vec3(model * vec4(position, 1.0));
    fragNormal = mat3(transpose(inverse(model))) * inormal;
    fragTex = aTexCoord;

    gl_Position = projection * view * vec4(fragPos, 1.0);
}