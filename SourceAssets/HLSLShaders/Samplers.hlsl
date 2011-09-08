// Material map samplers
sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sDetailMap : register(S3);
sampler2D sEnvMap : register(S4);
samplerCUBE sEnvCubeMap : register(S4);
sampler2D sEmissiveMap : register(S5);

// Shadow and light shape samplers
sampler2D sShadowMap : register(S5);
sampler1D sLightRampMap : register(S6);
sampler2D sLightSpotMap : register(S7);
samplerCUBE sLightCubeMap : register(S7);

// Rendertarget samplers
sampler2D sDiffBuffer : register(S0);
sampler2D sNormalBuffer : register(S1);
sampler2D sDepthBuffer : register(S2);
sampler2D sLightBuffer : register(S6);

float4 Sample(sampler2D map, float2 texCoord)
{
    // Use tex2Dlod if available to avoid divergence and allow branching
    #ifdef SM3
        return tex2Dlod(map, float4(texCoord, 0.0, 0.0));
    #else
        return tex2D(map, texCoord);
    #endif
}

float3 UnpackNormal(float4 normalInput)
{
    float3 normal;
    normal.xy = normalInput.ag * 2.0 - 1.0;
    normal.z = sqrt(1.0 - dot(normal.xy, normal.xy));
    return normal;
}

float ReconstructDepth(float hwDepth)
{
    return cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x);
}

float2 EncodeDepth(float depth)
{
    depth *= 255.0;
    return float2(floor(depth) / 255.0, frac(depth));
}

float DecodeDepth(float2 depth)
{
    const float2 dotValues = float2(1.0, 1.0 / 255.0);
    return dot(depth, dotValues);
}
