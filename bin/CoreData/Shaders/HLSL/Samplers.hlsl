#ifdef COMPILEPS
sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sAlbedoBuffer : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sNormalBuffer : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sEmissiveMap : register(S3);
sampler2D sEnvMap : register(S4);
sampler3D sVolumeMap : register(S5);
samplerCUBE sEnvCubeMap : register(S4);
sampler1D sLightRampMap : register(S8);
sampler2D sLightSpotMap : register(S9);
samplerCUBE sLightCubeMap : register(S9);
sampler2D sShadowMap : register(S10);
samplerCUBE sFaceSelectCubeMap : register(S11);
samplerCUBE sIndirectionCubeMap : register(S12);
sampler2D sDepthBuffer : register(S13);
sampler2D sLightBuffer : register(S14);
samplerCUBE sZoneCubeMap : register(S15);
sampler3D sZoneVolumeMap : register(S15);

float4 Sample(sampler2D map, float2 texCoord)
{
    return tex2Dlod(map, float4(texCoord, 0.0, 0.0));
}

float3 DecodeNormal(float4 normalInput)
{
    #ifdef PACKEDNORMAL
        float3 normal;
        normal.xy = normalInput.ag * 2.0 - 1.0;
        normal.z = sqrt(max(1.0 - dot(normal.xy, normal.xy), 0.0));
        return normal;
    #else
        return normalInput.rgb * 2.0 - 1.0;
    #endif
}

float ReconstructDepth(float hwDepth)
{
    return dot(float2(hwDepth, cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x)), cDepthReconstruct.zw);
}
#endif
