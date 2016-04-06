#ifdef COMPILEPS
    float3 ImportanceSampleGGX(float2 Xi, float Roughness, float3 N)
    {
        float a = Roughness * Roughness;
        float Phi = 2 * M_PI * Xi.x;
        float CosTheta = sqrt((1 - Xi.y) / (1 + (a*a - 1) * Xi.y));
        float SinTheta = sqrt(1 - CosTheta * CosTheta);
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

    float3 GetSpecularDominantDir(float3 normal, float3 reflection, float roughness)
    {
        const float smoothness = 1.0 - roughness;
        const float lerpFactor = smoothness * (sqrt(smoothness) + roughness);
        return lerp(normal, reflection, lerpFactor);
    }

    #define IMPORTANCE_SAMPLES 16
    static const float2 IMPORTANCE_KERNEL[IMPORTANCE_SAMPLES] =
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

    float1 GetMipFromRougness(float roughness)
    {
        const float smoothness = 1.0 - roughness;
        return (1.0 - smoothness * smoothness) * 10.0;
    }

    // Implementation based on Epics 2013 course notes
    float3 ImportanceSampling(in float3 reflectVec, in float3 wsNormal, in float3 toCamera,  in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    {
        reflectionCubeColor = 1.0;

        const float3 reflectSpec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

        const float3 V = normalize(-toCamera);
        const float3 N = normalize(wsNormal);
        const float ndv = saturate(dot(N, V));

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

                const float3 H = ImportanceSampleGGX(IMPORTANCE_KERNEL[i], rough, N);
                const float3 L = N + H;

                const float vdh = saturate(dot(V, H));
                const float ndh = saturate(dot(N, H));
                const float ndl = saturate(dot(N, L));

                //if (ndl > 0.0)
                {
                    const float3 sampledColor = (SampleCubeLOD(ZoneCubeMap, float4(L, mipLevel)));

                    const float3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
                    const float3 lightTerm = sampledColor;

                    diffuseFactor = lightTerm * diffuseTerm;
                }
            }

            {
                // Specular IBL
                const float rough = roughness;
                const float mipLevel = specMipLevel;

                const float3 H = ImportanceSampleGGX(IMPORTANCE_KERNEL[i], rough, N);
                const float3 L = 2 * dot( V, H ) * H - V;

                const float vdh = saturate(dot(V, H));
                const float ndh = saturate(dot(N, H));
                const float ndl = saturate(dot(N, L));

                if (ndl > 0.05)
                {
                    const float3 sampledColor = (SampleCubeLOD(ZoneCubeMap, float4(L, mipLevel)));

                    const float3 fresnelTerm = Fresnel(specColor, vdh);
                    const float distTerm = 1.0; // Optimization, this term is mathematically cancelled out  -- Distribution(ndh, roughness);
                    const float visTerm = Visibility(ndl, ndv, rough);
                    const float3 lightTerm = sampledColor * ndl;

                    const float3 specularTerm = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv);
                    const float3 pdf = ImportanceSamplePDF(distTerm, ndh, vdh);

                    specularFactor = lightTerm * specularTerm / pdf;
                }
                else // reduce artifacts at extreme grazing angles
                {
                    const float ndl_ = max(0.01, ndl);
                    const float ndh_ = max(0.01, ndh);
                    const float vdh_ = max(0.01, vdh);
                    const float ndv_ = max(0.01, ndv);

                    const float3 sampledColor = SampleCubeLOD(ZoneCubeMap, float4(L, mipLevel));

                    const float3 fresnelTerm = Fresnel(specColor, vdh_);
                    const float distTerm = 1.0;//Distribution(ndh_, roughness);
                    const float visTerm = Visibility(ndl_, ndv_, rough);
                    const float3 lightTerm = sampledColor * ndl_;

                    const float3 specularTerm = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl_, ndv_);
                    float roughFactor = saturate(1.0 - rough);
                    roughFactor *= roughFactor * roughFactor;

                    specularFactor = sampledColor * fresnelTerm * roughFactor;
                }

                kd = 1.0 - saturate(specularFactor); //energy conservation
            }
            accumulatedColor += specularFactor + diffuseFactor * kd;
        }

        return (accumulatedColor / IMPORTANCE_SAMPLES);
    }

    float3 ImportanceSamplingSimple(in float3 reflectVec, in float3 wsNormal, in float3 toCamera,  in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
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

                const float3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, wsNormal);
                const float3 sampleVec = wsNormal + perturb; //perturb by the sample vector

                const float3 sampledColor = (SampleCubeLOD(ZoneCubeMap, float4(sampleVec, mipLevel)));
                const float ndl = saturate(dot(sampleVec, wsNormal));

                const float3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
                const float3 lightTerm = sampledColor;

                diffuseFactor = lightTerm * diffuseTerm;
            }

            {
                // Specular IBL
                const float rough = roughness;
                const float mipLevel =  GetMipFromRougness(rough);

                const float3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, reflectVec);
                const float3 sampleVec = reflectVec + perturb; //perturb by the sample vector

                const float3 sampledColor = (SampleCubeLOD(ZoneCubeMap, float4(sampleVec, mipLevel)));
                const float ndl = saturate(dot(sampleVec, wsNormal));

                const float3 fresnelTerm = SchlickFresnel(specColor, ndh) ;
                const float distTerm = 1.0; //Optimization, this term is mathematically cancelled out  //Distribution(ndh, roughness);
                const float visTerm = SmithGGXVisibility(ndl, ndv, rough);
                const float3 lightTerm = sampledColor * ndl;

                const float3 pdf = 1.0;//ImportanceSamplePDF(distTerm, ndh, vdh);

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

    float3 ImageBasedLighting(in float3 reflectVec, in float3 wsNormal, in float3 toCamera, in float3 diffColor, in float3 specColor, in float roughness, inout float3 reflectionCubeColor)
    {
        return ImportanceSampling(reflectVec, wsNormal, toCamera, diffColor, specColor, roughness, reflectionCubeColor);
    }
#endif
