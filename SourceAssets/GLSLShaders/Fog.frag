vec3 GetFog(vec3 color, float depth)
{
    return mix(color, cFogColor, clamp((depth - cFogParams.x) * cFogParams.z, 0.0, 1.0));
}

vec3 GetLitFog(vec3 color, float depth)
{
    return color * clamp((cFogParams.y - depth) * cFogParams.z, 0.0, 1.0);
}
