#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD2,
    #endif
    float2 iTexCoord : TEXCOORD0,
    out float3 oTexCoord : TEXCOORD0,
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = float3(GetTexCoord(iTexCoord), GetDepth(oPos));
}

void PS(
    float3 iTexCoord : TEXCOORD0,
    out float4 oColor : COLOR0)
{
    #ifdef ALPHAMASK
        float alpha = tex2D(sDiffMap, iTexCoord.xy).a;
        if (alpha < 0.5)
            discard;
    #endif

    oColor = iTexCoord.z;
}
