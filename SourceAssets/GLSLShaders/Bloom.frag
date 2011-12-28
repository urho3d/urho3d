#version 120

#include "Uniforms.frag"
#include "Samplers.frag"

uniform float cBloomThreshold;
uniform vec2 cBloomMix;
uniform vec2 cHBlurInvSize;

varying vec2 vTexCoord;
varying vec2 vScreenPos;

float offsets[5] = float[](
    2.0,
    1.0,
    0.0,
    -1.0,
    -2.0
);

float weights[5] = float[](
    0.1,
    0.25,
    0.3,
    0.25,
    0.1
);

void main()
{
    #ifdef BRIGHT
    vec3 rgb = texture2D(sDiffMap, vScreenPos).rgb;
    gl_FragColor = vec4((rgb - vec3(cBloomThreshold, cBloomThreshold, cBloomThreshold)) / (1.0 - cBloomThreshold), 1.0);
    #endif

    #ifdef HBLUR
    vec3 rgb = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < 5; ++i)
        rgb += texture2D(sDiffMap, vTexCoord + vec2(offsets[i], 0.0) * cHBlurInvSize).rgb * weights[i];
    gl_FragColor = vec4(rgb, 1.0);
    #endif

    #ifdef VBLUR
    vec3 rgb = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < 5; ++i)
        rgb += texture2D(sDiffMap, vTexCoord + vec2(0.0, offsets[i]) * cHBlurInvSize).rgb * weights[i];
    gl_FragColor = vec4(rgb, 1.0);
    #endif

    #ifdef COMBINE
    vec3 original = texture2D(sDiffMap, vScreenPos).rgb * cBloomMix.x;
    vec3 bloom = texture2D(sNormalMap, vTexCoord).rgb  * cBloomMix.y;
    // Prevent oversaturation
    original *= vec3(1.0, 1.0, 1.0) - clamp(bloom, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
    gl_FragColor = vec4(original + bloom, 1.0);
    #endif
}
