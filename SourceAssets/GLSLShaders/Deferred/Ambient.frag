#include "../Uniforms.frag"
#include "../Samplers.frag"
#include "../Fog.frag"

varying vec2 vScreenPos;

void main()
{
    vec4 diffInput = texture2D(sDiffBuffer, vScreenPos);
    float depth = texture2D(sDepthBuffer, vScreenPos).r;

    vec3 ambientColor = cAmbientColor * diffInput.rgb;

    #ifdef ORTHO
        float linearDepth = depth;
    #else
        float linearDepth = ReconstructDepth(depth);
    #endif

    // Store coarse depth to alpha channel for deferred antialiasing
    gl_FragColor = vec4(ambientColor + GetFogFactor(linearDepth) * cFogColor, linearDepth);
    
    // Copy a slightly biased depth value because of possible inaccuracy
    gl_FragDepth = min(texture2D(sDepthBuffer, vScreenPos).r + 0.000001, 1.0);
}
