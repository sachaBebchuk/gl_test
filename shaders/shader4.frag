#version 150 core

in vec3 Color;

out vec4 outColor;

void main()
{
    outColor = vec4(1.0 - Color, 1.0);
}