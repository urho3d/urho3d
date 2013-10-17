#include "Uniforms.frag"
#include "Samplers.frag"
#include "PostProcess.frag"

uniform float cBloomHDRThreshold;
uniform float cBloomHDRBlurSigma;
uniform float cBloomHDRBlurRadius;
uniform vec2 cBloomHDRBlurDir;
uniform vec2 cBloomHDRMix;
uniform vec2 cBright2InvSize;
uniform vec2 cBright4InvSize;
uniform vec2 cBright8InvSize;
uniform vec2 cBright16InvSize;

varying vec2 vTexCoord;
varying vec2 vScreenPos;

const int BlurKernelSize = 5;

void main()
{
    #ifdef BRIGHT
    vec3 color = texture2D(sDiffMap, vScreenPos).rgb;
    gl_FragColor = vec4(max(color - cBloomHDRThreshold, 0.0), 1.0);
    #endif

    #ifdef BLUR16
    gl_FragColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright16InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, vScreenPos);
    #endif

    #ifdef BLUR8
    gl_FragColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright8InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, vScreenPos);
    #endif

    #ifdef BLUR4
    gl_FragColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright4InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, vScreenPos);
    #endif

    #ifdef BLUR2
    gl_FragColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright2InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, vScreenPos);
    #endif

    #ifdef COMBINE16
    gl_FragColor = texture2D(sDiffMap, vScreenPos) + texture2D(sNormalMap, vTexCoord);
    #endif

    #ifdef COMBINE8
    gl_FragColor = texture2D(sDiffMap, vScreenPos) + texture2D(sNormalMap, vTexCoord);
    #endif

    #ifdef COMBINE4
    gl_FragColor = texture2D(sDiffMap, vScreenPos) + texture2D(sNormalMap, vTexCoord);
    #endif

    #ifdef COMBINE2
    vec3 color = texture2D(sDiffMap, vScreenPos).rgb * cBloomHDRMix.x;
    vec3 bloom = texture2D(sNormalMap, vTexCoord).rgb * cBloomHDRMix.y;
    gl_FragColor = vec4(color + bloom, 1.0);
    #endif
}
