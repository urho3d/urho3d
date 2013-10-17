#include "Uniforms.frag"
#include "Samplers.frag"
#include "PostProcess.frag"

uniform float cGamma;

varying vec2 vScreenPos;

void main()
{
    vec3 color = texture2D(sDiffMap, vScreenPos).rgb;
    gl_FragColor = vec4(ToInverseGamma(color), 1.0);
}
