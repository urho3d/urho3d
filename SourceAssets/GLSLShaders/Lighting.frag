float GetDiffuseDir(vec3 normal, out vec3 lightDir)
{
    lightDir = cLightDir;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL;
}

float GetDiffusePointOrSpot(vec3 normal, vec3 worldPos, out vec3 lightDir, out vec3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten;
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL * texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
}

float GetDiffuseDirVolumetric()
{
    return 1.0;
}

float GetDiffusePointOrSpotVolumetric(vec3 worldPos, out vec3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten;
    float lightDist = length(lightVec);
    return texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
}

float GetSplitFade(float depth)
{
    float nearFadeFactor = clamp((depth - cLightSplits.x) * cLightSplits.y, 0.0, 1.0);
    float farFadeFactor = 1.0 - clamp((depth - cLightSplits.z) * cLightSplits.w, 0.0, 1.0);
    return nearFadeFactor * farFadeFactor;
}

float GetSpecular(vec3 normal, vec3 worldPos, vec3 lightDir, float specularPower)
{
    vec3 eyeDir = normalize(-worldPos);
    vec3 halfDir = normalize(eyeDir + lightDir);
    return pow(max(dot(normal, halfDir), 0.0), specularPower);
}

float GetShadow(vec4 shadowPos)
{
    // Take four samples and average them
    vec4 pcfValues = vec4(cShadowIntensity.x);
    vec2 projOfs = cSampleOffsets.xy * shadowPos.w;
    vec4 inLight = vec4(
        shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.x, projOfs.x), shadowPos.zw)).r,
        shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.y, projOfs.x), shadowPos.zw)).r,
        shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.x, projOfs.y), shadowPos.zw)).r,
        shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.y, projOfs.y), shadowPos.zw)).r
    );
    return cShadowIntensity.y + dot(inLight, pcfValues);
}
