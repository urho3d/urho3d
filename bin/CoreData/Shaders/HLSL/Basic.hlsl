#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef DIFFMAP
        float2 iTexCoord : TEXCOORD0,
    #endif
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
    #ifdef DIFFMAP
        out float2 oTexCoord : TEXCOORD0,
    #endif
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    #if defined(D3D11) && defined(CLIPPLANE)
        out float oClip : SV_CLIPDISTANCE0,
    #endif
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);

    #if defined(D3D11) && defined(CLIPPLANE)
        oClip = dot(oPos, cClipPlane);
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
    #ifdef DIFFMAP
        oTexCoord = iTexCoord;
    #endif
}

void PS(
    #if defined(DIFFMAP) || defined(ALPHAMAP)
        float2 iTexCoord : TEXCOORD0,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #if defined(D3D11) && defined(CLIPPLANE)
        float iClip : SV_CLIPDISTANCE0,
    #endif
    out float4 oColor : OUTCOLOR0)
{
    float4 diffColor = cMatDiffColor;

    #ifdef VERTEXCOLOR
        diffColor *= iColor;
    #endif

    #if (!defined(DIFFMAP)) && (!defined(ALPHAMAP))
        oColor = diffColor;
    #endif
    #ifdef DIFFMAP
        float4 diffInput = Sample2D(DiffMap, iTexCoord);
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
        oColor = diffColor * diffInput;
    #endif
    #ifdef ALPHAMAP
        float alphaInput = Sample2D(DiffMap, iTexCoord).a;
        oColor = float4(diffColor.rgb, diffColor.a * alphaInput);
    #endif
}
