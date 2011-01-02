#include "Common.hlsl"

void vs(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        #ifndef SM3
            int iInstanceNumber : TEXCOORD2,
        #else
            float4x3 iModelInstance : TEXCOORD2,
        #endif
    #endif
    #ifdef ALPHAMASK
        float2 iTexCoord : TEXCOORD0,
        out float2 oTexCoord : TEXCOORD0,
    #endif
    out float4 oPos : POSITION)
{
    #ifndef SKINNED
        #ifndef INSTANCED
            evaluatePosition(iPos, oPos);
        #else
            #ifndef SM3
                evaluatePositionInstanced(iPos, cModelInstances[iInstanceNumber], oPos);
            #else
                evaluatePositionInstanced(iPos, iModelInstance, oPos);
            #endif
        #endif
    #else
        evaluatePositionSkinned(iPos, iBlendWeights, iBlendIndices, oPos);
    #endif

    #ifdef ALPHAMASK
        oTexCoord = evaluateTexCoord(iTexCoord);
    #endif
}

void ps(
    #ifdef ALPHAMASK
        float2 iTexCoord : TEXCOORD0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef ALPHAMASK
    if (tex2D(sDiffMap, iTexCoord).a < 0.5)
        discard;
    #endif
    
    oColor = float4(1.0, 1.0, 1.0, 1.0);
}
