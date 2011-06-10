vec3 GetFog(vec3 color, float depth)
{
    return mix(color, cFogColor, clamp((depth - cFogParams.x) * cFogParams.z, 0.0, 1.0));
}

vec3 GetLitFog(vec3 color, float depth)
{
    return color * clamp((cFogParams.y - depth) * cFogParams.z, 0.0, 1.0);
}

float GetFogFactor(float depth)
{
    return clamp((depth - cFogParams.x) * cFogParams.z, 0.0, 1.0);
}

float GetReverseFogFactor(float depth)
{
    return clamp((cFogParams.y - depth) * cFogParams.z, 0.0, 1.0);
}
