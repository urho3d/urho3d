#line 10001
#ifdef COMPILEPS

    float GetMipFromRoughness(float roughness)
    {
        return (roughness * 12.0 - pow(roughness, 6.0) * 1.5);
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
    vec3 ImageBasedLighting(vec3 reflectVec, vec3 wsNormal, vec3 toCamera, vec3 diffColor, vec3 specColor, float roughness, inout vec3 reflectionCubeColor)
    {
        roughness = max(roughness, 0.08);
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
    }
#endif
