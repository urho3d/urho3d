#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"
#include "PostProcess.hlsl"

#ifndef D3D11

// D3D9 uniforms
uniform float cTonemapExposureBias;
uniform float cTonemapMaxWhite;

#else

#ifdef COMPILEPS
// D3D11 constant buffers
cbuffer CustomPS : register(b6)
{
    float cTonemapExposureBias;
    float cTonemapMaxWhite;
}
#endif

#endif

void VS(float4 iPos : POSITION,
    out float2 oScreenPos : TEXCOORD0,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iScreenPos : TEXCOORD0,
    out float4 oColor : OUTCOLOR0)
{
    #ifdef REINHARDEQ3
    float3 color = ReinhardEq3Tonemap(max(Sample2D(DiffMap, iScreenPos).rgb * cTonemapExposureBias, 0.0));
    oColor = float4(color, 1.0);
    #endif

    #ifdef REINHARDEQ4
    float3 color = ReinhardEq4Tonemap(max(Sample2D(DiffMap, iScreenPos).rgb * cTonemapExposureBias, 0.0), cTonemapMaxWhite);
    oColor = float4(color, 1.0);
    #endif

    #ifdef UNCHARTED2
    float3 color = Uncharted2Tonemap(max(Sample2D(DiffMap, iScreenPos).rgb * cTonemapExposureBias, 0.0)) / 
        Uncharted2Tonemap(float3(cTonemapMaxWhite, cTonemapMaxWhite, cTonemapMaxWhite));
    oColor = float4(color, 1.0);
    #endif
}
