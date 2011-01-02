#include "../Common.hlsl"

void vs(float4 iPos : POSITION,
    float3 iNormal : NORMAL,
    #ifdef NORMALMAP
        float4 iTangent : TANGENT0,
    #endif
    float2 iTexCoord : TEXCOORD0,
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
    out float2 oTexCoord : TEXCOORD0,
    out float oDepth : TEXCOORD1,
    #ifdef NORMALMAP
        out float3 oNormal : TEXCOORD2,
        out float3 oTangent : TEXCOORD3,
        out float3 oBinormal : TEXCOORD4,
    #else
        out float3 oNormal : TEXCOORD2,
    #endif
    out float4 oPos : POSITION)
{
    #ifndef SKINNED
        #ifndef INSTANCED
            #ifndef NORMALMAP
                evaluatePositionNormal(iPos, iNormal, oPos, oNormal);
            #else
                evaluatePositionNormalTangent(iPos, iNormal, iTangent, oPos, oNormal, oTangent);
            #endif
        #else
            #ifndef SM3
                #ifndef NORMALMAP
                    evaluatePositionNormalInstanced(iPos, iNormal, cModelInstances[iInstanceNumber], oPos, oNormal);
                #else
                    evaluatePositionNormalTangentInstanced(iPos, iNormal, iTangent, cModelInstances[iInstanceNumber], oPos, oNormal, oTangent);
                #endif
            #else
                #ifndef NORMALMAP
                    evaluatePositionNormalInstanced(iPos, iNormal, iModelInstance, oPos, oNormal);
                #else
                    evaluatePositionNormalTangentInstanced(iPos, iNormal, iTangent, iModelInstance, oPos, oNormal, oTangent);
                #endif
            #endif
        #endif
    #else
        #ifndef NORMALMAP
            evaluatePositionNormalSkinned(iPos, iNormal, iBlendWeights, iBlendIndices, oPos, oNormal);
        #else
            evaluatePositionNormalTangentSkinned(iPos, iNormal, iTangent, iBlendWeights, iBlendIndices, oPos, oNormal, oTangent);
        #endif
    #endif
    
    oTexCoord = evaluateTexCoord(iTexCoord);
    oDepth = calculateDepth(oPos);
    
    #ifdef NORMALMAP
        oBinormal = cross(oTangent, oNormal) * iTangent.w;
    #endif
}

void ps(
    float2 iTexCoord : TEXCOORD0,
    float iDepth : TEXCOORD1,
    #ifdef NORMALMAP
        float3 iNormal : TEXCOORD2,
        float3 iTangent : TEXCOORD3,
        float3 iBinormal : TEXCOORD4,
    #else
        float3 iNormal : TEXCOORD2,
    #endif
    #ifndef HWDEPTH
        out float4 oDepth : COLOR1,
    #endif
    out float4 oNormal : COLOR0)
{
    #ifdef ALPHAMASK
        float4 diffInput = tex2D(sDiffMap, iTexCoord);
        if (diffInput.a < 0.5)
            discard;
    #endif

    #ifdef NORMALMAP
        float3x3 tbn = float3x3(iTangent, iBinormal, iNormal);
        float3 normal = normalize(mul(unpackNormal(tex2D(sNormalMap, iTexCoord)), tbn));
    #else
        float3 normal = normalize(iNormal);
    #endif

    float specPower = cMatSpecProperties.y / 255.0;

    oNormal = float4(normal * 0.5 + 0.5, specPower);
    #ifndef HWDEPTH
        oDepth = iDepth;
    #endif
}
