#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,
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
    out float2 oTexCoord : TEXCOORD0,
    out float oDepth : TEXCOORD1,
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetTexCoord(iTexCoord);
    oDepth = GetDepth(oPos);

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    float iDepth : TEXCOORD1,
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffColor = cMatDiffColor * tex2D(sDiffMap, iTexCoord);
        #ifdef ALPHAMASK
            if (diffColor.a < 0.5)
                discard;
        #endif
    #else
        float4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= iColor;
    #endif

    oColor = float4(GetFog(diffColor.rgb, iDepth), diffColor.a);
}