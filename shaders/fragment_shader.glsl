#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 planeColor;  // Uniform variable for color

void main() {
    FragColor = vec4(planeColor, 1.0); // Use the uniform color
}
