#include "Common.hlsl"

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
    #ifdef ORTHO
        float depth = Sample(sDepthBuffer, iScreenPos).r;
        float3 worldPos = lerp(iNearRay, iFarRay, depth) + cCameraPosPS;
    #else
        float depth = Sample(sDepthBuffer, iScreenPos).r;
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

    // Sample the pixels this frame and previous, assume we are going to blend
    float4 current = Sample(sDiffBuffer, iScreenPos);
    float4 last = Sample(sNormalBuffer, screenPosLast);

    // If position is outside viewport, must disable blending
    if ((screenPosLast.x < cGBufferViewport.x) || (screenPosLast.y < cGBufferViewport.y) ||
        (screenPosLast.x > cGBufferViewport.z) || (screenPosLast.y > cGBufferViewport.w))
        last = current;

    // Compare coarse depth this and previous frame to check for ghosting
    // Set coarse depth threshold to be more than 1/255 so that depth gradients do not trigger it
    float threshold = 0.005;
    if (abs(last.a - current.a) > threshold)
    {
        // If we seem to have ghosting, check if it is an edge. Always allow blending on the edges
        float2 hOffset = float2(cSampleOffsets.x, 0);
        float2 vOffset = float2(0, cSampleOffsets.y);
        float4 adjacent = float4(Sample(sDiffBuffer, iScreenPos - hOffset).a,
            Sample(sDiffBuffer, iScreenPos + hOffset).a,
            Sample(sDiffBuffer, iScreenPos - vOffset).a,
            Sample(sDiffBuffer, iScreenPos + vOffset).a);

        float edge = dot(abs(adjacent - current.a) > threshold, 1);
        if (edge == 0)
            last = current;
    }

    oColor = cAntiAliasWeights.x * current + cAntiAliasWeights.y * last;
}
