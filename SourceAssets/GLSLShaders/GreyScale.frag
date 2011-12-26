#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"

varying vec2 vScreenPos;

void main()
{
    vec3 input = texture2D(sDiffMap, vScreenPos).rgb;
    float intensity = GetIntensity(input);
    gl_FragColor = vec4(intensity, intensity, intensity, 1.0);
}
