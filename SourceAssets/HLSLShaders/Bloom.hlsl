#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"

uniform float cBloomThreshold;
uniform float2 cBloomMix;
uniform float2 cBlurOffset;

// We are blurring a 4x downsampled RT, so blur offsets are 4x in terms of the original RT
static const float offsets[5] = {
    8.0,
    4.0,
    0.0,
    -4.0,
    -8.0,
};

static const float weights[5] = {
    0.1,
    0.25,
    0.3,
    0.25,
    0.1
};

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oTexCoord : TEXCOORD0,
    out float2 oScreenPos : TEXCOORD1)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetQuadTexCoord(oPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iTexCoord : TEXCOORD0,
    float2 iScreenPos : TEXCOORD1,
    out float4 oColor : COLOR0)
{
    #ifdef BRIGHT
    float3 rgb = Sample(sDiffMap, iScreenPos + cBlurOffset * cSampleOffsets).rgb;
    oColor = float4((rgb - cBloomThreshold) / (1.0 - cBloomThreshold), 1.0);
    #endif

    #ifdef HBLUR
    float3 rgb = 0.0;
    for (int i = 0; i < 5; ++i)
        rgb += Sample(sDiffMap, iTexCoord + (cBlurOffset + float2(offsets[i], 0.0)) * cSampleOffsets).rgb * weights[i];
    oColor = float4(rgb, 1.0);
    #endif

    #ifdef VBLUR
    float3 rgb = 0.0;
    for (int i = 0; i < 5; ++i)
        rgb += Sample(sDiffMap, iTexCoord + (cBlurOffset + float2(0.0, offsets[i])) * cSampleOffsets).rgb * weights[i];
    oColor = float4(rgb, 1.0);
    #endif

    #ifdef COMBINE
    float3 original = Sample(sDiffMap, iScreenPos).rgb * cBloomMix.x;
    float3 bloom = Sample(sNormalMap, iTexCoord).rgb  * cBloomMix.y;
    // Prevent oversaturation
    original *= (1.0 - saturate(bloom));
    oColor = float4(original + bloom, 1.0);
    #endif
}
