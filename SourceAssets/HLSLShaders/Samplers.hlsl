sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sEmissiveMap : register(S3);
sampler2D sDetailMap : register(S4);
sampler2D sEnvMap : register(S5);
samplerCUBE sEnvCubeMap : register(S5);
sampler2D sShadowMap : register(S6);
sampler1D sLightRampMap : register(S7);
sampler2D sLightSpotMap : register(S8);
samplerCUBE sLightCubeMap : register(S8);
samplerCUBE sFaceSelectCubeMap : register(S9);
samplerCUBE sIndirectionCubeMap : register(S10);
sampler2D sDepthBuffer : register(S0);
sampler2D sNormalBuffer : register(S1);
sampler2D sLightBuffer : register(S7);

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
    float3 normal;
    normal.xy = normalInput.ag * 2.0 - 1.0;
    normal.z = sqrt(max(1.0 - dot(normal.xy, normal.xy), 0.0));
    return normal;
}

float ReconstructDepth(float hwDepth)
{
    return cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x);
}
