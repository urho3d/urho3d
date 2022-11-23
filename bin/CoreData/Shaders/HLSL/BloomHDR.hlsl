#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"
#include "PostProcess.hlsl"

// D3D11 constant buffers
#ifdef COMPILEPS
cbuffer CustomPS : register(b6)
{
    float cBloomHDRThreshold;
    float2 cBloomHDRBlurDir;
    float cBloomHDRBlurRadius;
    float cBloomHDRBlurSigma;
    float2 cBloomHDRMix;
    float2 cBright2InvSize;
    float2 cBright4InvSize;
    float2 cBright8InvSize;
    float2 cBright16InvSize;
}
#endif

static const int BlurKernelSize = 5;

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
    #ifdef BRIGHT
    float3 color = Sample2D(DiffMap, iScreenPos).rgb;
    oColor = float4(max(color - cBloomHDRThreshold, 0.0), 1.0);
    #endif

    #ifdef BLUR16
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright16InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, tDiffMap, sDiffMap, iTexCoord);
    #endif

    #ifdef BLUR8
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright8InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, tDiffMap, sDiffMap, iTexCoord);
    #endif

    #ifdef BLUR4
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright4InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, tDiffMap, sDiffMap, iTexCoord);
    #endif

    #ifdef BLUR2
    oColor = GaussianBlur(BlurKernelSize, cBloomHDRBlurDir, cBright2InvSize * cBloomHDRBlurRadius, cBloomHDRBlurSigma, tDiffMap, sDiffMap, iTexCoord);
    #endif

    #ifdef COMBINE16
    oColor = Sample2D(DiffMap, iScreenPos) + Sample2D(NormalMap, iTexCoord);
    #endif

    #ifdef COMBINE8
    oColor = Sample2D(DiffMap, iScreenPos) + Sample2D(NormalMap, iTexCoord);
    #endif

    #ifdef COMBINE4
    oColor = Sample2D(DiffMap, iScreenPos) + Sample2D(NormalMap, iTexCoord);
    #endif

    #ifdef COMBINE2
    float3 color = Sample2D(DiffMap, iScreenPos).rgb * cBloomHDRMix.x;
    float3 bloom = Sample2D(NormalMap, iTexCoord).rgb * cBloomHDRMix.y;
    oColor = float4(color + bloom, 1.0);
    #endif
}
