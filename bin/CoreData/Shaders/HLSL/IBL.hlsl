#ifdef COMPILEPS
    //#define IBLFAST

    float3 ImportanceSampleSimple(in float2 Xi, in float roughness, in float3 T, in float3 B, in float3 N)
    {
        const float a = roughness * roughness;
        const float3x3 tbn = float3x3(T, B, N);
        #ifdef IBLFAST
            const float blurFactor = 0.0;
        #else
            const float blurFactor = 5.0;
        #endif
        const float3 Xi3 = lerp(float3(0,0,1), normalize(float3(Xi.xy * blurFactor % 1.0 , 1.0)), a);
        const float3 XiWS = mul(Xi3, tbn);
        return normalize(N + XiWS);
    }

    // Karis '13
    float3 ImportanceSampleGGX(in float2 Xi, in float roughness, in float3 T, in float3 B, in float3 N)
    {
        float a = roughness * roughness;
        float Phi = 2.0 * M_PI * Xi.x;
        float CosTheta = (sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y)));
        float SinTheta = sqrt(1.0 - CosTheta * CosTheta);
        float3 H = 0;
        H.x = SinTheta * cos(Phi);
        H.y = SinTheta * sin(Phi);
        H.z = CosTheta;

        float3 UpVector = abs(N.z) < 0.999 ? float3(0, 0, 1) : float3(1, 0, 0);
        float3 TangentX = normalize(cross(UpVector, N));
        float3 TangentY = cross(N, TangentX);
        // Tangent to world space
        return TangentX * H.x + TangentY * H.y + N * H.z;
    }

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

    #ifdef IBLFAST
        #define IMPORTANCE_SAMPLES 1
    #else
        #define IMPORTANCE_SAMPLES 16
    #endif

    #define IMPORTANCE_KERNEL_SIZE 16
    static const float2 IMPORTANCE_KERNEL[IMPORTANCE_KERNEL_SIZE] =
    {
        float2(-0.0780436, 0.0558389),
        float2(0.034318, -0.0635879),
        float2(0.00230821, 0.0807279),
        float2(0.0124638, 0.117585),
        float2(0.093943, -0.0944602),
        float2(0.139348, -0.109816),
        float2(-0.181872, -0.129649),
        float2(0.240066, -0.0494057),
        float2(0.115965, -0.0374714),
        float2(-0.294819, -0.100726),
        float2(-0.149652, 0.37459),
        float2(0.261695, -0.292813),
        float2(-0.37944, -0.425145),
        float2(0.628994, -0.189387),
        float2(-0.331257, -0.646864),
        float2(-0.467004, 0.439687),
    };

    float GetMipFromRougness(float roughness)
    {
        const float smoothness = 1.0 - roughness;
        return (1.0 - smoothness * smoothness) * 10.0;
    }

    /// Perform importance sampling
    ///     reflectVec: calculated vector of reflection
    ///     wsNormal: world-space normal of the surface
    ///     toCamera: direction from the pixel to the camera
    ///     specular: specular color
    ///     roughness: surface roughness
    ///     reflectionCubeColor: output color for diffuse

    // Implementation based on Epics 2013 course notes
    float3 ImportanceSampling(in float3 reflectVec, in float3 tangent, in float3 bitangent, in float3 wsNormal, in float3 toCamera,  in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    {
        reflectionCubeColor = 1.0;

        const float3 reflectSpec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

        const float3 V = normalize(-toCamera);
        const float3 N = normalize(wsNormal);
        const float ndv = saturate(abs(dot(N, V)));

        const float specMipLevel = GetMipFromRougness(roughness);

        float3 accumulatedColor = float3(0,0,0);
        for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
        {
            float3 kd = 1.0;
            float3 diffuseFactor = 0.0;
            float3 specularFactor = 0.0;

            {
                // Diffuse IBL
                const float rough = 1.0;
                const float mipLevel = 9.0;

                const float3 H = ImportanceSampleSimple(IMPORTANCE_KERNEL[i], rough, tangent, bitangent, N);
                const float3 L = 2.0 * dot( V, H ) * H - V;

                const float vdh = saturate(abs(dot(V, H)));
                const float ndh = saturate(abs(dot(N, H)));
                const float ndl = saturate(abs(dot(N, L)));

                const float3 sampledColor = SampleCubeLOD(ZoneCubeMap, float4(L, mipLevel));

                const float3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
                const float3 lightTerm = sampledColor;

                diffuseFactor = lightTerm * diffuseTerm;
            }

            {
                // Specular IBL
                const float rough = roughness;
                const float mipLevel = specMipLevel;

                const float3 H = ImportanceSampleSimple(IMPORTANCE_KERNEL[i], rough, tangent, bitangent, N);
                const float3 L = 2.0 * dot( V, H ) * H - V;
                const float3 sampledColor = SampleCubeLOD(ZoneCubeMap, float4(L, mipLevel));

                const float vdh = saturate(abs(dot(V, H)));
                const float ndh = saturate(abs(dot(N, H)));
                const float ndl = saturate(abs(dot(N, L)));

                const float3 fresnelTerm = Fresnel(specColor, vdh);
                const float distTerm = 1.0;//Distribution(ndh_, roughness);
                const float visTerm = Visibility(ndl, ndv, rough);
                const float3 lightTerm = sampledColor * ndl;

                const float pdf = ndl > 0.05 ? ImportanceSamplePDF(distTerm, ndh, vdh) : 4.0; // reduce artifacts at extreme grazing angles

                const float3 specularTerm = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv);

                // Energy conservation:
                // Specular conservation:
                specularFactor = lightTerm * specularTerm / pdf;
                specularFactor = max(saturate(normalize(specularFactor) * (length(sampledColor * specColor))), specularFactor);

                // Diffuse conservation:
                kd = 1.0 - specularFactor;
            }

            accumulatedColor += specularFactor + diffuseFactor * kd;
        }

        return (accumulatedColor / IMPORTANCE_SAMPLES);
    }


    float3 ImportanceSamplingSimple(in float3 reflectVec, in float3 tangent, in float3 bitangent, in float3 wsNormal, in float3 toCamera,  in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    {
        reflectionCubeColor = 1.0;

        reflectVec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

        const float3 Hn = normalize(-toCamera + wsNormal);
        const float ndv = saturate(dot(-toCamera, wsNormal));
        const float vdh = saturate(dot(-toCamera, Hn));
        const float ndh = saturate(dot(wsNormal, Hn));

        float3 accumulatedColor = float3(0,0,0);
        for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
        {
            float3 kd = 1.0;
            float3 diffuseFactor = 0.0;
            float3 specularFactor = 0.0;

            {
                // Diffuse IBL
                const float rough = 1.0;
                const float mipLevel = 9.0;

                const float3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, tangent, bitangent, wsNormal);
                const float3 sampleVec = wsNormal + perturb; //perturb by the sample vector

                const float3 sampledColor = SampleCubeLOD(ZoneCubeMap, float4(sampleVec, mipLevel));
                const float ndl = saturate(dot(sampleVec, wsNormal));

                const float3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
                const float3 lightTerm = sampledColor;

                diffuseFactor = lightTerm * diffuseTerm;
            }

            {
                // Specular IBL
                const float rough = roughness;
                const float mipLevel =  GetMipFromRougness(rough);

                const float3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, tangent, bitangent, reflectVec);
                const float3 sampleVec = reflectVec + perturb; //perturb by the sample vector

                const float3 sampledColor = SampleCubeLOD(ZoneCubeMap, float4(sampleVec, mipLevel));
                const float ndl = saturate(dot(sampleVec, wsNormal));

                const float3 fresnelTerm = SchlickFresnel(specColor, ndh) ;
                const float distTerm = 1.0; //Optimization, this term is mathematically cancelled out  //Distribution(ndh, roughness);
                const float visTerm = SmithGGXVisibility(ndl, ndv, rough);
                const float3 lightTerm = sampledColor * ndl;

                const float pdf = 1.0;//ImportanceSamplePDF(distTerm, ndh, vdh);

                specularFactor = lightTerm * SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv) / pdf;
                specularFactor *= pdf * ndv * (4.0 * ndl * ndv); // hacks
                kd = (1.0 - saturate(specularFactor)); //energy conservation
            }

            accumulatedColor += specularFactor + diffuseFactor * kd;
        }

        return accumulatedColor / IMPORTANCE_SAMPLES;
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

    float EnvBRDFApproxNonmetal( float Roughness, float NoV )
    {
        // Same as EnvBRDFApprox( 0.04, Roughness, NoV )
        const float2 c0 = { -1, -0.0275 };
        const float2 c1 = { 1, 0.0425 };
        float2 r = Roughness * c0 + c1;
        return min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
    }

    /// Calculate IBL contributation
    ///     reflectVec: reflection vector for cube sampling
    ///     wsNormal: surface normal in word space
    ///     toCamera: normalized direction from surface point to camera
    ///     roughness: surface roughness
    ///     ambientOcclusion: ambient occlusion
    float3 ImageBasedLighting(in float3 reflectVec, in float3 tangent, in float3 bitangent, in float3 wsNormal, in float3 toCamera, in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    {
        return ImportanceSampling(reflectVec, tangent, bitangent, wsNormal, toCamera, diffColor, specColor, roughness, reflectionCubeColor);
    }
#endif
