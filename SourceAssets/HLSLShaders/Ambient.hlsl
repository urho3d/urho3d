#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef NUMVERTEXLIGHTS
        float3 iNormal : NORMAL,
    #endif
    float2 iTexCoord : TEXCOORD0,
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD2,
    #endif
    #ifdef BILLBOARD
        float2 iSize : TEXCOORD1,
    #endif
    out float4 oTexCoord : TEXCOORD0,
    out float3 oVertexLighting : TEXCOORD1,
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = float4(GetTexCoord(iTexCoord), GetZonePos(worldPos), GetDepth(oPos));

    oVertexLighting = 0.0;
    #ifdef NUMVERTEXLIGHTS
    float3 normal = GetWorldNormal(modelMatrix);
    for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
        oVertexLighting += GetVertexLight(i, worldPos, normal) * cVertexLights[i * 3].rgb;
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
}

void PS(float4 iTexCoord : TEXCOORD0,
    float3 iVertexLighting : TEXCOORD1,
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffColor = cMatDiffColor * tex2D(sDiffMap, iTexCoord.xy);
    #else
        float4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= iColor;
    #endif

    float3 finalColor = (GetAmbient(iTexCoord.z) + iVertexLighting) * diffColor.rgb;

    oColor = float4(GetFog(finalColor, iTexCoord.w), diffColor.a);
}
