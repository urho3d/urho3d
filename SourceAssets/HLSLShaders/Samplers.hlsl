// Material map samplers
sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sEmissiveMap : register(S3);
sampler2D sDetailMap : register(S4);
sampler2D sEnvMap : register(S5);
samplerCUBE sEnvCubeMap : register(S5);

// Shadow and light shape samplers
sampler2D sShadowMap : register(S6);
sampler1D sLightRampMap : register(S7);
sampler2D sLightSpotMap : register(S8);
samplerCUBE sLightCubeMap : register(S8);
samplerCUBE sFaceSelectCubeMap : register(S9);
samplerCUBE sIndirectionCubeMap : register(S10);

// Deferred buffer samplers
sampler2D sNormalBuffer : register(S0);
sampler2D sDepthBuffer : register(S1);
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

float3 DecodeNormal(float4 normalInput)
{
    float3 normal;
    normal.xy = normalInput.ag * 2.0 - 1.0;
    normal.z = sqrt(max(1.0 - dot(normal.xy, normal.xy), 0.0));
    return normal;
}

float4 PackNormalDepth(float3 normal, float depth)
{
    float4 ret;
    ret.xy = normal.xz * 0.5 + 0.5;
    ret.z = (floor(depth * 127.0) + (normal.y < 0.0) * 128.0) * (1.0 / 255.0);
    ret.w = frac(depth * 127.0);
    return ret;
}

void UnpackNormalDepth(float4 input, out float3 normal, out float depth)
{
    normal.xz = input.xy * 2.0 - 1.0;
    normal.y = sqrt(1.0 - dot(normal.xz, normal.xz));

    float hiDepth = input.z * 255.0;
    if (hiDepth > 127.0)
    {
        hiDepth -= 128.0;
        normal.y = -normal.y;
    }

    depth = (hiDepth + input.w) * (1.0 / 127.0);
}

float ReconstructDepth(float hwDepth)
{
    return cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x);
}
