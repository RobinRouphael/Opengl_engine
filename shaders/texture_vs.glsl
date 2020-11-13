#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 normal;
out vec2 TexCoord;
out vec3 oposition;
void main()
{
    // Note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(position, 1.0f);
    normal = (transpose(inverse(mat3(model)))) * inormal;
    TexCoord = aTexCoord;
    oposition = position;
}
