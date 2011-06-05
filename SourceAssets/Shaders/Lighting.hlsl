float GetDiffuseDir(float3 normal, out float3 lightDir)
{
    lightDir = cLightDir;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL;
}

float GetDiffusePointOrSpot(float3 normal, float3 worldPos, out float3 lightDir, out float3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten.x;
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL * tex1D(sLightRampMap, lightDist).r;
}

float GetDiffuseDirVolumetric()
{
    return 1.0;
}

float GetDiffusePointOrSpotVolumetric(float3 worldPos, out float3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten.x;
    float lightDist = length(lightVec);
    return tex1D(sLightRampMap, lightDist).r;
}

float GetSplitFade(float depth)
{
    float nearFadeFactor = saturate((depth - cLightSplits.x) * cLightSplits.y);
    float farFadeFactor = 1.0 - saturate((depth - cLightSplits.z) * cLightSplits.w);
    return nearFadeFactor * farFadeFactor;
}

float GetSpecular(float3 normal, float3 worldPos, float3 lightDir, float specularPower)
{
    float3 eyeDir = normalize(-worldPos);
    float3 halfDir = normalize(eyeDir + lightDir);
    return pow(dot(normal, halfDir), specularPower);
}

float GetShadow(float4 shadowPos)
{
    // Take four samples and average them
    float4 pcfValues = cShadowIntensity.x;
    #ifdef SM3
        float2 ofs = cSampleOffsets.xy;
        float4 projShadowPos = float4(shadowPos.xyz / shadowPos.w, 0.0);
        float4 inLight = float4(
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.x, ofs.x), projShadowPos.zw)).r,
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.y, ofs.x), projShadowPos.zw)).r,
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.x, ofs.y), projShadowPos.zw)).r,
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.y, ofs.y), projShadowPos.zw)).r
        );
        #ifdef HWSHADOW
            return cShadowIntensity.y + dot(inLight, pcfValues);
        #else
            return cShadowIntensity.y + dot(inLight > projShadowPos.z, pcfValues);
        #endif
    #else
        float2 projOfs = cSampleOffsets.xy * shadowPos.w;
        float4 inLight = float4(
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.x, projOfs.x), shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.y, projOfs.x), shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.x, projOfs.y), shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.y, projOfs.y), shadowPos.zw)).r
        );
        #ifdef HWSHADOW
            return cShadowIntensity.y + dot(inLight, pcfValues);
        #else
            return cShadowIntensity.y + dot((inLight * shadowPos.w) > shadowPos.z, pcfValues);
        #endif
    #endif
}
