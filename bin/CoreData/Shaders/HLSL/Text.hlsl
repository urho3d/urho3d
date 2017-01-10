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

// See notes in GLSL shader
#if defined(COMPILEPS) && defined(SIGNED_DISTANCE_FIELD)
    float GetAlpha(float distance, float width)
    {
        return smoothstep(0.5 - width, 0.5 + width, distance);
    }

    // Comment this define to turn off supersampling
    #define SUPERSAMPLING
#endif


void PS(float2 iTexCoord : TEXCOORD0,
    float4 iColor : COLOR0,
    out float4 oColor : OUTCOLOR0)
{
#ifdef SIGNED_DISTANCE_FIELD
    oColor.rgb = iColor.rgb;
    float distance = Sample2D(DiffMap, iTexCoord).a;

    #ifdef TEXT_EFFECT_STROKE
        #ifdef SUPERSAMPLING
            float outlineFactor = smoothstep(0.5, 0.525, distance); // Border of glyph
            oColor.rgb = lerp(cStrokeColor.rgb, iColor.rgb, outlineFactor);
        #else
            if (distance < 0.525)
                oColor.rgb = cStrokeColor.rgb;
        #endif
    #endif

    #ifdef TEXT_EFFECT_SHADOW
        if (Sample2D(DiffMap, iTexCoord - cShadowOffset).a > 0.5 && distance <= 0.5)
            oColor = cShadowColor;
        #ifndef SUPERSAMPLING
        else if (distance <= 0.5)
            oColor.a = 0.0;
        #endif
        else
    #endif
        {
            float width = fwidth(distance);
            float alpha = GetAlpha(distance, width);

            #ifdef SUPERSAMPLING
                float2 deltaUV = 0.354 * fwidth(iTexCoord); // (1.0 / sqrt(2.0)) / 2.0 = 0.354
                float4 square = float4(iTexCoord - deltaUV, iTexCoord + deltaUV);

                float distance2 = Sample2D(DiffMap, square.xy).a;
                float distance3 = Sample2D(DiffMap, square.zw).a;
                float distance4 = Sample2D(DiffMap, square.xw).a;
                float distance5 = Sample2D(DiffMap, square.zy).a;

                alpha += GetAlpha(distance2, width)
                       + GetAlpha(distance3, width)
                       + GetAlpha(distance4, width)
                       + GetAlpha(distance5, width);
            
                // For calculating of average correct would be dividing by 5.
                // But when text is blurred, its brightness is lost. Therefore divide by 4.
                alpha = alpha * 0.25;
            #endif

            oColor.a = alpha;
        }
#else
    #ifdef ALPHAMAP
        oColor.rgb = iColor.rgb;
        oColor.a = iColor.a * Sample2D(DiffMap, iTexCoord).a;
    #else
        oColor = iColor* Sample2D(DiffMap, iTexCoord);
    #endif
#endif
}
