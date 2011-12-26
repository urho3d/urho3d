#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"

varying vec2 vScreenPos;

void main()
{
    vec3 rgb = texture2D(sDiffMap, vScreenPos).rgb;
    float intensity = GetIntensity(rgb);
    gl_FragColor = vec4(intensity, intensity, intensity, 1.0);
}
