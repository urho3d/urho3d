#include "Uniforms.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
        float4 iColor : COLOR0,
        out float4 oColor : COLOR0,
        out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);

    oColor = iColor;
}

void PS(float4 iColor : COLOR0,
        out float4 oColor : OUTCOLOR0)
{
    oColor = iColor;
}
