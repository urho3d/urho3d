#include "../Common.hlsl"

void VS(float4 iPos : POSITION,
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
        float4x3 iModelInstance : TEXCOORD2,
    #endif
    out float2 oTexCoord : TEXCOORD0,
    out float oDepth : TEXCOORD1,
    #ifdef NORMALMAP
        out float3 oNormal : TEXCOORD2,
        out float3 oTangent : TEXCOORD3,
        out float3 oBitangent : TEXCOORD4,
    #else
        out float3 oNormal : TEXCOORD2,
    #endif
    out float4 oPos : POSITION)
{
    #if (!defined(SKINNED)) && (!defined(INSTANCED))
        #ifndef NORMALMAP
            GetPositionNormal(iPos, iNormal, oPos, oNormal);
        #else
            GetPositionNormalTangent(iPos, iNormal, iTangent, oPos, oNormal, oTangent);
        #endif
    #endif
    #ifdef SKINNED
        #ifndef NORMALMAP
            GetPositionNormalSkinned(iPos, iNormal, iBlendWeights, iBlendIndices, oPos, oNormal);
        #else
            GetPositionNormalTangentSkinned(iPos, iNormal, iTangent, iBlendWeights, iBlendIndices, oPos, oNormal, oTangent);
        #endif
    #endif
    #ifdef INSTANCED
        #ifndef NORMALMAP
            GetPositionNormalInstanced(iPos, iNormal, iModelInstance, oPos, oNormal);
        #else
            GetPositionNormalTangentInstanced(iPos, iNormal, iTangent, iModelInstance, oPos, oNormal, oTangent);
        #endif
    #endif

    oTexCoord = GetTexCoord(iTexCoord);
    oDepth = GetDepth(oPos);
    
    #ifdef NORMALMAP
        oBitangent = cross(oTangent, oNormal) * iTangent.w;
    #endif
}

void PS(
    float2 iTexCoord : TEXCOORD0,
    float iDepth : TEXCOORD1,
    #ifdef NORMALMAP
        float3 iNormal : TEXCOORD2,
        float3 iTangent : TEXCOORD3,
        float3 iBitangent : TEXCOORD4,
    #else
        float3 iNormal : TEXCOORD2,
    #endif
    out float4 oNormal : COLOR0,
    out float4 oDepth : COLOR1)
{
    #ifdef ALPHAMASK
        if (tex2D(sDiffMap, iTexCoord).a < 0.5)
            discard;
    #endif

    #ifdef NORMALMAP
        float3x3 tbn = float3x3(iTangent, iBitangent, iNormal);
        float3 normal = normalize(mul(UnpackNormal(tex2D(sNormalMap, iTexCoord)), tbn));
    #else
        float3 normal = normalize(iNormal);
    #endif

    float specPower = cMatSpecProperties.y * (1.0 / 255.0);

    oNormal = float4(normal * 0.5 + 0.5, specPower);
    oDepth = iDepth;
}
