#include "Common.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef DIFFMAP
        float2 iTexCoord : TEXCOORD0,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
        out float4 oColor : COLOR0,
    #endif
    #ifdef DIFFMAP
        out float2 oTexCoord : TEXCOORD0,
    #endif
    out float4 oPos : POSITION)
{
    GetPosition(iPos, oPos);
    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
    #ifdef DIFFMAP
        oTexCoord = iTexCoord;
    #endif
}

void PS(
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #if defined(DIFFMAP) || defined(ALPHAMAP)
        float2 iTexCoord : TEXCOORD0,
    #endif
    out float4 oColor : COLOR0)
{
    float4 diffColor = cMatDiffColor;
    
    #ifdef VERTEXCOLOR
        diffColor *= iColor;
    #endif
    
    #if (!defined(DIFFMAP)) && (!defined(ALPHAMAP))
        oColor = diffColor;
    #endif
    #ifdef DIFFMAP
        oColor = diffColor * tex2D(sDiffMap, iTexCoord);
    #endif
    #ifdef ALPHAMAP
        float alphaInput = tex2D(sDiffMap, iTexCoord).a;
        oColor = float4(diffColor.rgb, diffColor.a * alphaInput);
    #endif
}
