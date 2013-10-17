#include "Uniforms.frag"
#include "Samplers.frag"
#include "PostProcess.frag"

varying vec2 vScreenPos;

void main()
{
    vec3 color = texture2D(sDiffMap, vScreenPos).rgb;
    gl_FragColor = vec4(ColorCorrection(color, sVolumeMap), 1.0);
}
