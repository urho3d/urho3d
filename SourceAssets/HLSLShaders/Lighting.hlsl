#pragma warning(disable:3571)

float GetDiffuseDir(float3 normal, float3 lightDir)
{
    return saturate(dot(normal, lightDir));
}

float GetDiffusePointOrSpot(float3 normal, float3 lightVec, out float3 lightDir)
{
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    return saturate(dot(normal, lightDir)) * tex1D(sLightRampMap, lightDist).r;
}

float GetDiffuseDirVolumetric()
{
    return 1.0;
}

float GetDiffusePointOrSpotVolumetric(float3 lightVec)
{
    float lightDist = length(lightVec);
    return tex1D(sLightRampMap, lightDist).r;
}

float GetSpecular(float3 normal, float3 eyeVec, float3 lightDir, float specularPower)
{
    float3 halfVec = normalize(normalize(eyeVec) + lightDir);
    return pow(dot(normal, halfVec), specularPower);
}

float3 GetAmbient(float zonePos)
{
    return cAmbientStartColor + zonePos * cAmbientEndColor;
}

float GetIntensity(float3 color)
{
    return dot(color, float3(0.333, 0.333, 0.333));
}

#ifdef NUMVERTEXLIGHTS
float GetVertexLight(int index, float3 worldPos, float3 normal)
{
    float3 lightDir = cVertexLights[index * 3 + 1].xyz;
    float3 lightPos = cVertexLights[index * 3 + 2].xyz;
    float invRange = cVertexLights[index * 3].w;
    float cutoff = cVertexLights[index * 3 + 1].w;
    float invCutoff = cVertexLights[index * 3 + 2].w;

    #ifndef BILLBOARD
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
    #else
        // Directional light
        if (invRange == 0.0)
            return 1.0;
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
    #endif
}
#endif

#ifdef SHADOW
float GetShadow(float4 shadowPos)
{
    // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
    #ifndef FALLBACK
        #ifndef LQSHADOW
            // Take four samples and average them
            #ifndef POINTLIGHT
                float2 offsets = cSampleOffsets * shadowPos.w;
            #else
                float2 offsets = cSampleOffsets;
            #endif
            float4 inLight = float4(
                tex2Dproj(sShadowMap, shadowPos).r,
                tex2Dproj(sShadowMap, float4(shadowPos.x + offsets.x, shadowPos.yzw)).r,
                tex2Dproj(sShadowMap, float4(shadowPos.x, shadowPos.y + offsets.y, shadowPos.zw)).r,
                tex2Dproj(sShadowMap, float4(shadowPos.xy + offsets.xy, shadowPos.zw)).r
            );
            #ifdef HWSHADOW
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
            #ifdef HWSHADOW
                return cShadowIntensity.y + cShadowIntensity.x * inLight;
            #else
                #ifndef POINTLIGHT
                    return cShadowIntensity.y + cShadowIntensity.x * (inLight * shadowPos.w > shadowPos.z);
                #else
                    return cShadowIntensity.y + cShadowIntensity.x * (inLight > shadowPos.z);
                #endif
            #endif
        #endif
    #else
        // Fallback mode: take two samples, depth needs to be decoded from RG channels
        #ifndef POINTLIGHT
            float2 offsets = cSampleOffsets * shadowPos.w;
        #else
            float2 offsets = cSampleOffsets;
        #endif
        float2 inLight = float2(
            DecodeDepth(tex2Dproj(sShadowMap, shadowPos).rg),
            DecodeDepth(tex2Dproj(sShadowMap, float4(shadowPos.x + offsets.x, shadowPos.yzw)).rg)
        );
        #ifndef POINTLIGHT
            return cShadowIntensity.y + dot(inLight * shadowPos.w > shadowPos.z, cShadowIntensity.x);
        #else
            return cShadowIntensity.y + dot(inLight > shadowPos.z, cShadowIntensity.x);
        #endif
    #endif
}

float GetCubeShadow(float3 lightVec)
{
    float3 axis = texCUBE(sFaceSelectCubeMap, lightVec).rgb;
    float depth = dot(abs(lightVec), axis);

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

float GetShadowFade(float depth)
{
    return saturate((depth - cShadowDepthFade.z) * cShadowDepthFade.w);
}

float4 GetDirShadowPos(const float4 iShadowPos[4], float depth)
{
    if (depth < cShadowSplits.x)
        return iShadowPos[0];
    else if (depth < cShadowSplits.y)
        return iShadowPos[1];
    else if (depth < cShadowSplits.z)
        return iShadowPos[2];
    else
        return iShadowPos[3];
}

#ifdef SM3
float4x4 GetDirShadowMatrix(float depth, const float4x4 matrices[4])
{
    if (depth < cShadowSplits.x)
        return matrices[0];
    else if (depth < cShadowSplits.y)
        return matrices[1];
    else if (depth < cShadowSplits.z)
        return matrices[2];
    else
        return matrices[3];
}
#else
float4x4 GetDirShadowMatrix(float depth, const float4x4 matrices[3])
{
    if (depth < cShadowSplits.x)
        return matrices[0];
    else if (depth < cShadowSplits.y)
        return matrices[1];
    else
        return matrices[2];
}
#endif
#endif