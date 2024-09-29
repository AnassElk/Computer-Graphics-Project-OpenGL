#version 330 core

out vec4 out_color;

uniform vec3 uniformColor;

void main() {
    out_color = vec4(uniformColor, 1.0);
}
