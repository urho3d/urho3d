/*============================================================================

                  FXAA v2 CONSOLE by TIMOTHY LOTTES @ NVIDIA

============================================================================*/

// Adapted for Urho3D from http://timothylottes.blogspot.com/2011/04/nvidia-fxaa-ii-for-console.html

#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"

uniform float4 cFXAAParams;

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oScreenPos : TEXCOORD0)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iScreenPos : TEXCOORD0,
    out float4 oColor : COLOR0)
{
    float FXAA_SUBPIX_SHIFT = 1.0/4.0; // Not used
    float FXAA_SPAN_MAX = 8.0;
    float FXAA_REDUCE_MUL = 1.0/8.0;
    float FXAA_REDUCE_MIN = 1.0/128.0;

    float2 posOffset = cGBufferInvSize.xy * cFXAAParams.x;

    float3 rgbNW = Sample(sDiffMap, iScreenPos + float2(-posOffset.x, -posOffset.y)).rgb;
    float3 rgbNE = Sample(sDiffMap, iScreenPos + float2(posOffset.x, -posOffset.y)).rgb;
    float3 rgbSW = Sample(sDiffMap, iScreenPos + float2(-posOffset.x, posOffset.y)).rgb;
    float3 rgbSE = Sample(sDiffMap, iScreenPos + float2(posOffset.x, posOffset.y)).rgb;
    float3 rgbM  = Sample(sDiffMap, iScreenPos).rgb;

    float3 luma = float3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    if (((lumaMax - lumaMin) / lumaMin) >= cFXAAParams.y)
    {
        float2 dir;
        dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
        dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
        float dirReduce = max(
            (lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL),
            FXAA_REDUCE_MIN);
        float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
        dir = min(float2( FXAA_SPAN_MAX,  FXAA_SPAN_MAX),
              max(float2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
              dir * rcpDirMin)) * cGBufferInvSize.xy;
    
        dir *= cFXAAParams.z;
    
        float3 rgbA = (1.0/2.0) * (
            Sample(sDiffMap, iScreenPos + dir * (1.0/3.0 - 0.5)).xyz +
            Sample(sDiffMap, iScreenPos + dir * (2.0/3.0 - 0.5)).xyz);
        float3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (
            Sample(sDiffMap, iScreenPos + dir * (0.0/3.0 - 0.5)).xyz +
            Sample(sDiffMap, iScreenPos + dir * (3.0/3.0 - 0.5)).xyz);
        float lumaB = dot(rgbB, luma);
        
        float3 rgbOut;
        if((lumaB < lumaMin) || (lumaB > lumaMax))
            rgbOut = rgbA;
        else
            rgbOut = rgbB;

        oColor = float4(rgbOut, 1.0);
    }
    else
        oColor = float4(rgbM, 1.0);
}
