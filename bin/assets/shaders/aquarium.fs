#version 330 core

in vec3 interpolatedPosition;

out vec4 color;

uniform vec4 uColor;
uniform vec3 CamPos;

float reverseSmoothstep(float edge0, float edge1, float value) {
    return 1.0 - smoothstep(edge0, edge1, value);
}

void main() {
    float dist = distance(CamPos, interpolatedPosition);


    color.rgb = max(reverseSmoothstep(-5.0, 10.0, dist), 0.3) * uColor.rgb;
    color.a = 0.9;
}
