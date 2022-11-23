#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

// D3D11 constant buffer
cbuffer CustomVS : register(b6)
{
    float cWindHeightFactor;
    float cWindHeightPivot;
    float cWindPeriod;
    float2 cWindWorldSpacing;
    #ifdef WINDSTEMAXIS
        float3 cWindStemAxis;
    #endif
}

void VS(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD4,
    #endif
    float2 iTexCoord : TEXCOORD0,
    #ifdef VSM_SHADOW
        out float4 oTexCoord : TEXCOORD0,
    #else
        out float2 oTexCoord : TEXCOORD0,
    #endif
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);

    #ifdef WINDSTEMAXIS
        float stemDistance = dot(iPos, cWindStemAxis);
    #else
        float stemDistance = iPos.y;
    #endif
    float windStrength = max(stemDistance - cWindHeightPivot, 0.0) * cWindHeightFactor;
    float windPeriod = cElapsedTime * cWindPeriod + dot(worldPos.xz, cWindWorldSpacing);
    worldPos.x += windStrength * sin(windPeriod);
    worldPos.z -= windStrength * cos(windPeriod);

    oPos = GetClipPos(worldPos);
    #ifdef VSM_SHADOW
        oTexCoord = float4(GetTexCoord(iTexCoord), oPos.z, oPos.w);
    #else
        oTexCoord = GetTexCoord(iTexCoord);
    #endif
}
