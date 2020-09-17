#version 410 core
in vec3 normal;
out vec4 color;
in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform bool objectIsTextured;
void main()
{
    if(objectIsTextured)
        color = texture(ourTexture, TexCoord);
    else
        color =vec4(vec3(0.5f),1);
}
