#version 330 core

layout(location = 0) in vec4 vPos;

out vec3 interpolatedPosition;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vPos;

    interpolatedPosition = vPos.xyz;
}
