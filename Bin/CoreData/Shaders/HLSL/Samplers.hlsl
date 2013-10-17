sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sAlbedoBuffer : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sNormalBuffer : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sEmissiveMap : register(S3);
sampler2D sEnvMap : register(S4);
samplerCUBE sEnvCubeMap : register(S4);
sampler1D sLightRampMap : register(S5);
sampler2D sLightSpotMap : register(S6);
samplerCUBE sLightCubeMap : register(S6);
sampler2D sShadowMap : register(S7);
samplerCUBE sFaceSelectCubeMap : register(S8);
samplerCUBE sIndirectionCubeMap : register(S9);
sampler2D sDepthBuffer : register(S10);
sampler2D sLightBuffer : register(S11);
sampler3D sVolumeMap : register(S12);

float4 Sample(sampler2D map, float2 texCoord)
{
    // Use tex2Dlod if available to avoid divergence and allow branching
    #ifdef SM3
        return tex2Dlod(map, float4(texCoord, 0.0, 0.0));
    #else
        return tex2D(map, texCoord);
    #endif
}

float3 DecodeNormal(float4 normalInput)
{
    #ifdef PACKEDNORMAL
        float3 normal;
        normal.xy = normalInput.ag * 2.0 - 1.0;
        normal.z = sqrt(max(1.0 - dot(normal.xy, normal.xy), 0.0));
        return normal;
    #else
        return normalize(normalInput.rgb * 2.0 - 1.0);
    #endif
}
