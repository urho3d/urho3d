#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD2,
    #endif
    #ifdef ALPHAMASK
        float2 iTexCoord : TEXCOORD0,
        out float2 oTexCoord : TEXCOORD0,
    #endif
    #ifdef FALLBACK
        out float4 oClipPos : TEXCOORD1,
    #endif
    out float4 oPos : POSITION)
{
    #if defined(SKINNED)
        GetPositionSkinned(iPos, iBlendWeights, iBlendIndices, oPos);
    #elif defined(INSTANCED)
        GetPositionInstanced(iPos, iModelInstance, oPos);
    #else
        GetPosition(iPos, oPos);
    #endif

    #ifdef ALPHAMASK
        oTexCoord = GetTexCoord(iTexCoord);
    #endif
    #ifdef FALLBACK
        oClipPos = oPos;
    #endif
}

void PS(
    #ifdef ALPHAMASK
        float2 iTexCoord : TEXCOORD0,
    #endif
    #ifdef FALLBACK
        float4 iClipPos : TEXCOORD1,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef ALPHAMASK
        float alpha = tex2D(sDiffMap, iTexCoord).a;
    #else
        const float alpha = 1.0;
    #endif

    #ifdef FALLBACK
        float depth = min(iClipPos.z / iClipPos.w + cShadowIntensity.w, 1.0);
        oColor = float4(EncodeDepth(depth), 1.0, alpha);
    #else
        oColor = alpha;
    #endif
}
