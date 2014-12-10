#version 330 core

in vec3 interpolatedPosition;

out vec4 color;

uniform vec4 uColor;
uniform vec3 CamPos;
uniform vec3 lightbubblePosition[5];

const vec3 lightbubbleColor = vec3(1.0, 0.0, 0.0);

float reverseSmoothstep(float edge0, float edge1, float value) {
    return 1.0 - smoothstep(edge0, edge1, value);
}

void main() {
    float dist = distance(CamPos, interpolatedPosition);
    color.rgb = max(reverseSmoothstep(-5.0, 10.0, dist), 0.3) * uColor.rgb;

    for(int i = 0; i < 5; ++i) {
        float dist2 = distance(lightbubblePosition[i], interpolatedPosition);
        color.rgb += lightbubbleColor * clamp((0.1 / (dist2 * dist2 + 0.25)), 0.0, 0.5);
    }

    color.a = 0.9;
}
