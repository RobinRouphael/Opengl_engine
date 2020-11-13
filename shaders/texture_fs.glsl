#version 410 core
in vec3 normal;
out vec4 color;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{

        color = vec4(normal,1.0);//texture(ourTexture, TexCoord);

}
