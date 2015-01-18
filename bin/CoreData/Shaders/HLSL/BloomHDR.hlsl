#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"
#include "PostProcess.hlsl"

uniform float cBloomHDRThreshold;
uniform float2 cBloomHDRBlurDir;
uniform float cBloomHDRBlurRadius;
uniform float cBloomHDRBlurSigma;
uniform float2 cBloomHDRMix;
uniform float2 cBright2Offsets;
uniform float2 cBright4Offsets;
uniform float2 cBright8Offsets;
uniform float2 cBright16Offsets;
uniform float2 cBright2InvSize;
uniform float2 cBright4InvSize;
uniform float2 cBright8InvSize;
uniform float2 cBright16InvSize;

static const int BlurKernelSize = 5;

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oTexCoord : TEXCOORD0,
    out float2 oScreenPos : TEXCOORD1)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);

    oTexCoord = GetQuadTexCoord(oPos);

    #ifdef BLUR2
    oTexCoord = GetQuadTexCoord(oPos) + cBright2Offsets;
    #endif

    #ifdef BLUR4
    oTexCoord = GetQuadTexCoord(oPos) + cBright4Offsets;
    #endif

    #ifdef BLUR8
    oTexCoord = GetQuadTexCoord(oPos) + cBright8Offsets;
    #endif

    #ifdef BLUR16
    oTexCoord = GetQuadTexCoord(oPos) + cBright16Offsets;
    #endif

    #ifdef COMBINE2
    oTexCoord = GetQuadTexCoord(oPos) + cBright2Offsets;
    #endif

    #ifdef COMBINE4
    oTexCoord = GetQuadTexCoord(oPos) + cBright4Offsets;
    #endif

    #ifdef COMBINE8
    oTexCoord = GetQuadTexCoord(oPos) + cBright8Offsets;
    #endif

    #ifdef COMBINE16
    oTexCoord = GetQuadTexCoord(oPos) + cBright16Offsets;
    #endif

    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iTexCoord : TEXCOORD0,
    float2 iScreenPos : TEXCOORD1,
    out float4 oColor : COLOR0)
{
    #ifdef BRIGHT
    float3 color = tex2D(sDiffMap, iScreenPos).rgb;
    oColor = float4(max(color - cBloomHDRThreshold, 0.0), 1.0);
    #endif

    #ifdef BLUR16
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright16InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, iTexCoord);
    #endif

    #ifdef BLUR8
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright8InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, iTexCoord);
    #endif

    #ifdef BLUR4
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright4InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, iTexCoord);
    #endif

    #ifdef BLUR2
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright2InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, sDiffMap, iTexCoord);
    #endif

    #ifdef COMBINE16
    oColor = tex2D(sDiffMap, iScreenPos) + tex2D(sNormalMap, iTexCoord);
    #endif

    #ifdef COMBINE8
    oColor = tex2D(sDiffMap, iScreenPos) + tex2D(sNormalMap, iTexCoord);
    #endif

    #ifdef COMBINE4
    oColor = tex2D(sDiffMap, iScreenPos) + tex2D(sNormalMap, iTexCoord);
    #endif

    #ifdef COMBINE2
    float3 color = tex2D(sDiffMap, iScreenPos).rgb * cBloomHDRMix.x;
    float3 bloom = tex2D(sNormalMap, iTexCoord).rgb * cBloomHDRMix.y;
    oColor = float4(color + bloom, 1.0);
    #endif
}
