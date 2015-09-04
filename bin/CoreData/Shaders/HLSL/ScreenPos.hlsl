#ifdef COMPILEVS
float4 GetScreenPos(float4 clipPos)
{
    return float4(
        clipPos.x * cGBufferOffsets.z + cGBufferOffsets.x * clipPos.w,
        -clipPos.y * cGBufferOffsets.w + cGBufferOffsets.y * clipPos.w,
        0.0,
        clipPos.w);
}

float2 GetScreenPosPreDiv(float4 clipPos)
{
    return float2(
        clipPos.x / clipPos.w * cGBufferOffsets.z + cGBufferOffsets.x,
        -clipPos.y / clipPos.w * cGBufferOffsets.w + cGBufferOffsets.y);
}

float2 GetQuadTexCoord(float4 clipPos)
{
    return float2(
        clipPos.x / clipPos.w * 0.5 + 0.5,
        -clipPos.y / clipPos.w * 0.5 + 0.5);
}

float2 GetQuadTexCoordNoFlip(float3 worldPos)
{
    return float2(
        worldPos.x * 0.5 + 0.5,
        -worldPos.y * 0.5 + 0.5);
}

float3 GetFarRay(float4 clipPos)
{
    float3 viewRay = float3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        cFrustumSize.z);

    return mul(viewRay, cCameraRot);
}

float3 GetNearRay(float4 clipPos)
{
    float3 viewRay = float3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        0.0);

    return mul(viewRay, cCameraRot) * cDepthMode.z;
}
#endif
