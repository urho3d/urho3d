vec3 GetFog(vec3 color, float depth)
{
    return mix(cFogColor, color, clamp((cFogParams.x - depth) * cFogParams.y, 0.0, 1.0));
}

vec3 GetLitFog(vec3 color, float depth)
{
    return color * clamp((cFogParams.x - depth) * cFogParams.y, 0.0, 1.0);
}

float GetFogFactor(float depth)
{
    return clamp((cFogParams.x - depth) * cFogParams.y, 0.0, 1.0);
}
