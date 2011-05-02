#include "Common.hlsl"

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
    #if (!defined(SKINNED)) && (!defined(INSTANCED))
        GetPosition(iPos, oPos);
    #endif
    #ifdef SKINNED
        GetPositionSkinned(iPos, iBlendWeights, iBlendIndices, oPos);
    #endif
    #ifdef INSTANCED
        GetPositionInstanced(iPos, iModelInstance, oPos);
    #endif

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
        if (tex2D(sDiffMap, iTexCoord).a < 0.5)
            discard;
    #endif

    oColor = 1.0;
}
