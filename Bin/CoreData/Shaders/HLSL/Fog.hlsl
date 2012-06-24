float3 GetFog(float3 color, float depth)
{
    return lerp(cFogColor, color, saturate((cFogParams.x - depth) * cFogParams.y));
}

float3 GetLitFog(float3 color, float depth)
{
    return color * saturate((cFogParams.x - depth) * cFogParams.y);
}

float GetFogFactor(float depth)
{
    return saturate((cFogParams.x - depth) * cFogParams.y);
}
