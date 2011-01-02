#include "Common.hlsl"

void vs(float4 iPos : POSITION,
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #ifdef DIFFMAP
        float2 iTexCoord : TEXCOORD0,
    #endif
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    #ifdef DIFFMAP
        out float2 oTexCoord : TEXCOORD0,
    #endif
    out float4 oPos : POSITION)
{
    evaluatePosition(iPos, oPos);
    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
    #ifdef DIFFMAP
        oTexCoord = iTexCoord;
    #endif
}

void ps(
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #if defined(DIFFMAP) || defined(ALPHAMAP)
        float2 iTexCoord : TEXCOORD0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef VERTEXCOLOR
        float4 baseColor = iColor;
    #else
        float4 baseColor = cMatDiffColor;
    #endif
    
    #if (!defined(DIFFMAP)) && (!defined(ALPHAMAP))
        oColor = baseColor;
    #endif
    #ifdef DIFFMAP
        oColor = baseColor * tex2D(sDiffMap, iTexCoord);
    #endif
    #ifdef ALPHAMAP
        float alphaInput = tex2D(sDiffMap, iTexCoord).a;
        oColor = float4(baseColor.rgb, baseColor.a * alphaInput);
    #endif
}
