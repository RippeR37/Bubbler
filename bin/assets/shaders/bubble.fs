#version 330 core

in vec3 interpolatedPosition;
in vec3 interpolatedNormal;

out vec4 color;

uniform vec3 uColor;
uniform vec3 uCamPos;
uniform vec3 uBubbleCenter;
uniform vec3 uEyeDir;

const vec3 directionalLight = vec3(0.0, 1.0, 0.0);
const vec3 directionalLightColor = vec3(1.0);

void main() {
    float dist = distance(uCamPos, uBubbleCenter);
    float directionalLightFactor = clamp(dot(interpolatedNormal, directionalLight), 0.0, 0.7);
    float ambientLightFactor = 0.3;
    float specularLightFactor;
    vec3 materialColor = uColor;

    specularLightFactor = clamp(dot(normalize(uEyeDir), reflect(directionalLight, interpolatedNormal)), 0.0, 1.0);
    specularLightFactor = clamp(pow(specularLightFactor, 10) * 0.3, 0.0, 0.3);

    color.rgb  = vec3(0.0);
    color.rgb += ambientLightFactor * materialColor.rgb;
    color.rgb += directionalLightFactor * color.rgb * directionalLightColor;
    color.rgb += specularLightFactor * directionalLightColor;

    color.a = clamp(1.0 - smoothstep(2.0, 8.0, dist), 0.2, 0.8);
}
