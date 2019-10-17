#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    float2 iTexCoord : TEXCOORD0,
    float4 iColor : COLOR0,
    out float4 oColor : COLOR0,
    out float2 oTexCoord : TEXCOORD0,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);

    oColor = iColor;
    oTexCoord = iTexCoord;
}

void PS(float4 iColor : COLOR0,
        float2 iTexCoord : TEXCOORD0,
        out float4 oColor : OUTCOLOR0)
{
    float4 diffColor = cMatDiffColor * iColor;
    float4 diffInput = Sample2D(DiffMap, iTexCoord);
    oColor = diffColor * diffInput;
}
