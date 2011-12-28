#include "Uniforms.frag"
#include "Samplers.frag"

uniform float cBloomThreshold;
uniform vec2 cBloomMix;
uniform vec2 cHBlurInvSize;

varying vec2 vTexCoord;
varying vec2 vScreenPos;

void main()
{
    #ifdef BRIGHT
    vec3 rgb = texture2D(sDiffMap, vScreenPos).rgb;
    gl_FragColor = vec4((rgb - vec3(cBloomThreshold, cBloomThreshold, cBloomThreshold)) / (1.0 - cBloomThreshold), 1.0);
    #endif

    #ifdef HBLUR
    vec3 rgb = texture2D(sDiffMap, vTexCoord + vec2(-2.0, 0.0) * cHBlurInvSize).rgb * 0.1;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(-1.0, 0.0) * cHBlurInvSize).rgb * 0.25;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(0.0, 0.0) * cHBlurInvSize).rgb * 0.3;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(1.0, 0.0) * cHBlurInvSize).rgb * 0.25;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(2.0, 0.0) * cHBlurInvSize).rgb * 0.1;
    gl_FragColor = vec4(rgb, 1.0);
    #endif

    #ifdef VBLUR
    vec3 rgb = texture2D(sDiffMap, vTexCoord + vec2(0.0, -2.0) * cHBlurInvSize).rgb * 0.1;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(0.0, -1.0) * cHBlurInvSize).rgb * 0.25;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(0.0, 0.0) * cHBlurInvSize).rgb * 0.3;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(0.0, 1.0) * cHBlurInvSize).rgb * 0.25;
    rgb += texture2D(sDiffMap, vTexCoord + vec2(0.0, 2.0) * cHBlurInvSize).rgb * 0.1;
    gl_FragColor = vec4(rgb, 1.0);
    #endif

    #ifdef COMBINE
    vec3 original = texture2D(sDiffMap, vScreenPos).rgb * cBloomMix.x;
    vec3 bloom = texture2D(sNormalMap, vTexCoord).rgb  * cBloomMix.y;
    // Prevent oversaturation
    original *= max(vec3(1.0) - bloom, vec3(0.0));
    gl_FragColor = vec4(original + bloom, 1.0);
    #endif
}
