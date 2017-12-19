#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Fog.glsl"

varying vec2 vTexCoord;
uniform float cMixFactor;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);

    // texcoord2
    vTexCoord = iTexCoord1;

    // bake
    vec2 texEnc = vTexCoord.xy * 2 - vec2(1);
    gl_Position = vec4(texEnc, 0.5, 1);
}

void PS()
{
    vec4 diffColor = cMatDiffColor;
    vec3 direct    = texture2D(sNormalMap, vTexCoord).rgb;
    vec3 indirect  = texture2D(sEmissiveMap, vTexCoord).rgb;

    diffColor.rgb *= direct + indirect * cMixFactor;

    gl_FragColor = diffColor;
}
