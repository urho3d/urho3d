#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD4,
    #endif
    #ifndef NOUV
        float2 iTexCoord : TEXCOORD0,
    #endif
    out float3 oTexCoord : TEXCOORD0,
    out float4 oPos : OUTPOSITION)
{
    // Define a 0,0 UV coord if not expected from the vertex data
    #ifdef NOUV
    float2 iTexCoord = float2(0.0, 0.0);
    #endif
    
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = float3(GetTexCoord(iTexCoord), GetDepth(oPos));
}

void PS(
    float3 iTexCoord : TEXCOORD0,
    out float4 oColor : OUTCOLOR0)
{
    #ifdef ALPHAMASK
        float alpha = Sample2D(sDiffMap, iTexCoord.xy).a;
        if (alpha < 0.5)
            discard;
    #endif

    oColor = iTexCoord.z;
}
