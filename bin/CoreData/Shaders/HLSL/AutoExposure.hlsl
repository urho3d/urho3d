#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"
#include "PostProcess.hlsl"

uniform float cAutoExposureAdaptRate;
uniform float2 cAutoExposureLumRange;
uniform float cAutoExposureMiddleGrey;
uniform float2 cHDR128InvSize;
uniform float2 cLum64InvSize;
uniform float2 cLum16InvSize;
uniform float2 cLum4InvSize;

float GatherAvgLum(Texture2D tex, SamplerState texSampler, float2 texCoord, float2 texelSize)
{
    float lumAvg = 0.0;
    lumAvg += tex.Sample(texSampler, texCoord + float2(0.0, 0.0) * texelSize).r;
    lumAvg += tex.Sample(texSampler, texCoord + float2(0.0, 2.0) * texelSize).r;
    lumAvg += tex.Sample(texSampler, texCoord + float2(2.0, 2.0) * texelSize).r;
    lumAvg += tex.Sample(texSampler, texCoord + float2(2.0, 0.0) * texelSize).r;
    return lumAvg / 4.0;
}

void VS(float4 iPos : POSITION,
    out float2 oTexCoord : TEXCOORD0,
    out float2 oScreenPos : TEXCOORD1,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetQuadTexCoord(oPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iTexCoord : TEXCOORD0,
    float2 iScreenPos : TEXCOORD1,
    out float4 oColor : OUTCOLOR0)
{
    #ifdef LUMINANCE64
    float logLumSum = 0.0;
    logLumSum += log(dot(Sample2D(DiffMap, iTexCoord + float2(0.0, 0.0) * cHDR128InvSize).rgb, LumWeights) + 1e-5);
    logLumSum += log(dot(Sample2D(DiffMap, iTexCoord + float2(0.0, 2.0) * cHDR128InvSize).rgb, LumWeights) + 1e-5);
    logLumSum += log(dot(Sample2D(DiffMap, iTexCoord + float2(2.0, 2.0) * cHDR128InvSize).rgb, LumWeights) + 1e-5);
    logLumSum += log(dot(Sample2D(DiffMap, iTexCoord + float2(2.0, 0.0) * cHDR128InvSize).rgb, LumWeights) + 1e-5);
    oColor = logLumSum;
    #endif

    #ifdef LUMINANCE16
    oColor = GatherAvgLum(tDiffMap, sDiffMap, iTexCoord, cLum64InvSize);
    #endif

    #ifdef LUMINANCE4
    oColor = GatherAvgLum(tDiffMap, sDiffMap, iTexCoord, cLum16InvSize);
    #endif

    #ifdef LUMINANCE1
    oColor = exp(GatherAvgLum(tDiffMap, sDiffMap, iTexCoord, cLum4InvSize) / 16.0);
    #endif

    #ifdef ADAPTLUMINANCE
    float adaptedLum = Sample2D(DiffMap, iTexCoord).r;
    float lum = clamp(Sample2D(NormalMap, iTexCoord).r, cAutoExposureLumRange.x, cAutoExposureLumRange.y);
    oColor = adaptedLum + (lum - adaptedLum) * (1.0 - exp(-cDeltaTimePS * cAutoExposureAdaptRate));
    #endif

    #ifdef EXPOSE
    float3 color = Sample2D(DiffMap, iScreenPos).rgb;
    float adaptedLum = Sample2D(NormalMap, iTexCoord).r;
    oColor = float4(color * (cAutoExposureMiddleGrey / adaptedLum), 1.0);
    #endif
}
