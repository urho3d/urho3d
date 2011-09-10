#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float3 oFarRay : TEXCOORD1,
    #ifdef ORTHO
        out float3 oNearRay : TEXCOORD2,
    #endif
    out float2 oScreenPos : TEXCOORD0)
{
    GetPosition(iPos, oPos);
    oScreenPos = GetScreenPosPreDiv(oPos);

    oFarRay = GetFarRay(oPos);
    #ifdef ORTHO
        oNearRay = GetNearRay(oPos);
    #endif
}

void PS(float2 iScreenPos : TEXCOORD0,
    float3 iFarRay : TEXCOORD1,
    #ifdef ORTHO
        float3 iNearRay : TEXCOORD2,
    #endif
    out float4 oColor : COLOR0)
{
    float2 hOffset = float2(cSampleOffsets.x, 0);
    float2 vOffset = float2(0, cSampleOffsets.y);
    float3 current = Sample(sDiffBuffer, iScreenPos).rgb;

    #ifdef FALLBACK
        float4 diffInput = Sample(sDetailMap, iScreenPos);
        float4 normalInput = Sample(sEnvMap, iScreenPos);
    #endif

    // Reconstruct position for this frame's pixel
    #ifdef ORTHO
        #ifdef FALLBACK
            float depth = DecodeDepth(float2(diffInput.w, normalInput.w));
        #else
            float depth = Sample(sDepthBuffer, iScreenPos).r;
        #endif
        float3 worldPos = lerp(iNearRay, iFarRay, depth) + cCameraPosPS;
    #else
        #if defined(LINEAR)
            float depth = Sample(sDepthBuffer, iScreenPos).r;
        #elif defined(FALLBACK)
            float depth = DecodeDepth(float2(diffInput.w, normalInput.w));
        #else
            float depth = ReconstructDepth(Sample(sDepthBuffer, iScreenPos).r);
        #endif
        float3 worldPos = iFarRay * depth + cCameraPosPS;
    #endif

    // Calculate G-buffer position for pixel on last frame
    float4 clipPosLast = mul(float4(worldPos, 1.0), cViewProjPS);
    #ifdef ORTHO
        float2 screenPosLast = float2(
            clipPosLast.x * cGBufferOffsetsPS.z + cGBufferOffsetsPS.x,
            -clipPosLast.y * cGBufferOffsetsPS.w + cGBufferOffsetsPS.y);
    #else
       float2 screenPosLast = float2(
            clipPosLast.x / clipPosLast.w * cGBufferOffsetsPS.z + cGBufferOffsetsPS.x,
            -clipPosLast.y / clipPosLast.w * cGBufferOffsetsPS.w + cGBufferOffsetsPS.y);
    #endif

    float3 last = Sample(sNormalBuffer, screenPosLast).rgb;
    float3 color = cSampleOffsets.z * current + cSampleOffsets.w * last;

    // To eliminate ghosting, clamp RGB values to the pixel's neighbours
    // This is rather expensive, so only do it if there is a large color difference
    if (dot(abs(current - last), 1.0) > 0.25)
    {
        float3 left = Sample(sDiffBuffer, iScreenPos - hOffset).rgb;
        float3 right = Sample(sDiffBuffer, iScreenPos + hOffset).rgb;
        float3 up = Sample(sDiffBuffer, iScreenPos - vOffset).rgb;
        float3 down = Sample(sDiffBuffer, iScreenPos + vOffset).rgb;
        float3 minColor = min(min(left, right), min(up, down));
        float3 maxColor = max(max(left, right), max(up, down));
        oColor = float4(clamp(color, minColor, maxColor), 1.0);
    }
    else
        oColor = float4(color, 1.0);
}
