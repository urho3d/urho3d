#ifdef COMPILEPS

    float GetMipFromRoughness(float roughness)
    {
        return (roughness * 12.0 - pow(roughness, 6.0) * 1.5);
    }


    float3 EnvBRDFApprox (float3 specColor, float roughness, float ndv)
    {
        const float4 c0 = float4(-1, -0.0275, -0.572, 0.022 );
        const float4 c1 = float4(1, 0.0425, 1.0, -0.04 );
        float4 r = roughness * c0 + c1;
        float a004 = min( r.x * r.x, exp2( -9.28 * ndv ) ) * r.x + r.y;
        float2 AB = float2( -1.04, 1.04 ) * a004 + r.zw;
        return specColor * AB.x + AB.y;
    }

    // https://web.archive.org/web/20200228213025/http://the-witness.net/news/2012/02/seamless-cube-map-filtering/
    float3 FixCubeLookup(float3 v, float cubeMapSize)
    {
        float M = max(max(abs(v.x), abs(v.y)), abs(v.z));
        float scale = (cubeMapSize - 1.0) / cubeMapSize;

        if (abs(v.x) != M) v.x *= scale;
        if (abs(v.y) != M) v.y *= scale;
        if (abs(v.z) != M) v.z *= scale; 

        return v;
    }
    
    /// Calculate IBL contributation
    ///     reflectVec: reflection vector for cube sampling
    ///     wsNormal: surface normal in word space
    ///     toCamera: normalized direction from surface point to camera
    ///     roughness: surface roughness
    ///     ambientOcclusion: ambient occlusion
    float3 ImageBasedLighting(in float3 reflectVec, in float3 wsNormal, in float3 toCamera, in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    { 
        roughness = max(roughness, 0.08);
        reflectVec = GetSpecularDominantDir(wsNormal, reflectVec, roughness);
        const float ndv = saturate(dot(-toCamera, wsNormal));

        /// Test: Parallax correction, currently not working

        // float3 intersectMax = (cZoneMax - toCamera) / reflectVec;
        // float3 intersectMin = (cZoneMin - toCamera) / reflectVec;
        
        // float3 furthestPlane = max(intersectMax, intersectMin);
        
        // float planeDistance = min(min(furthestPlane.x, furthestPlane.y), furthestPlane.z);

        // // Get the intersection position
        // float3 intersectionPos = toCamera + reflectVec * planeDistance;
        // // Get corrected reflection
        // reflectVec = intersectionPos - ((cZoneMin + cZoneMax )/ 2);

        const float mipSelect = GetMipFromRoughness(roughness);
        const float cubeMapSize = 1024.0; // TODO This only works with textures of a given size
        float3 cube = SampleCubeLOD(ZoneCubeMap, float4(FixCubeLookup(reflectVec, cubeMapSize), mipSelect)).rgb;
        float3 cubeD = SampleCubeLOD(ZoneCubeMap, float4(FixCubeLookup(wsNormal, cubeMapSize), 9.0)).rgb;
        
        // Fake the HDR texture
        float brightness = clamp(cAmbientColor.a, 0.0, 1.0);
        float darknessCutoff = clamp((cAmbientColor.a - 1.0) * 0.1, 0.0, 0.25);

        const float hdrMaxBrightness = 5.0;
        float3 hdrCube = pow(cube + darknessCutoff, max(1.0, cAmbientColor.a));
        hdrCube += max(0.0, hdrCube - 1.0) * hdrMaxBrightness;

        float3 hdrCubeD = pow(cubeD + darknessCutoff, max(1.0, cAmbientColor.a));
        hdrCubeD += max(0.0, hdrCubeD - 1.0) * hdrMaxBrightness;

        const float3 environmentSpecular = EnvBRDFApprox(specColor, roughness, ndv);
        const float3 environmentDiffuse = EnvBRDFApprox(diffColor, 1.0, ndv);

        return (hdrCube * environmentSpecular + hdrCubeD * environmentDiffuse) * brightness;
    }
#endif
