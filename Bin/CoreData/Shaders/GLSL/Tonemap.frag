#include "Uniforms.frag"
#include "Samplers.frag"
#include "PostProcess.frag"

uniform float cTonemapExposureBias;
uniform float cTonemapMaxWhite;

varying vec2 vScreenPos;

void main()
{
    #ifdef REINHARDEQ3
    vec3 color = ReinhardEq3Tonemap(max(texture2D(sDiffMap, vScreenPos).rgb * cTonemapExposureBias, 0.0));
    gl_FragColor = vec4(color, 1.0);
    #endif

    #ifdef REINHARDEQ4
    vec3 color = ReinhardEq4Tonemap(max(texture2D(sDiffMap, vScreenPos).rgb * cTonemapExposureBias, 0.0), cTonemapMaxWhite);
    gl_FragColor = vec4(color, 1.0);
    #endif

    #ifdef UNCHARTED2
    vec3 color = Uncharted2Tonemap(max(texture2D(sDiffMap, vScreenPos).rgb * cTonemapExposureBias, 0.0)) / 
        Uncharted2Tonemap(vec3(cTonemapMaxWhite, cTonemapMaxWhite, cTonemapMaxWhite));
    gl_FragColor = vec4(color, 1.0);
    #endif
}
