float3 GetFog(float3 color, float depth)
{
    return lerp(color, cFogColor, saturate((depth - cFogParams.x) * cFogParams.z));
}

float3 GetLitFog(float3 color, float depth)
{
    return color * saturate((cFogParams.y - depth) * cFogParams.z);
}
