float GetDiffuseDir(vec3 normal, vec3 lightDir)
{
    return max(dot(normal, lightDir), 0.0);
}

float GetDiffuseDirVolumetric()
{
    return 1.0;
}

#if defined(POINTLIGHT) || defined(SPOTLIGHT)
float GetDiffusePointOrSpot(vec3 normal, vec3 lightVec, out vec3 lightDir)
{
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    return max(dot(normal, lightDir), 0.0) * texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
}
#endif

#if defined(POINTLIGHT) || defined(SPOTLIGHT)
float GetDiffusePointOrSpotVolumetric(vec3 lightVec)
{
    float lightDist = length(lightVec);
    return texture2D(sLightRampMap, vec2(lightDist, 0.0)).r;
}
#endif

float GetSpecular(vec3 normal, vec3 eyeVec, vec3 lightDir, float specularPower)
{
    vec3 halfVec = normalize(normalize(eyeVec) + lightDir);
    return pow(max(dot(normal, halfVec), 0.0), specularPower);
}

float GetIntensity(vec3 color)
{
    return dot(color, vec3(0.333));
}

#ifdef SHADOW

#ifdef DIRLIGHT
    #ifndef GL_ES
        #define NUMCASCADES 4
    #else
        #define NUMCASCADES 2
    #endif
#else
    #define NUMCASCADES 1
#endif

float GetShadow(vec4 shadowPos)
{
    #ifndef GL_ES
        #ifndef LQSHADOW
            // Take four samples and average them
            // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
            #ifndef POINTLIGHT
                vec2 offsets = cShadowMapInvSize * shadowPos.w;
            #else
                vec2 offsets = cShadowMapInvSize;
            #endif
            vec4 inLight = vec4(
                shadow2DProj(sShadowMap, shadowPos).r,
                shadow2DProj(sShadowMap, vec4(shadowPos.x + offsets.x, shadowPos.yzw)).r,
                shadow2DProj(sShadowMap, vec4(shadowPos.x, shadowPos.y + offsets.y, shadowPos.zw)).r,
                shadow2DProj(sShadowMap, vec4(shadowPos.xy + offsets.xy, shadowPos.zw)).r
            );
            return cShadowIntensity.y + dot(inLight, vec4(cShadowIntensity.x));
        #else
            // Take one sample
            float inLight = shadow2DProj(sShadowMap, shadowPos).r;
            return cShadowIntensity.y + cShadowIntensity.x * inLight;
        #endif
    #else
        vec3 projShadowPos = shadowPos.xyz / shadowPos.w;
        #ifndef LQSHADOW
            // Take four samples and average them
            vec4 inLight = vec4(
                texture2D(sShadowMap, projShadowPos.xy).r > projShadowPos.z,
                texture2D(sShadowMap, vec2(projShadowPos.x + cShadowMapInvSize.x, projShadowPos.y)).r > projShadowPos.z,
                texture2D(sShadowMap, vec2(projShadowPos.x, projShadowPos.y + cShadowMapInvSize.y)).r > projShadowPos.z,
                texture2D(sShadowMap, projShadowPos.xy + cShadowMapInvSize).r > projShadowPos.z
            );
            return cShadowIntensity.y + dot(inLight, vec4(cShadowIntensity.x));
        #else
            // Take one sample
            return cShadowIntensity.y + (texture2D(sShadowMap, projShadowPos.xy).r > projShadowPos.z) ? cShadowIntensity.x : 0.0;
        #endif
    #endif
}

#ifdef POINTLIGHT
float GetPointShadow(vec3 lightVec)
{
    vec3 axis = textureCube(sFaceSelectCubeMap, lightVec).rgb;
    float depth = abs(dot(lightVec, axis));

    // Expand the maximum component of the light vector to get full 0.0 - 1.0 UV range from the cube map,
    // and to avoid sampling across faces. Some GPU's filter across faces, while others do not, and in this
    // case filtering across faces is wrong
    const vec3 factor = vec3(1.0 / 256.0);
    lightVec += factor * axis * lightVec;

    // Read the 2D UV coordinates, adjust according to shadow map size and add face offset
    vec4 indirectPos = textureCube(sIndirectionCubeMap, lightVec);
    indirectPos.xy *= cShadowCubeAdjust.xy;
    indirectPos.xy += vec2(cShadowCubeAdjust.z + indirectPos.z * 0.5, cShadowCubeAdjust.w + indirectPos.w);

    vec4 shadowPos = vec4(indirectPos.xy, cShadowDepthFade.x + cShadowDepthFade.y / depth, 1.0);
    return GetShadow(shadowPos);
}
#endif

#ifdef DIRLIGHT
float GetDirShadowFade(float inLight, float depth)
{
    return min(inLight + max((depth - cShadowDepthFade.z) * cShadowDepthFade.w, 0.0), 1.0);
}

#ifndef GL_ES
float GetDirShadow(const vec4 iShadowPos[NUMCASCADES], float depth)
{
    vec4 shadowPos;

    if (depth < cShadowSplits.x)
        shadowPos = iShadowPos[0];
    else if (depth < cShadowSplits.y)
        shadowPos = iShadowPos[1];
    else if (depth < cShadowSplits.z)
        shadowPos = iShadowPos[2];
    else
        shadowPos = iShadowPos[3];
        
    return GetDirShadowFade(GetShadow(shadowPos), depth);
}

float GetDirShadowDeferred(vec4 projWorldPos, float depth)
{
    vec4 shadowPos;

    if (depth < cShadowSplits.x)
        shadowPos = cLightMatricesPS[0] * projWorldPos;
    else if (depth < cShadowSplits.y)
        shadowPos = cLightMatricesPS[1] * projWorldPos;
    else if (depth < cShadowSplits.z)
        shadowPos = cLightMatricesPS[2] * projWorldPos;
    else
        shadowPos = cLightMatricesPS[3] * projWorldPos;

    return GetDirShadowFade(GetShadow(shadowPos), depth);
}
#else
float GetDirShadow(const vec4 iShadowPos[NUMCASCADES], float depth)
{
    vec4 shadowPos;

    if (depth < cShadowSplits.x)
        shadowPos = iShadowPos[0];
    else
        shadowPos = iShadowPos[1];

    return GetDirShadowFade(GetShadow(shadowPos), depth);
}
#endif
#endif

float GetShadow(vec4 iShadowPos[NUMCASCADES], float depth)
{
    #if defined(DIRLIGHT)
        return GetDirShadow(iShadowPos, depth);
    #elif defined(SPOTLIGHT)
        return GetShadow(iShadowPos[0]);
    #else
        return GetPointShadow(iShadowPos[0].xyz);
    #endif
}

#ifndef GL_ES
float GetShadowDeferred(vec4 projWorldPos, float depth)
{
    #if defined(DIRLIGHT)
        return GetDirShadowDeferred(projWorldPos, depth);
    #elif defined(SPOTLIGHT)
        vec4 shadowPos = cLightMatricesPS[1] * projWorldPos;
        return GetShadow(shadowPos);
    #else
        vec3 shadowPos = projWorldPos.xyz - cLightPosPS.xyz;
        return GetPointShadow(shadowPos);
    #endif
}
#endif
#endif