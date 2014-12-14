#version 330 core

in vec3 interpolatedPosition;
in vec3 interpolatedNormal;

out vec4 color;

uniform vec3 uColor;
uniform vec3 uCamPos;
uniform vec3 uBubbleCenter;
uniform vec3 uEyeDir;
uniform vec3 lightbubblePosition[5];
uniform int  lightbubbleCount;

const vec3 lightbubbleColor = vec3(1.0, 0.0, 0.0);
const vec3 directionalLight = vec3(0.0, 1.0, 0.0);
const vec3 directionalLightColor = vec3(1.0);

void main() {
    float dist = distance(uCamPos, uBubbleCenter);
    float directionalLightFactor = clamp(dot(interpolatedNormal, directionalLight), 0.0, 0.7);
    float ambientLightFactor = 0.3;
    float specularLightFactor;
    float lightbubbleDistanceFactor;
    float lightbubbleDiffuseFactor;
    vec3 materialColor;
    
    
    materialColor = uColor;
    specularLightFactor = clamp(dot(normalize(uEyeDir), reflect(directionalLight, interpolatedNormal)), 0.0, 1.0);
    specularLightFactor = clamp(pow(specularLightFactor, 10) * 0.3, 0.0, 0.3);

    color.rgb  = vec3(0.0);
    color.rgb += ambientLightFactor * materialColor.rgb;
    color.rgb += directionalLightFactor * color.rgb * directionalLightColor;
    color.rgb += specularLightFactor * directionalLightColor;


    /////////////
    // Ligbubbles
    /////////////
    for(int i = 0; i < min(5, lightbubbleCount); ++i) {
        lightbubbleDistanceFactor = distance(lightbubblePosition[i], interpolatedPosition);
        lightbubbleDistanceFactor = clamp(1.0 / (lightbubbleDistanceFactor * lightbubbleDistanceFactor), 0.0, 1.0);
        lightbubbleDiffuseFactor = clamp(dot(interpolatedNormal, normalize(lightbubblePosition[i] - uBubbleCenter)), 0.0, 1.0);

        color.rgb += lightbubbleColor * lightbubbleDistanceFactor * lightbubbleDiffuseFactor * 2.0;
    }

    color.a = clamp(1.0 - smoothstep(2.0, 8.0, dist), 0.2, 0.8);
}
