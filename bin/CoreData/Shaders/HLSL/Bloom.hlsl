#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"

#ifndef D3D11

// D3D9 uniforms
uniform float cBloomThreshold;
uniform float2 cBloomMix;
uniform float2 cHBlurOffsets;
uniform float2 cHBlurInvSize;

#else

// D3D11 constant buffers
#ifdef COMPILEVS
cbuffer CustomVS : register(b6)
{
    float2 cHBlurOffsets;
}
#else
cbuffer CustomPS : register(b6)
{
    float cBloomThreshold;
    float2 cBloomMix;
    float2 cHBlurInvSize;
}
#endif

#endif

static const float offsets[5] = {
    2.0,
    1.0,
    0.0,
    -1.0,
    -2.0,
};

static const float weights[5] = {
    0.1,
    0.25,
    0.3,
    0.25,
    0.1
};

void VS(float4 iPos : POSITION,
    out float2 oTexCoord : TEXCOORD0,
    out float2 oScreenPos : TEXCOORD1,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetQuadTexCoord(oPos) + cHBlurOffsets;
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iTexCoord : TEXCOORD0,
    float2 iScreenPos : TEXCOORD1,
    out float4 oColor : OUTCOLOR0)
{
    #ifdef BRIGHT
    float3 rgb = Sample2D(DiffMap, iScreenPos).rgb;
    oColor = float4((rgb - cBloomThreshold) / (1.0 - cBloomThreshold), 1.0);
    #endif

    #ifdef HBLUR
    float3 rgb = 0.0;
    for (int i = 0; i < 5; ++i)
        rgb += Sample2D(DiffMap, iTexCoord + (float2(offsets[i], 0.0)) * cHBlurInvSize).rgb * weights[i];
    oColor = float4(rgb, 1.0);
    #endif

    #ifdef VBLUR
    float3 rgb = 0.0;
    for (int i = 0; i < 5; ++i)
        rgb += Sample2D(DiffMap, iTexCoord + (float2(0.0, offsets[i])) * cHBlurInvSize).rgb * weights[i];
    oColor = float4(rgb, 1.0);
    #endif

    #ifdef COMBINE
    float3 original = Sample2D(DiffMap, iScreenPos).rgb * cBloomMix.x;
    float3 bloom = Sample2D(NormalMap, iTexCoord).rgb  * cBloomMix.y;
    // Prevent oversaturation
    original *= saturate(1.0 - bloom);
    oColor = float4(original + bloom, 1.0);
    #endif
}
