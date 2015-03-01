#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : SV_POSITION,
    out float3 oTexCoord : TEXCOORD0)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    
    oPos.z = oPos.w;
    oTexCoord = iPos.xyz;
}

void PS(float3 iTexCoord : TEXCOORD0,
    out float4 oColor : SV_TARGET)
{
    oColor = cMatDiffColor * tDiffCubeMap.Sample(sDiffCubeMap, iTexCoord);
}
