 #ifdef COMPILEPS

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
        
        //#ifdef IMPORTANCESAMPLE_HQ
        #define IMPORTANCE_SAMPLES 16
        vec2 IMPORTANCE_KERNEL[IMPORTANCE_SAMPLES] = vec2[] (
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
            vec2(-0.467004, 0.439687));

        
        // Karis '13
        vec3 ImportanceSampleGGX(vec2 Xi, float Roughness, vec3 N) 
        { 
            float a = Roughness * Roughness;
            float Phi = 2 * 3.14159 * Xi.x;
            float CosTheta = sqrt((1 - Xi.y) / (1 + (a*a - 1) * Xi.y));
            float SinTheta = sqrt(1 - CosTheta * CosTheta);
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
        
        /// Perform importance sampling
        ///     reflectVec: calculated vector of reflection
        ///     wsNormal: world-space normal of the surface
        ///     toCamera: direction from the pixel to the camera
        ///     specular: specular color
        ///     roughness: surface roughness
        ///     reflectionCubeColor: output color for diffuse
        vec3 ImportanceSampling(in vec3 reflectVec, in vec3 wsNormal, in vec3 toCamera, in vec3 specular, in float roughness, out vec3 reflectionCubeColor)
        {
            reflectionCubeColor = vec3(1.0, 1.0, 1.0);
            reflectVec = normalize(GetSpecularDominantDir(wsNormal, reflectVec, roughness));
            
            vec3 Hn = normalize(-toCamera + wsNormal);
            float ndv = clamp(dot(-toCamera, wsNormal), 0.0, 1.0);
            float vdh = clamp(dot(-toCamera, Hn), 0.0, 1.0);
            float ndh = clamp(dot(wsNormal, Hn), 0.0, 1.0);
            
            float mipSelect = roughness * 10;  // Lux-style
            vec3 accumulatedColor = vec3(0,0,0);
            for (int i = 0; i < IMPORTANCE_SAMPLES; ++i)
            {
                vec2 Xi = IMPORTANCE_KERNEL[i].xy;
                vec3 perturb = ImportanceSampleGGX(Xi, roughness, reflectVec);
                vec3 sampleVec = reflectVec + perturb; //perturb by the sample vector
                
                float ndl = clamp(dot(sampleVec, wsNormal), 0.0, 1.0);
                
                vec3 sampledColor = textureCube(sZoneCubeMap, sampleVec, mipSelect).rgb;
                accumulatedColor += (sampledColor * SchlickFresnel(specular, ndh) * ndv * SmithGGXVisibility(ndl, ndv, roughness) * ndl);
            }
            
            return accumulatedColor / IMPORTANCE_SAMPLES;
        }
            
        /// Epic's approximation, convenient outside of mobile as well - very tolerant of 'lazy' IBL such as unfiltered mips
        /// https://www.unrealengine.com/blog/physically-based-shading-on-mobile
        ///     specColor: specular color of the fragment
        ///     roughness: surface roughness
        ///     nDotV: dot product of normal and view vectors
        vec3 EnvBRDFApprox(in vec3 specColor, in float roughness, in float nDotV )
        {            
            vec4 c0 = vec4(-1.0, -0.0275, -0.572, 0.022);
            vec4 c1 = vec4(1.0, 0.0425, 1.0, -0.04 );
            vec4 r = roughness * c0 + c1;
            float a004 = min( r.x * r.x, exp2( -9.28 * nDotV)) * r.x + r.y;
            vec2 AB = vec2( -1.04, 1.04) * a004 + r.zw;
            return specColor * AB.x + AB.y;
            }

        /// Calculate IBL contributation
        ///     reflectVec: reflection vector for cube sampling
        ///     wsNormal: surface normal in word space
        ///     toCamera: normalized direction from surface point to camera
        ///     roughness: surface roughness
        ///     ambientOcclusion: ambient occlusion
        vec3 ImageBasedLighting(in vec3 reflectVec, in vec3 wsNormal, in vec3 toCamera, in vec3 specular, in float roughness, out vec3 reflectionCubeColor)
        {    
            reflectVec = GetSpecularDominantDir(wsNormal, reflectVec, roughness);
            vec3 Hn = normalize(-toCamera + wsNormal);
            float vdh = clamp(dot(-toCamera, Hn), 0.0, 1.0);
            float ndv = clamp(dot(-toCamera, wsNormal), 0.0, 1.0);
            
            float smoothness = 1.0 - roughness;
            float mipLevel = (1.0 - smoothness * smoothness) * 10.0;
            
            vec3 cube =  ImportanceSampling(reflectVec, wsNormal, toCamera, specular, roughness, reflectionCubeColor);
            reflectionCubeColor = textureCube(sZoneCubeMap, wsNormal, 9.6).rgb;
            
            vec3 environmentSpecular = EnvBRDFApprox(specular, roughness, ndv);
          
            return environmentSpecular * cube;
        }
#endif