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
                return cShadowIntensity.z + dot(inLight, cShadowIntensity.y);
            #else
                #ifndef POINTLIGHT
                    return cShadowIntensity.z + dot(inLight * shadowPos.w > shadowPos.z, cShadowIntensity.y);
                #else
                    return cShadowIntensity.z + dot(inLight > shadowPos.z, cShadowIntensity.y);
                #endif
            #endif
        #else
            // Take one sample
            float inLight = tex2Dproj(sShadowMap, shadowPos).r;
            #ifdef HWSHADOW
                return cShadowIntensity.z + cShadowIntensity.x * inLight;
            #else
                #ifndef POINTLIGHT
                    return cShadowIntensity.z + cShadowIntensity.x * (inLight * shadowPos.w > shadowPos.z);
                #else
                    return cShadowIntensity.z + cShadowIntensity.x * (inLight > shadowPos.z);
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
            return cShadowIntensity.z + dot(inLight * shadowPos.w > shadowPos.z, cShadowIntensity.y);
        #else
            return cShadowIntensity.z + dot(inLight > shadowPos.z, cShadowIntensity.y);
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

    float4 shadowPos = float4(indirectPos.xy, cShadowCubeProj.x + cShadowCubeProj.y / depth, 1.0);
    return GetShadow(shadowPos);
}

float GetShadowFade(float depth)
{
    return saturate((depth - cShadowFade.x) * cShadowFade.y);
}
