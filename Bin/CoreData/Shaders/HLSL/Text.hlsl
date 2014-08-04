#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

#ifdef TEXT_EFFECT_SHADOW
uniform float2 cShadowOffset;
uniform float4 cShadowColor;
#endif

#ifdef TEXT_EFFECT_STROKE
uniform float4 cStrokeColor;
#endif

void VS(float4 iPos : POSITION,
        float4 iColor : COLOR0,
        float2 iTexCoord : TEXCOORD0,
        out float4 oPos : POSITION,
        out float4 oColor : COLOR0,
        out float2 oTexCoord : TEXCOORD0)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oColor = iColor;
    oTexCoord = iTexCoord;
}

void PS(float4 iColor : COLOR0,
        float2 iTexCoord : TEXCOORD0,
        out float4 oColor : COLOR0)
{
    oColor.rgb = iColor.rgb;

#ifdef SIGNED_DISTANCE_FIELD
    float distance = tex2D(sDiffMap, iTexCoord).a;
    if (distance < 0.5f)
    {
    #ifdef TEXT_EFFECT_SHADOW
        if (tex2D(sDiffMap, iTexCoord - cShadowOffset).a > 0.5f)
            oColor = cShadowColor;
        else
    #endif
        oColor.a = 0.0f;
    }
    else
    {
    #ifdef TEXT_EFFECT_STROKE
        if (distance < 0.525f)
            oColor.rgb = cStrokeColor.rgb;
    #endif

    #ifdef TEXT_EFFECT_SHADOW
        if (tex2D(sDiffMap, iTexCoord + cShadowOffset).a < 0.5f)
            oColor.a = iColor.a;
        else
    #endif
        oColor.a = iColor.a * smoothstep(0.5f, 0.505f, distance);
    }
#else
    oColor.a = iColor.a * tex2D(sDiffMap, iTexCoord).a;
#endif
}