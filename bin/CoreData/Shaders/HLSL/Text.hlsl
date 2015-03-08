#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

#ifndef D3D11

// D3D9 uniforms
uniform float2 cShadowOffset;
uniform float4 cShadowColor;
uniform float4 cStrokeColor;

#else

#ifdef COMPILEPS
// D3D11 constant buffers
cbuffer CustomPS : register(b6)
{
    float2 cShadowOffset;
    float4 cShadowColor;
    float4 cStrokeColor;
}
#endif

#endif

void VS(float4 iPos : POSITION,
    float2 iTexCoord : TEXCOORD0,
    out float2 oTexCoord : TEXCOORD0,
    float4 iColor : COLOR0,
    out float4 oColor : COLOR0,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oColor = iColor;
    oTexCoord = iTexCoord;
}

void PS(float2 iTexCoord : TEXCOORD0,
    float4 iColor : COLOR0,
    out float4 oColor : OUTCOLOR0)
{
    oColor.rgb = iColor.rgb;

#ifdef SIGNED_DISTANCE_FIELD
    float distance = Sample2D(DiffMap, iTexCoord).a;
    if (distance < 0.5f)
    {
    #ifdef TEXT_EFFECT_SHADOW
        if (Sample2D(DiffMap, iTexCoord - cShadowOffset).a > 0.5f)
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
        if (Sample2D(DiffMap, iTexCoord + cShadowOffset).a < 0.5f)
            oColor.a = iColor.a;
        else
    #endif
        oColor.a = iColor.a * smoothstep(0.5f, 0.505f, distance);
    }
#else
    oColor.a = iColor.a * Sample2D(DiffMap, iTexCoord).a;
#endif
}