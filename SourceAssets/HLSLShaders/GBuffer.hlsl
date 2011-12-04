#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

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
    #ifdef HWDEPTH
        out float2 oTexCoord : TEXCOORD0,
    #else
        out float3 oTexCoord : TEXCOORD0,
    #endif
    out float3 oNormal : TEXCOORD1,
    #ifdef NORMALMAP
        out float3 oTangent : TEXCOORD2,
        out float3 oBitangent : TEXCOORD3,
    #endif
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    #ifdef HWDEPTH
        oTexCoord = GetTexCoord(iTexCoord);
    #else
        oTexCoord = float3(GetTexCoord(iTexCoord), GetDepth(oPos));
    #endif

    oNormal = GetWorldNormal(modelMatrix);
    #ifdef NORMALMAP
        oTangent = GetWorldTangent(modelMatrix);
        oBitangent = cross(oTangent, oNormal) * iTangent.w;
    #endif
}

void PS(
    #ifdef HWDEPTH
        float2 iTexCoord : TEXCOORD0,
    #else
        float3 iTexCoord : TEXCOORD0,
    #endif
    float3 iNormal : TEXCOORD1,
    #ifdef NORMALMAP
        float3 iTangent : TEXCOORD2,
        float3 iBitangent : TEXCOORD3,
    #endif
    #ifndef HWDEPTH
        out float4 oDepth : COLOR1,
    #endif
    out float4 oNormal : COLOR0)
{
    #ifdef ALPHAMASK
        float4 diffInput = tex2D(sDiffMap, iTexCoord.xy);
        if (diffInput.a < 0.5)
            discard;
    #endif

    #ifdef NORMALMAP
        float3x3 tbn = float3x3(iTangent, iBitangent, iNormal);
        float3 normal = normalize(mul(DecodeNormal(tex2D(sNormalMap, iTexCoord.xy)), tbn));
    #else
        float3 normal = normalize(iNormal);
    #endif

    #ifdef SPECMAP
        float specStrength = tex2D(sSpecMap, iTexCoord.xy).g * cMatSpecProperties.x;
    #else
        float specStrength = cMatSpecProperties.x;
    #endif
    float specPower = cMatSpecProperties.y / 255.0;

    oNormal = float4(normal * 0.5 + 0.5, specPower);
    #ifndef HWDEPTH
        oDepth = iTexCoord.z;
    #endif
}
