#include "Common.hlsl"

void vs(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oScreenPos : TEXCOORD0,
    out float2 oLeftPos : TEXCOORD1,
    out float2 oRightPos : TEXCOORD2,
    out float2 oUpPos : TEXCOORD3,
    out float2 oDownPos : TEXCOORD4)
{
    evaluatePosition(iPos, oPos);
    oScreenPos = calculateScreenPosPreDiv(oPos);
    oLeftPos = oScreenPos - float2(2.0 * cGBufferOffsets.x, 0.0);
    oRightPos = oScreenPos + float2(2.0 * cGBufferOffsets.x, 0.0);
    oUpPos = oScreenPos - float2(0.0, 2.0 * cGBufferOffsets.y);
    oDownPos = oScreenPos + float2(0.0, 2.0 * cGBufferOffsets.y);
}

void ps(float2 iScreenPos : TEXCOORD0,
    float2 iLeftPos : TEXCOORD1,
    float2 iRightPos : TEXCOORD2,
    float2 iUpPos : TEXCOORD3,
    float2 iDownPos : TEXCOORD4,
    out float4 oColor : COLOR0)
{
    // Calculate color deviation in 4 directions
    float3 colorBase = tex2D(sDiffBuffer, iScreenPos).rgb;
    float3 colorDiff1 = colorBase - tex2D(sDiffBuffer, iLeftPos).rgb;
    float3 colorDiff2 = colorBase - tex2D(sDiffBuffer, iRightPos).rgb;
    float3 colorDiff3 = colorBase - tex2D(sDiffBuffer, iUpPos).rgb;
    float3 colorDiff4 = colorBase - tex2D(sDiffBuffer, iDownPos).rgb;

    // Scale the deviation according to inverse brightness of pixel, but only up to a specified scale value
    float scale = min(1.0 / dot(colorBase, colorBase), cEdgeFilterParams.w);

    // Check which deviations exceed a threshold
    float4 diffs = (scale * float4(
        dot(colorDiff1, colorDiff1),
        dot(colorDiff2, colorDiff2),
        dot(colorDiff3, colorDiff3),
        dot(colorDiff4, colorDiff4)
    )) > cEdgeFilterParams.x;

    // Sum and clamp to maximum filtering level
    float t = min(dot(diffs, cEdgeFilterParams.y), cEdgeFilterParams.z);

    // Blend between pixel center & pixel corners
    float2 offset1 = t * cSampleOffsets.xz;
    float2 offset2 = t * cSampleOffsets.yz;

    oColor = float4(
        (tex2D(sDiffBuffer, iScreenPos + offset1) +
        tex2D(sDiffBuffer, iScreenPos + offset2) +
        tex2D(sDiffBuffer, iScreenPos - offset1) +
        tex2D(sDiffBuffer, iScreenPos - offset2)) * 0.25
    );
}
