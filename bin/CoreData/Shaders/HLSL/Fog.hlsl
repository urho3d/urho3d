#ifdef COMPILEPS
float3 GetFog(float3 color, float fogFactor)
{
    return lerp(cFogColor, color, fogFactor);
}

float3 GetLitFog(float3 color, float fogFactor)
{
    return color * fogFactor;
}

float GetFogFactor(float depth)
{
    return saturate((cFogParams.x - depth) * cFogParams.y);
}

float GetHeightFogFactor(float depth, float height)
{
    float fogFactor = GetFogFactor(depth);
    float heightFogFactor = (height - cFogParams.z) * cFogParams.w;
    heightFogFactor = 1.0 - saturate(exp(-(heightFogFactor * heightFogFactor)));
    return min(heightFogFactor, fogFactor);
}
#endif
