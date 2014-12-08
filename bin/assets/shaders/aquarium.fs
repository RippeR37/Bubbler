#version 330 core

in vec3 interpolatedPosition;

out vec4 color;

uniform vec4 uColor;
uniform vec3 CamPos;

void main() {
    float dist = distance(CamPos, interpolatedPosition);

    color = uColor;

    color.rgb = max(smoothstep(10.0, -5.0, dist), 0.3) * color.rgb;
    color.a = 0.9;
}
