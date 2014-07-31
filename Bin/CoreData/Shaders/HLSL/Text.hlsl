#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

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
        oColor.a = 0.0f;
    else
        oColor.a = iColor.a;

    // Stroke effect testing
    if (distance < 0.53f)
        oColor.r = 1.0f;

    float width = 0.015f;
    oColor.a *= smoothstep(0.5f - width, 0.5f + width, distance);
#else
    oColor.a = iColor.a * tex2D(sDiffMap, iTexCoord).a;
#endif
}

