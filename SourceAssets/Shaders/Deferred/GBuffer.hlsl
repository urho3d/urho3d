#include "../Uniforms.hlsl"
#include "../Samplers.hlsl"
#include "../Transform.hlsl"
#include "../Fog.hlsl"

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
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION)
{
    #if defined(SKINNED)
        #ifndef NORMALMAP
            GetPositionNormalSkinned(iPos, iNormal, iBlendWeights, iBlendIndices, oPos, oNormal);
        #else
            GetPositionNormalTangentSkinned(iPos, iNormal, iTangent, iBlendWeights, iBlendIndices, oPos, oNormal, oTangent);
        #endif
    #elif defined(INSTANCED)
        #ifndef NORMALMAP
            GetPositionNormalInstanced(iPos, iNormal, iModelInstance, oPos, oNormal);
        #else
            GetPositionNormalTangentInstanced(iPos, iNormal, iTangent, iModelInstance, oPos, oNormal, oTangent);
        #endif
    #else
        #ifndef NORMALMAP
            GetPositionNormal(iPos, iNormal, oPos, oNormal);
        #else
            GetPositionNormalTangent(iPos, iNormal, iTangent, oPos, oNormal, oTangent);
        #endif
    #endif

    #ifdef NORMALMAP
        oBitangent = cross(oTangent, oNormal) * iTangent.w;
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif

    oTexCoord = GetTexCoord(iTexCoord);
    oDepth = GetDepth(oPos);
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
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oDiff : COLOR0,
    out float4 oNormal : COLOR1,
    out float4 oDepth : COLOR2)
{
    #ifdef DIFFMAP
        float4 diffInput = tex2D(sDiffMap, iTexCoord);
        float3 diffColor = cMatDiffColor.rgb * diffInput.rgb;
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
    #else
        float3 diffColor = cMatDiffColor.rgb;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= iColor.rgb;
    #endif

    #ifdef NORMALMAP
        float3x3 tbn = float3x3(iTangent, iBitangent, iNormal);
        float3 normal = normalize(mul(UnpackNormal(tex2D(sNormalMap, iTexCoord)), tbn));
    #else
        float3 normal = normalize(iNormal);
    #endif

    #ifdef SPECMAP
        float specStrength = tex2D(sSpecMap, iTexCoord).r * cMatSpecProperties.x;
    #else
        float specStrength = cMatSpecProperties.x;
    #endif
    float specPower = cMatSpecProperties.y / 255.0;

    // Take fogging into account here so that deferred lights do not need to calculate it
    oDiff = GetReverseFogFactor(iDepth) * float4(diffColor, specStrength);
    oNormal = float4(normal * 0.5 + 0.5, specPower);
    oDepth = iDepth;
}
