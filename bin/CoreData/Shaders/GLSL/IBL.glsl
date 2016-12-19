#line 10001
#ifdef COMPILEPS

    //
    // Legacy Importance Sampled IBL
    //

    // vec3 ImportanceSampleSimple(in vec2 Xi, in float roughness, in vec3 T, in vec3 B, in vec3 N)
    // {
    //     float a = roughness * roughness;
    //     mat3 tbn = mat3(T, B, N);
    //     #ifdef IBLFAST
    //         const float blurFactor = 0.0;
    //     #else
    //         const float blurFactor = 5.0;
    //     #endif
    //     vec2 xx = Xi.xy * blurFactor;
    //     xx = xx - 1.0 * trunc(xx/1.0); // hlsl style modulo
    //     vec3 Xi3 = mix(vec3(0,0,1), normalize(vec3(xx, 1.0)), a);
    //     vec3 XiWS = tbn * Xi3;
    //     return normalize(N + XiWS);
    // }

    // // Karis '13
    // vec3 ImportanceSampleGGX(in vec2 Xi, in float roughness, in vec3 T, in vec3 B, in vec3 N)
    // {
    //     float a = roughness * roughness;
    //     float Phi = 2.0 * M_PI * Xi.x;
    //     float CosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    //     float SinTheta = sqrt(1.0 - CosTheta * CosTheta);
    //     vec3 H = vec3(0,0,0);
    //     H.x = SinTheta * cos(Phi);
    //     H.y = SinTheta * sin(Phi);
    //     H.z = CosTheta;

    //     vec3 UpVector = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    //     vec3 TangentX = normalize(cross(UpVector, N));
    //     vec3 TangentY = cross(N, TangentX);
    //     // Tangent to world space
    //     return TangentX * H.x + TangentY * H.y + N * H.z;
    // }

    // #ifdef IBLFAST
    //     #define IMPORTANCE_SAMPLES 1
    // #else
    //     #define IMPORTANCE_SAMPLES 4
    // #endif

    // #define IMPORTANCE_KERNEL_SIZE 16
    // vec2 IMPORTANCE_KERNEL[IMPORTANCE_KERNEL_SIZE] = vec2[] (
    //     vec2(-0.0780436, 0.0558389),
    //     vec2(0.034318, -0.0635879),
    //     vec2(0.00230821, 0.0807279),
    //     vec2(0.0124638, 0.117585),
    //     vec2(0.093943, -0.0944602),
    //     vec2(0.139348, -0.109816),
    //     vec2(-0.181872, -0.129649),
    //     vec2(0.240066, -0.0494057),
    //     vec2(0.115965, -0.0374714),
    //     vec2(-0.294819, -0.100726),
    //     vec2(-0.149652, 0.37459),
    //     vec2(0.261695, -0.292813),
    //     vec2(-0.37944, -0.425145),
    //     vec2(0.628994, -0.189387),
    //     vec2(-0.331257, -0.646864),
    //     vec2(-0.467004, 0.439687)
    //   );

    //   float GetMipFromRougness(float roughness)
    //   {
    //       float smoothness = 1.0 - roughness;
    //       return (1.0 - smoothness * smoothness) * 10.0;
    //   }

    // /// Perform importance sampling
    // ///     reflectVec: calculated vector of reflection
    // ///     wsNormal: world-space normal of the surface
    // ///     toCamera: direction from the pixel to the camera
    // ///     specular: specular color
    // ///     roughness: surface roughness
    // ///     reflectionCubeColor: output color for diffuse
    // // Implementation based on Epics 2013 course notes
    // vec3 ImportanceSampling(in vec3 reflectVec, in vec3 tangent, in vec3 bitangent, in vec3 wsNormal, in vec3 toCamera,  in vec3 diffColor, in vec3 specColor, in float roughness, inout vec3 reflectionCubeColor)
    // {
    //     reflectionCubeColor = vec3(1,1,1);

    //     vec3 reflectSpec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

    //     vec3 V = normalize(-toCamera);
    //     vec3 N = normalize(wsNormal);
    //     float ndv = clamp(abs(dot(N, V)), 0.0, 1.0);

    //     float specMipLevel = GetMipFromRougness(roughness);

    //     vec3 accumulatedColor = vec3(0,0,0);
    //     for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
    //     {
    //         vec3 kd = vec3(1,1,1);
    //         vec3 diffuseFactor = vec3(0,0,0);
    //         vec3 specularFactor = vec3(0,0,0);

    //         {
    //             // Diffuse IBL
    //             const float rough = 1.0;
    //             const float mipLevel = 9.0;

    //             vec3 H = ImportanceSampleSimple(IMPORTANCE_KERNEL[i], rough, tangent, bitangent, N);
    //             vec3 L = 2.0 * dot( V, H ) * H - V;

    //             float vdh = clamp(abs(dot(V, H)), 0.0, 1.0);
    //             float ndh = clamp(abs(dot(N, H)), 0.0, 1.0);
    //             float ndl = clamp(abs(dot(N, L)), 0.0, 1.0);

    //             vec3 sampledColor = textureLod(sZoneCubeMap, L, mipLevel).rgb;

    //             vec3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
    //             vec3 lightTerm = sampledColor;

    //             diffuseFactor = lightTerm * diffuseTerm;
    //         }

    //         {
    //             // Specular IBL
    //             float rough = roughness;
    //             float mipLevel = specMipLevel;

    //             vec3 H = ImportanceSampleSimple(IMPORTANCE_KERNEL[i], rough, tangent, bitangent, N);
    //             vec3 L = 2.0 * dot( V, H ) * H - V;
    //             vec3 sampledColor = textureLod(sZoneCubeMap, L, mipLevel).rgb;

    //             float vdh = clamp(abs(dot(V, H)), 0.0, 1.0);
    //             float ndh = clamp(abs(dot(N, H)), 0.0, 1.0);
    //             float ndl = clamp(abs(dot(N, L)), 0.0, 1.0);

    //             vec3 fresnelTerm = Fresnel(specColor, vdh);
    //             float distTerm = 1.0; // Optimization, this term is mathematically cancelled out  -- Distribution(ndh, roughness);
    //             float visTerm = Visibility(ndl, ndv, rough);

    //             vec3 lightTerm = sampledColor * ndl;

    //             float pdf = ndl > 0.05 ? ImportanceSamplePDF(distTerm, ndh, vdh) : 4.0; // reduce artifacts at extreme grazing angles

    //             vec3 specularTerm = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv);

    //             // energy conservation:
    //             // Specular conservation:
    //             specularFactor = lightTerm * specularTerm / pdf;
    //             specularFactor = max(
    //               clamp(normalize(specularFactor) * (length(sampledColor * specColor)), 0.0, 1.0),
    //               specularFactor
    //             );

    //             // Diffuse conservation:
    //             //kd = (sampledColor * specColor)/specularFactor; //energy conservation
    //             kd = 1.0 - specularFactor;
    //         }

    //         accumulatedColor += specularFactor + diffuseFactor * kd;
    //     }

    //     return (accumulatedColor / IMPORTANCE_SAMPLES);
    // }

    // vec3 ImportanceSamplingSimple(in vec3 reflectVec, in vec3 tangent, in vec3 bitangent, in vec3 wsNormal, in vec3 toCamera,  in vec3 diffColor, in vec3 specColor, in float roughness, inout vec3 reflectionCubeColor)
    // {
    //     reflectionCubeColor = vec3(1,1,1);

    //     reflectVec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));

    //     vec3 Hn = normalize(-toCamera + wsNormal);
    //     float ndv = clamp(dot(-toCamera, wsNormal), 0.0, 1.0);
    //     float vdh = clamp(dot(-toCamera, Hn), 0.0, 1.0);
    //     float ndh = clamp(dot(wsNormal, Hn), 0.0, 1.0);

    //     vec3 accumulatedColor = vec3(0,0,0);
    //     for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
    //     {
    //         vec3 kd = vec3(1,1,1);
    //         vec3 diffuseFactor = vec3(0,0,0);
    //         vec3 specularFactor = vec3(0,0,0);

    //         {
    //             // Diffuse IBL
    //             const float rough = 1.0;
    //             const float mipLevel = 9.0;

    //             vec3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, tangent, bitangent, wsNormal);
    //             vec3 sampleVec = wsNormal + perturb; //perturb by the sample vector

    //             vec3 sampledColor = textureLod(sZoneCubeMap, sampleVec, mipLevel).rgb;
    //             float ndl = clamp(dot(sampleVec, wsNormal), 0.0, 1.0);

    //             vec3 diffuseTerm = Diffuse(diffColor, rough, ndv, ndl, vdh);
    //             vec3 lightTerm = sampledColor;

    //             diffuseFactor = lightTerm * diffuseTerm;
    //         }

    //         {
    //             // Specular IBL
    //             float rough = roughness;
    //             float mipLevel =  GetMipFromRougness(rough);

    //             vec3 perturb = ImportanceSampleGGX(IMPORTANCE_KERNEL[i].xy, rough, tangent, bitangent, reflectVec);
    //             vec3 sampleVec = reflectVec + perturb; //perturb by the sample vector

    //             vec3 sampledColor = textureCube(sZoneCubeMap, sampleVec, mipLevel).rgb;
    //             float ndl = clamp(dot(sampleVec, wsNormal), 0.0, 1.0);

    //             vec3 fresnelTerm = SchlickFresnel(specColor, ndh) ;
    //             float distTerm = 1.0; //Optimization, this term is mathematically cancelled out  //Distribution(ndh, roughness);
    //             float visTerm = SmithGGXVisibility(ndl, ndv, rough);
    //             vec3 lightTerm = sampledColor * ndl;

    //             float pdf = 1.0; //ImportanceSamplePDF(distTerm, ndh, vdh);

    //             specularFactor = lightTerm * SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv) / pdf;
    //             specularFactor *= pdf * ndv * (4.0 * ndl * ndv); // hacks
    //             kd = (1.0 - clamp(specularFactor, 0.0, 1.0)); //energy conservation
    //         }

    //         accumulatedColor += specularFactor + diffuseFactor * kd;
    //     }

    //     return accumulatedColor / IMPORTANCE_SAMPLES;
    // }

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

    float GetMipFromRoughness(float roughness)
    {
        float Level = 3 - 1.15 * log2( roughness );
        return 9.0 - 1 - Level;
    }


    vec3 EnvBRDFApprox (vec3 SpecularColor, float Roughness, float NoV)
    {
        vec4 c0 = vec4(-1, -0.0275, -0.572, 0.022 );
        vec4 c1 = vec4(1, 0.0425, 1.0, -0.04 );
        vec4 r = Roughness * c0 + c1;
        float a004 = min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
        vec2 AB = vec2( -1.04, 1.04 ) * a004 + r.zw;
        return SpecularColor * AB.x + AB.y;
    }

    vec3 FixCubeLookup(vec3 v) 
    {
        float M = max(max(abs(v.x), abs(v.y)), abs(v.z));
        float scale = (1024 - 1) / 1024;

        if (abs(v.x) != M) v.x += scale;
        if (abs(v.y) != M) v.y += scale;
        if (abs(v.z) != M) v.z += scale; 

        return v;
    }

    /// Calculate IBL contributation
    ///     reflectVec: reflection vector for cube sampling
    ///     wsNormal: surface normal in word space
    ///     toCamera: normalized direction from surface point to camera
    ///     roughness: surface roughness
    ///     ambientOcclusion: ambient occlusion
    vec3 ImageBasedLighting(vec3 reflectVec, vec3 tangent, vec3 bitangent, vec3 wsNormal, vec3 toCamera, vec3 diffColor, vec3 specColor, float roughness, inout vec3 reflectionCubeColor)
    {
        reflectVec = GetSpecularDominantDir(wsNormal, reflectVec, roughness);
        float ndv = clamp(dot(-toCamera, wsNormal), 0.0, 1.0);

        // PMREM Mipmapmode https://seblagarde.wordpress.com/2012/06/10/amd-cubemapgen-for-physically-based-rendering/
        //float GlossScale = 16.0;
        //float GlossBias = 5.0;
        float mipSelect = GetMipFromRoughness(roughness); //exp2(GlossScale * roughness * roughness + GlossBias) - exp2(GlossBias);

        // OpenGL ES does not support textureLod without extensions and does not have the sZoneCubeMap sampler,
        // so for now, sample without explicit LOD, and from the environment sampler, where the zone texture will be put
        // on mobile hardware
        #ifndef GL_ES
            vec3 cube = textureLod(sZoneCubeMap, FixCubeLookup(reflectVec), mipSelect).rgb;
            vec3 cubeD = textureLod(sZoneCubeMap, FixCubeLookup(wsNormal), 9.0).rgb;
        #else
            vec3 cube = textureCube(sEnvCubeMap, FixCubeLookup(reflectVec)).rgb;
            vec3 cubeD = textureCube(sEnvCubeMap, FixCubeLookup(wsNormal)).rgb;
        #endif

        // Fake the HDR texture
        float brightness = clamp(cAmbientColor.a, 0.0, 1.0);
        float darknessCutoff = clamp((cAmbientColor.a - 1.0) * 0.1, 0.0, 0.25);

        const float hdrMaxBrightness = 5.0;
        vec3 hdrCube = pow(cube + darknessCutoff, vec3(max(1.0, cAmbientColor.a)));
        hdrCube += max(vec3(0.0), hdrCube - vec3(1.0)) * hdrMaxBrightness;

        vec3 hdrCubeD = pow(cubeD + darknessCutoff, vec3(max(1.0, cAmbientColor.a)));
        hdrCubeD += max(vec3(0.0), hdrCubeD - vec3(1.0)) * hdrMaxBrightness;

        vec3 environmentSpecular = EnvBRDFApprox(specColor, roughness, ndv);
        vec3 environmentDiffuse = EnvBRDFApprox(diffColor, 1.0, ndv);

        return (hdrCube * environmentSpecular + hdrCubeD * environmentDiffuse) * brightness;
        //return ImportanceSampling(reflectVec, tangent, bitangent, wsNormal, toCamera, diffColor, specColor, roughness, reflectionCubeColor);
    }
#endif
