#include "../Uniforms.frag"
#include "../Samplers.frag"

varying vec2 vScreenPos;

void main()
{
    gl_FragColor = vec4(cFogColor, 1.0);
    // Copy a slightly biased depth value because of possible inaccuracy
    gl_FragDepth = min(texture2D(sDepthBuffer, vScreenPos).r + 0.000001, 1.0);
}
