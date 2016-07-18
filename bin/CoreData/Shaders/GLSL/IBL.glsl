#line 10001
#ifdef COMPILEPS
    vec3 ImportanceSampleSimple(in vec2 Xi, in float roughness, in vec3 T, in vec3 B, in vec3 N)
    {
        float a = roughness * roughness;
        mat3 tbn = mat3(T, B, N);
        #ifdef IBLFAST
            const float blurFactor = 0.0;
        #else
            const float blurFactor = 5.0;
        #endif
        vec2 xx = Xi.xy * blurFactor;
        xx = xx - 1.0 * trunc(xx/1.0); // hlsl style modulo
        vec3 Xi3 = mix(vec3(0,0,1), normalize(vec3(xx, 1.0)), a);
        vec3 XiWS = tbn * Xi3;
        return normalize(N + XiWS);
    }

    // Karis '13
    vec3 ImportanceSampleGGX(in vec2 Xi, in float roughness, in vec3 T, in vec3 B, in vec3 N)
    {
        float a = roughness * roughness;
        float Phi = 2.0 * M_PI * Xi.x;
        float CosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
        float SinTheta = sqrt(1.0 - CosTheta * CosTheta);
        vec3 H = vec3(0,0,0);
        H.x = SinTheta * cos(Phi);
        H.y = SinTheta * sin(Phi);
        H.z = CosTheta;

        vec3 UpVector = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
        vec3 TangentX = normalize(cross(UpVector, N));
        vec3 TangentY = cross(N, TangentX);
        // Tangent to world space
        return TangentX * H.x + TangentY * H.y + N * H.z;
    }

    /// Determine reflection vector based on surface roughness, rougher uses closer to the normal and smoother uses closer to the reflection vector
    ///     normal: surface normal
    ///     reflection: vector of reflection off of the surface
    ///     roughness: surface roughness
    vec3 GetSpecularDominantDir(vec3 normal, vec3 reflection, float roughness)
    {
        float smoothness = 1.0 - roughness;
        float lerpFactor = smoothness * (sqrt(smoothness) + roughness);
        return mix(normal, reflection, lerpFactor);
    }

    #ifdef IBLFAST
        #define IMPORTANCE_SAMPLES 1
    #else
        #define IMPORTANCE_SAMPLES 4
    #endif

    #define IMPORTANCE_KERNEL_SIZE 16
    vec2 IMPORTANCE_KERNEL[IMPORTANCE_KERNEL_SIZE] = vec2[] (
        vec2(-0.0780436, 0.0558389),
        vec2(0.034318, -0.0635879),
        vec2(0.00230821, 0.0807279),
        vec2(0.0124638, 0.117585),
        vec2(0.093943, -0.0944602),
        vec2(0.139348, -0.109816),
        vec2(-0.181872, -0.129649),
        vec2(0.240066, -0.0494057),
        vec2(0.115965, -0.0374714),
        vec2(-0.294819, -0.100726),
        vec2(-0.149652, 0.37459),
        vec2(0.261695, -0.292813),
        vec2(-0.37944, -0.425145),
        vec2(0.628994, -0.189387),
        vec2(-0.331257, -0.646864),
        vec2(-0.467004, 0.439687)
      );

      float GetMipFromRougness(float roughness)
      {
          float smoothness = 1.0 - roughness;
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
    vec3 ImportanceSampling(in vec3 reflectVec, in vec3 tangent, in vec3 bitangent, in vec3 wsNormal, in vec3 toCamera,  in vec3 diffColor, in vec3 specColor, in float roughness, inout vec3 reflectionCubeColor)
    {
        reflectionCubeColor = vec3(1,1,1);

        vec3 reflectSpec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

        vec3 V = normalize(-toCamera);
        vec3 N = normalize(wsNormal);
        float ndv = clamp(abs(dot(N, V)), 0.0, 1.0);

        float specMipLevel = GetMipFromRougness(roughness);

        vec3 accumulatedColor = vec3(0,0,0);
        for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
        {
            vec3 kd = vec3(1,1,1);
            vec3 diffuseFactor = vec3(0,0,0);
            vec3 specularFactor = vec3(0,0,0);

            {
                // Diffuse IBL
                const float rough = 1.0;
                const float mipLevel = 9.0;

                vec3 H = ImportanceSampleSimple(IMPORTANCE_KERNEL[i], rough, tangent, bitangent, N);
                vec3 L = 2.0 * dot( V, H ) * H - V;

                float vdh = clamp(abs(dot(V, H)), 0.0, 1.0);
                float ndh = clamp(abs(dot(N, H)), 0.0, 1.0);
                float ndl = clamp(abs(dot(N, L)), 0.0, 1.0);

                vec3 sampledColor = textureLod(sZoneCubeMap, L, mipLevel).rgb;

                vec3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
                vec3 lightTerm = sampledColor;

                diffuseFactor = lightTerm * diffuseTerm;
            }

            {
                // Specular IBL
                float rough = roughness;
                float mipLevel = specMipLevel;

                vec3 H = ImportanceSampleSimple(IMPORTANCE_KERNEL[i], rough, tangent, bitangent, N);
                vec3 L = 2.0 * dot( V, H ) * H - V;
                vec3 sampledColor = textureLod(sZoneCubeMap, L, mipLevel).rgb;

                float vdh = clamp(abs(dot(V, H)), 0.0, 1.0);
                float ndh = clamp(abs(dot(N, H)), 0.0, 1.0);
                float ndl = clamp(abs(dot(N, L)), 0.0, 1.0);

                vec3 fresnelTerm = Fresnel(specColor, vdh);
                float distTerm = 1.0; // Optimization, this term is mathematically cancelled out  -- Distribution(ndh, roughness);
                float visTerm = Visibility(ndl, ndv, rough);

                vec3 lightTerm = sampledColor * ndl;

                float pdf = ndl > 0.05 ? ImportanceSamplePDF(distTerm, ndh, vdh) : 4.0; // reduce artifacts at extreme grazing angles

                vec3 specularTerm = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv);

                // energy conservation:
                // Specular conservation:
                specularFactor = lightTerm * specularTerm / pdf;
                specularFactor = max(
                  clamp(normalize(specularFactor) * (length(sampledColor * specColor)), 0.0, 1.0),
                  specularFactor
                );

                // Diffuse conservation:
                //kd = (sampledColor * specColor)/specularFactor; //energy conservation
                kd = 1.0 - specularFactor;
            }

            accumulatedColor += specularFactor + diffuseFactor * kd;
        }

        return (accumulatedColor / IMPORTANCE_SAMPLES);
    }

    vec3 ImportanceSamplingSimple(in vec3 reflectVec, in vec3 tangent, in vec3 bitangent, in vec3 wsNormal, in vec3 toCamera,  in vec3 diffColor, in vec3 specColor, in float roughness, inout vec3 reflectionCubeColor)
    {
        reflectionCubeColor = vec3(1,1,1);

        reflectVec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

        vec3 Hn = normalize(-toCamera + wsNormal);
        float ndv = clamp(dot(-toCamera, wsNormal), 0.0, 1.0);
        float vdh = clamp(dot(-toCamera, Hn), 0.0, 1.0);
        float ndh = clamp(dot(wsNormal, Hn), 0.0, 1.0);

        vec3 accumulatedColor = vec3(0,0,0);
        for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
        {
            vec3 kd = vec3(1,1,1);
            vec3 diffuseFactor = vec3(0,0,0);
            vec3 specularFactor = vec3(0,0,0);

            {
                // Diffuse IBL
                const float rough = 1.0;
                const float mipLevel = 9.0;

                vec3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, tangent, bitangent, wsNormal);
                vec3 sampleVec = wsNormal + perturb; //perturb by the sample vector

                vec3 sampledColor = textureLod(sZoneCubeMap, sampleVec, mipLevel).rgb;
                float ndl = clamp(dot(sampleVec, wsNormal), 0.0, 1.0);

                vec3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
                vec3 lightTerm = sampledColor;

                diffuseFactor = lightTerm * diffuseTerm;
            }

            {
                // Specular IBL
                float rough = roughness;
                float mipLevel =  GetMipFromRougness(rough);

                vec3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, tangent, bitangent, reflectVec);
                vec3 sampleVec = reflectVec + perturb; //perturb by the sample vector

                vec3 sampledColor = textureCube(sZoneCubeMap, sampleVec, mipLevel).rgb;
                float ndl = clamp(dot(sampleVec, wsNormal), 0.0, 1.0);

                vec3 fresnelTerm = SchlickFresnel(specColor, ndh) ;
                float distTerm = 1.0; //Optimization, this term is mathematically cancelled out  //Distribution(ndh, roughness);
                float visTerm = SmithGGXVisibility(ndl, ndv, rough);
                vec3 lightTerm = sampledColor * ndl;

                float pdf = 1.0; //ImportanceSamplePDF(distTerm, ndh, vdh);

                specularFactor = lightTerm * SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv) / pdf;
                specularFactor *= pdf * ndv * (4.0 * ndl * ndv); // hacks
                kd = (1.0 - clamp(specularFactor, 0.0, 1.0)); //energy conservation
            }

            accumulatedColor += specularFactor + diffuseFactor * kd;
        }

        return accumulatedColor / IMPORTANCE_SAMPLES;
    }


    /// Calculate IBL contributation
    ///     reflectVec: reflection vector for cube sampling
    ///     wsNormal: surface normal in word space
    ///     toCamera: normalized direction from surface point to camera
    ///     roughness: surface roughness
    ///     ambientOcclusion: ambient occlusion
    vec3 ImageBasedLighting(in vec3 reflectVec, in vec3 tangent, in vec3 bitangent, in vec3 wsNormal, in vec3 toCamera, in vec3 diffColor, in vec3 specColor, in float roughness, inout vec3 reflectionCubeColor)
    {
        return ImportanceSampling(reflectVec, tangent, bitangent, wsNormal, toCamera, diffColor, specColor, roughness, reflectionCubeColor);
    }
#endif
