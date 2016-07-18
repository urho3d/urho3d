#ifdef COMPILEPS

    /// Determine reflection vector based on surface roughness, rougher uses closer to the normal and smoother uses closer to the reflection vector
    ///     normal: surface normal
    ///     reflection: vector of reflection off of the surface
    ///     roughness: surface roughness
    float3 GetSpecularDominantDir(float3 normal, float3 reflection, float roughness)
    {
        const float smoothness = 1.0 - roughness;
        const float lerpFactor = smoothness * (sqrt(smoothness) + roughness);
        return lerp(normal, reflection, lerpFactor);
    }

    float GetMipFromRougness(float roughness)
    {
        const float smoothness = 1.0 - roughness;
        return (1.0 - smoothness * smoothness) * 10.0;
    }


    float3 EnvBRDFApprox (float3 SpecularColor, float Roughness, float NoV)
    {
        const float4 c0 = float4(-1, -0.0275, -0.572, 0.022 );
        const float4 c1 = float4(1, 0.0425, 1.0, -0.04 );
        float4 r = Roughness * c0 + c1;
        float a004 = min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
        float2 AB = float2( -1.04, 1.04 ) * a004 + r.zw;
        return SpecularColor * AB.x + AB.y;
    }

    /// Calculate IBL contributation
    ///     reflectVec: reflection vector for cube sampling
    ///     wsNormal: surface normal in word space
    ///     toCamera: normalized direction from surface point to camera
    ///     roughness: surface roughness
    ///     ambientOcclusion: ambient occlusion
    float3 ImageBasedLighting(in float3 reflectVec, in float3 tangent, in float3 bitangent, in float3 wsNormal, in float3 toCamera, in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    {
        reflectVec = GetSpecularDominantDir(wsNormal, reflectVec, roughness);
        const float ndv = saturate(dot(-toCamera, wsNormal));
        
        const float mipSelect = roughness  * 9;

        float3 cube = SampleCubeLOD(ZoneCubeMap, float4(reflectVec, mipSelect)).rgb;
        const float3 environmentSpecular = EnvBRDFApprox(specColor, roughness, ndv);

        return cube * environmentSpecular;
    }
#endif
