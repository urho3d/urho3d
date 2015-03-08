#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"
#include "PostProcess.hlsl"

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
    float3 color = Sample2D(DiffMap, iScreenPos).rgb;
    #ifndef D3D11
        oColor = float4(ColorCorrection(color, sVolumeMap), 1.0);
    #else
        oColor = float4(ColorCorrection(color, tVolumeMap, sVolumeMap), 1.0);
    #endif
}
