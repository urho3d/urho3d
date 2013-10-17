#include "Uniforms.frag"
#include "Samplers.frag"
#include "PostProcess.frag"

uniform vec2 cBlurDir;
uniform float cBlurRadius;
uniform float cBlurSigma;
uniform vec2 cBlurHInvSize;

varying vec2 vTexCoord;
varying vec2 vScreenPos;

void main()
{
    #ifdef BLUR3
        gl_FragColor = GaussianBlur(3, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, vTexCoord);
    #endif

    #ifdef BLUR5
        gl_FragColor = GaussianBlur(5, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, vTexCoord);
    #endif

    #ifdef BLUR7
        gl_FragColor = GaussianBlur(7, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, vTexCoord);
    #endif

    #ifdef BLUR9
        gl_FragColor = GaussianBlur(9, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, vTexCoord);
    #endif
}
