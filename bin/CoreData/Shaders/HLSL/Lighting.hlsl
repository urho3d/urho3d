#pragma warning(disable:3571)

#ifdef COMPILEVS
float3 GetAmbient(float zonePos)
{
    return cAmbientStartColor + zonePos * cAmbientEndColor;
}

#ifdef NUMVERTEXLIGHTS
float GetVertexLight(int index, float3 worldPos, float3 normal)
{
    float3 lightDir = cVertexLights[index * 3 + 1].xyz;
    float3 lightPos = cVertexLights[index * 3 + 2].xyz;
    float invRange = cVertexLights[index * 3].w;
    float cutoff = cVertexLights[index * 3 + 1].w;
    float invCutoff = cVertexLights[index * 3 + 2].w;

    // Directional light
    if (invRange == 0.0)
    {
        float NdotL = max(dot(normal, lightDir), 0.0);
        return NdotL;
    }
    // Point/spot light
    else
    {
        float3 lightVec = (lightPos - worldPos) * invRange;
        float lightDist = length(lightVec);
        float3 localDir = lightVec / lightDist;
        float NdotL = max(dot(normal, localDir), 0.0);
        float atten = saturate(1.0 - lightDist * lightDist);
        float spotEffect = dot(localDir, lightDir);
        float spotAtten = saturate((spotEffect - cutoff) * invCutoff);
        return NdotL * atten * spotAtten;
    }
}

float GetVertexLightVolumetric(int index, float3 worldPos)
{
    float3 lightDir = cVertexLights[index * 3 + 1].xyz;
    float3 lightPos = cVertexLights[index * 3 + 2].xyz;
    float invRange = cVertexLights[index * 3].w;
    float cutoff = cVertexLights[index * 3 + 1].w;
    float invCutoff = cVertexLights[index * 3 + 2].w;

    // Directional light
    if (invRange == 0.0)
    {
        return 1.0;
    }
    // Point/spot light
    else
    {
        float3 lightVec = (lightPos - worldPos) * invRange;
        float lightDist = length(lightVec);
        float3 localDir = lightVec / lightDist;
        float atten = saturate(1.0 - lightDist * lightDist);
        float spotEffect = dot(localDir, lightDir);
        float spotAtten = saturate((spotEffect - cutoff) * invCutoff);
        return atten * spotAtten;
    }
}
#endif

#ifdef SHADOW

#ifdef DIRLIGHT
    #ifdef SM3
        #define NUMCASCADES 4
    #else
        #define NUMCASCADES 3
    #endif
#else
    #define NUMCASCADES 1
#endif

void GetShadowPos(float4 projWorldPos, out float4 shadowPos[NUMCASCADES])
{
    // Shadow projection: transform from world space to shadow space
    #if defined(DIRLIGHT)
        shadowPos[0] = mul(projWorldPos, cLightMatrices[0]);
        shadowPos[1] = mul(projWorldPos, cLightMatrices[1]);
        shadowPos[2] = mul(projWorldPos, cLightMatrices[2]);
        #ifdef SM3
            shadowPos[3] = mul(projWorldPos, cLightMatrices[3]);
        #endif
    #elif defined(SPOTLIGHT)
        shadowPos[0] = mul(projWorldPos, cLightMatrices[1]);
    #else
        shadowPos[0] = float4(projWorldPos.xyz - cLightPos.xyz, 0.0);
    #endif
}
#endif
#endif

#ifdef COMPILEPS
float GetDiffuse(float3 normal, float3 worldPos, out float3 lightDir)
{
    #ifdef DIRLIGHT
        lightDir = cLightDirPS;
        return saturate(dot(normal, lightDir));
    #else
        float3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
        float lightDist = length(lightVec);
        lightDir = lightVec / lightDist;
        return saturate(dot(normal, lightDir)) * tex1D(sLightRampMap, lightDist).r;
    #endif
}

float GetDiffuseVolumetric(float3 worldPos)
{
    #ifdef DIRLIGHT
        return 1.0;
    #else
        float3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
        float lightDist = length(lightVec);
        return tex1D(sLightRampMap, lightDist).r;
    #endif
}

float GetSpecular(float3 normal, float3 eyeVec, float3 lightDir, float specularPower)
{
    float3 halfVec = normalize(normalize(eyeVec) + lightDir);
    return pow(dot(normal, halfVec), specularPower);
}

float GetIntensity(float3 color)
{
    return dot(color, float3(0.333, 0.333, 0.333));
}

#ifdef SHADOW

#ifdef DIRLIGHT
    #ifdef SM3
        #define NUMCASCADES 4
    #else
        #define NUMCASCADES 3
    #endif
#else
    #define NUMCASCADES 1
#endif

float GetShadow(float4 shadowPos)
{
    #ifndef LQSHADOW
        // Take four samples and average them
        // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
        #ifndef POINTLIGHT
            float2 offsets = cShadowMapInvSize * shadowPos.w;
        #else
            float2 offsets = cShadowMapInvSize;
        #endif
        float4 inLight = float4(
            tex2Dproj(sShadowMap, shadowPos).r,
            tex2Dproj(sShadowMap, float4(shadowPos.x + offsets.x, shadowPos.yzw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.x, shadowPos.y + offsets.y, shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + offsets.xy, shadowPos.zw)).r
        );
        #ifndef SHADOWCMP
            return cShadowIntensity.y + dot(inLight, cShadowIntensity.x);
        #else
            #ifndef POINTLIGHT
                return cShadowIntensity.y + dot(inLight * shadowPos.w > shadowPos.z, cShadowIntensity.x);
            #else
                return cShadowIntensity.y + dot(inLight > shadowPos.z, cShadowIntensity.x);
            #endif
        #endif
    #else
        // Take one sample
        float inLight = tex2Dproj(sShadowMap, shadowPos).r;
        #ifndef SHADOWCMP
            return cShadowIntensity.y + cShadowIntensity.x * inLight;
        #else
            #ifndef POINTLIGHT
                return cShadowIntensity.y + cShadowIntensity.x * (inLight * shadowPos.w > shadowPos.z);
            #else
                return cShadowIntensity.y + cShadowIntensity.x * (inLight > shadowPos.z);
            #endif
        #endif
    #endif
}

#ifdef POINTLIGHT
float GetPointShadow(float3 lightVec)
{
    float3 axis = texCUBE(sFaceSelectCubeMap, lightVec).rgb;
    float depth = abs(dot(lightVec, axis));

    // Expand the maximum component of the light vector to get full 0.0 - 1.0 UV range from the cube map,
    // and to avoid sampling across faces. Some GPU's filter across faces, while others do not, and in this
    // case filtering across faces is wrong
    const float factor = 1.0 / 256.0;
    lightVec += factor * axis * lightVec;

    // Read the 2D UV coordinates, adjust according to shadow map size and add face offset
    float4 indirectPos = texCUBE(sIndirectionCubeMap, lightVec);
    indirectPos.xy *= cShadowCubeAdjust.xy;
    indirectPos.xy += float2(cShadowCubeAdjust.z + indirectPos.z * 0.5, cShadowCubeAdjust.w + indirectPos.w);

    float4 shadowPos = float4(indirectPos.xy, cShadowDepthFade.x + cShadowDepthFade.y / depth, 1.0);
    return GetShadow(shadowPos);
}
#endif

#ifdef DIRLIGHT
float GetDirShadowFade(float inLight, float depth)
{
    return saturate(inLight + saturate((depth - cShadowDepthFade.z) * cShadowDepthFade.w));
}

float GetDirShadow(const float4 iShadowPos[NUMCASCADES], float depth)
{
    float4 shadowPos;

    #ifdef SM3
        if (depth < cShadowSplits.x)
            shadowPos = iShadowPos[0];
        else if (depth < cShadowSplits.y)
            shadowPos = iShadowPos[1];
        else if (depth < cShadowSplits.z)
            shadowPos = iShadowPos[2];
        else
            shadowPos = iShadowPos[3];
    #else
        if (depth < cShadowSplits.x)
            shadowPos = iShadowPos[0];
        else if (depth < cShadowSplits.y)
            shadowPos = iShadowPos[1];
        else
            shadowPos = iShadowPos[2];
    #endif

    return GetDirShadowFade(GetShadow(shadowPos), depth);
}

float GetDirShadowDeferred(float4 projWorldPos, float depth)
{
    float4 shadowPos;

    #ifdef SM3
        if (depth < cShadowSplits.x)
            shadowPos = mul(projWorldPos, cLightMatricesPS[0]);
        else if (depth < cShadowSplits.y)
            shadowPos = mul(projWorldPos, cLightMatricesPS[1]);
        else if (depth < cShadowSplits.z)
            shadowPos = mul(projWorldPos, cLightMatricesPS[2]);
        else
            shadowPos = mul(projWorldPos, cLightMatricesPS[3]);
    #else
        if (depth < cShadowSplits.x)
            shadowPos = mul(projWorldPos, cLightMatricesPS[0]);
        else if (depth < cShadowSplits.y)
            shadowPos = mul(projWorldPos, cLightMatricesPS[1]);
        else if (depth < cShadowSplits.z)
            shadowPos = mul(projWorldPos, cLightMatricesPS[2]);
    #endif

    return GetDirShadowFade(GetShadow(shadowPos), depth);
}
#endif

float GetShadow(float4 iShadowPos[NUMCASCADES], float depth)
{
    #if defined(DIRLIGHT)
        return GetDirShadow(iShadowPos, depth);
    #elif defined(SPOTLIGHT)
        return GetShadow(iShadowPos[0]);
    #else
        return GetPointShadow(iShadowPos[0].xyz);
    #endif
}

float GetShadowDeferred(float4 projWorldPos, float depth)
{
    #if defined(DIRLIGHT)
        return GetDirShadowDeferred(projWorldPos, depth);
    #elif defined(SPOTLIGHT)
        float4 shadowPos = mul(projWorldPos, cLightMatricesPS[1]);
        return GetShadow(shadowPos);
    #else
        float3 shadowPos = projWorldPos.xyz - cLightPosPS.xyz;
        return GetPointShadow(shadowPos);
    #endif
}
#endif
#endif