#version 410

in vec3 oposition;
out vec4 ocolor;

void main() {
    ocolor = vec4(vec3((1-length(oposition))*10), 1.0);
}