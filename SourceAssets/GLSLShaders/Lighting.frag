float GetDiffuseDir(vec3 normal, vec3 lightDir, out float NdotL)
{
    NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL;
}

float GetDiffusePointOrSpot(vec3 normal, vec3 lightVec, out vec3 lightDir, out float NdotL)
{
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL * texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
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

float GetSpecular(vec3 normal, vec3 eyeVec, vec3 lightDir, float NdotL, float specularPower)
{
    vec3 reflectDir = 2.0 * NdotL * normal - lightDir;
    return pow(max(dot(reflectDir, normalize(eyeVec)), 0.0), specularPower);
}

float GetShadow(vec4 shadowPos)
{
    // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
    #ifndef LQSHADOW
        // Take four samples and average them
        vec4 pcfValues = vec4(cShadowIntensity.y);
        #ifndef POINTLIGHT
            vec4 projOfs = cSampleOffsets * shadowPos.w;
        #else
            vec4 projOfs = cSampleOffsets;
        #endif
        vec4 inLight = vec4(
            shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.x, projOfs.z), shadowPos.zw)).r,
            shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.y, projOfs.z), shadowPos.zw)).r,
            shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.x, projOfs.w), shadowPos.zw)).r,
            shadow2DProj(sShadowMap, vec4(shadowPos.xy + vec2(projOfs.y, projOfs.w), shadowPos.zw)).r
        );
        return cShadowIntensity.z + dot(inLight, pcfValues);
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
