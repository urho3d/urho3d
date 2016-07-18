#line 10001
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

    float GetMipFromRougness(float roughness)
    {
        float smoothness = 1.0 - roughness;
        return (1.0 - smoothness * smoothness) * 10.0;
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
        
        float mipSelect = roughness  * 9;

        vec3 cube = texture2DLod(sZoneCubeMap, reflectVec, mipSelect).rgb;
        vec3 environmentSpecular = EnvBRDFApprox(specColor, roughness, ndv);

        return cube * environmentSpecular;
    }
#endif
