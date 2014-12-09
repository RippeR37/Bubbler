#version 330 core

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vNor;

out vec3 interpolatedPosition;
out vec3 interpolatedNormal;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main() {
    gl_Position = MVP * vPos;

    interpolatedPosition = vPos.xyz;
    interpolatedNormal = vNor.xyz;
}
