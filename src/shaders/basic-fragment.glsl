#version 330 core
out vec4 FragColor;

in vec3 ourColorFromVtx;

uniform vec4 ourColorUniform; //UNUSED

void main () {
    FragColor = vec4(ourColorFromVtx, 1.0);
}