float3 GetFog(float3 color, float depth)
{
    return lerp(color, cFogColor, saturate((depth - cFogParams.x) * cFogParams.z));
}

float3 GetLitFog(float3 color, float depth)
{
    return color * saturate((cFogParams.y - depth) * cFogParams.z);
}

float GetFogFactor(float depth)
{
    return saturate((depth - cFogParams.x) * cFogParams.z);
}

float GetReverseFogFactor(float depth)
{
    return saturate((cFogParams.y - depth) * cFogParams.z);
}
