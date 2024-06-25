#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColorFromVtx;
uniform float sinWave;

void main() {
    gl_Position = vec4(aPos.x + sinWave, aPos.y, aPos.z, 1.0);
    ourColorFromVtx = vec3(aColor.x + sinWave, aColor.y + sinWave, aColor.z + sinWave);
}