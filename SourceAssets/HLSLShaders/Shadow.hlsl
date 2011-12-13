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
    #ifdef ALPHAMASK
        float2 iTexCoord : TEXCOORD0,
        out float2 oTexCoord : TEXCOORD0,
    #endif
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);

    #ifdef ALPHAMASK
        oTexCoord = GetTexCoord(iTexCoord);
    #endif
}

void PS(
    #ifdef ALPHAMASK
        float2 iTexCoord : TEXCOORD0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef ALPHAMASK
        float alpha = tex2D(sDiffMap, iTexCoord).a;
    #else
        const float alpha = 1.0;
    #endif

    oColor = alpha;
}
