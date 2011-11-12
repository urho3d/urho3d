float GetDiffuseDir(vec3 normal, vec3 lightDir)
{
    return max(dot(normal, lightDir), 0.0);
}

float GetDiffusePointOrSpot(vec3 normal, vec3 lightVec, out vec3 lightDir)
{
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    return max(dot(normal, lightDir), 0.0) * texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
}

float GetDiffuseDirVolumetric()
{
    return 1.0;
}

float GetDiffusePointOrSpotVolumetric(vec3 lightVec)
{
    float lightDist = length(lightVec);
    return texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
}

float GetSpecular(vec3 normal, vec3 eyeVec, vec3 lightDir, float specularPower)
{
    vec3 halfVec = normalize(normalize(eyeVec) + lightDir);
    return pow(max(dot(normal, halfVec), 0.0), specularPower);
}

vec3 GetAmbient(float zonePos)
{
    return mix(cAmbientStartColor, cAmbientEndColor, zonePos);
}

float GetShadow(vec4 shadowPos)
{
    // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
    #ifndef LQSHADOW
        // Take four samples and average them
        #ifndef POINTLIGHT
            vec2 offsets = cSampleOffsets * shadowPos.w;
        #else
            vec2 offsets = cSampleOffsets;
        #endif
        vec4 inLight = vec4(
            shadow2DProj(sShadowMap, shadowPos).r,
            shadow2DProj(sShadowMap, vec4(shadowPos.x + offsets.x, shadowPos.yzw)).r,
            shadow2DProj(sShadowMap, vec4(shadowPos.x, shadowPos.y + offsets.y, shadowPos.zw)).r,
            shadow2DProj(sShadowMap, vec4(shadowPos.xy + offsets.xy, shadowPos.zw)).r
        );
        return cShadowIntensity.z + dot(inLight, vec4(cShadowIntensity.y));
    #else
        // Take one sample
        float inLight = shadow2DProj(sShadowMap, shadowPos).r;
        return cShadowIntensity.z + cShadowIntensity.x * inLight;
    #endif
}

float GetCubeShadow(vec3 lightVec)
{
    vec3 axis = textureCube(sFaceSelectCubeMap, lightVec).rgb;
    float depth = dot(abs(lightVec), axis);

    // Expand the maximum component of the light vector to get full 0.0 - 1.0 UV range from the cube map,
    // and to avoid sampling across faces. Some GPU's filter across faces, while others do not, and in this
    // case filtering across faces is wrong
    const vec3 factor = vec3(1.0 / 256.0, 1.0 / 256.0, 1.0 / 256.0);
    lightVec += factor * axis * lightVec;

    // Read the 2D UV coordinates, adjust according to shadow map size and add face offset
    vec4 indirectPos = textureCube(sIndirectionCubeMap, lightVec);
    indirectPos.xy *= cShadowCubeAdjust.xy;
    indirectPos.xy += vec2(cShadowCubeAdjust.z + indirectPos.z * 0.5, cShadowCubeAdjust.w + indirectPos.w);

    vec4 shadowPos = vec4(indirectPos.xy, cShadowCubeProj.x + cShadowCubeProj.y / depth, 1.0);
    return GetShadow(shadowPos);
}

float GetShadowFade(float depth)
{
    return clamp((depth - cShadowFade.x) * cShadowFade.y, 0.0, 1.0);
}

vec4 GetDirShadowPos(const vec4 shadowPos[4], float depth)
{
    if (depth < cShadowSplits.x)
        return shadowPos[0];
    else if (depth < cShadowSplits.y)
        return shadowPos[1];
    else if (depth < cShadowSplits.z)
        return shadowPos[2];
    else
        return shadowPos[3];
}
