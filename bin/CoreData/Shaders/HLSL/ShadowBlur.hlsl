#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"

#ifndef D3D11

// D3D9 uniforms
uniform float2 cBlurOffsets;

#else

#ifdef COMPILEPS
// D3D11 constant buffers
cbuffer CustomPS : register(b6)
{
    float2 cBlurOffsets;
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
    float2 color = 0.0;

    color += 0.015625 * Sample2D(DiffMap, iScreenPos - 3.0 * cBlurOffsets).rg;
    color += 0.09375 * Sample2D(DiffMap, iScreenPos - 2.0 * cBlurOffsets).rg;
    color += 0.234375 * Sample2D(DiffMap, iScreenPos - cBlurOffsets).rg;
    color += 0.3125 * Sample2D(DiffMap, iScreenPos).rg;
    color += 0.234375 * Sample2D(DiffMap, iScreenPos + cBlurOffsets).rg;
    color += 0.09375 * Sample2D(DiffMap, iScreenPos + 2.0 * cBlurOffsets).rg;
    color += 0.015625 * Sample2D(DiffMap, iScreenPos + 3.0 * cBlurOffsets).rg;

    oColor = float4(color, 0.0, 0.0);
}

