#version 410

uniform vec3 color;

out vec4 ocolor;

void main() {
    ocolor = vec4(color, 1.0);
}