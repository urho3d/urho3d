#ifdef COMPILEPS

 /// Diffuse factors

    /// Oren-Nayar diffuse factor
    ///     diffuseColor: input rgb
    ///     roughness: roughness of the surface
    ///     nDotV: dot prod of surface normal and view direction
    ///     nDotL: dot prod of surface normal and light direction
    ///     vDotH: dot prod of view direction and half-angle
    vec3 OrenNayarDiffuse(in vec3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
    {
        float rough2 = roughness * roughness;
        
        float vDotL = 2.0 * vDotH - 1.0;
        float majorCtrl = 1.0 - 0.5 * rough2 / (rough2 + 0.33);
        float cosRi = vDotL - nDotV * nDotL;
        float minorCtrl = 0.4545 * rough2 / (rough2 + 0.09) * cosRi * (cosRi >= 0.0 ? min(1.0, nDotL / nDotV) : nDotL);
        return diffuseColor / 3.141596 * (nDotL * majorCtrl + minorCtrl);
    }

    /// Lambertian diffuse factor
    ///     diffuseColor: input rgb
    ///     roughness: roughness of the surface
    ///     nDotV: dot prod of surface normal and view direction
    ///     nDotL: dot prod of surface normal and light direction
    ///     vDotH: dot prod of view direction and half-angle
    vec3 LambertianDiffuse(in vec3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
    {
        return diffuseColor * nDotL;
    }
    
    vec3 BurleyDiffuse(in vec3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
    {
        
        float energyBias = mix(0, 0.5, roughness);
        float energyFactor = mix(1.0, 1.0 / 1.51, roughness);
        float fd90 = energyBias + 2.0 * vDotH * vDotH * roughness;
        float f0 = 1.0;
        float lightScatter = f0 + (fd90 - f0) * pow(1.0f - nDotL, 5.0f);
        float viewScatter = f0 + (fd90 - f0) * pow(1.0f - nDotV, 5.0f);
        
        return diffuseColor * lightScatter * viewScatter * energyFactor;
    }
/// Fresnel Terms

    /// Fresnel factor
    ///     specular: Specular color input
    ///     vDotH: dot product of view direction and half-angle
    vec3 SchlickFresnel(in vec3 specular, in float vDotH)
    {
        return specular + (vec3(1.0, 1.0, 1.0) - specular) * pow(1.0 - vDotH, 5.0);
    }
    
    /// Fresnel factor, spherical gaussian in Schlick approximation; https://seblagarde.wordpress.com/2012/06/03/spherical-gaussien-approximation-for-blinn-phong-phong-and-fresnel/
    ///     specular: specular color of the surface
    ///     vDotH: dot product of view direction and half-angle
    vec3 SchlickGaussianFresnel(in vec3 specular, in float vDotH)
    {
        float sphericalGaussian = pow(2.0, (-5.55473 * vDotH - 6.98316) * vDotH);
        return specular + (vec3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
    }
    
// Visibility terms

    /// Smith GGX Visibility
    ///     nDotL: dot-prod of surface normal and light direction
    ///     nDotV: dot-prod of surface normal and view direction
    ///     roughness: surface roughness
    float SmithGGXVisibility(in float nDotL, in float nDotV, in float roughness)
    {
        float rough2 = roughness * roughness;
        float gSmithV = nDotV + sqrt(nDotV * (nDotV - nDotV * rough2) + rough2);
        float gSmithL = nDotL + sqrt(nDotL * (nDotL - nDotL * rough2) + rough2);
        return 1.0 / ( gSmithV * gSmithL );
    }
    
    
    float SchlickG1(in float factor, in float rough2)
    {
        return 1.0 / (factor * (1.0 - rough2) + rough2);
    }
    
    /// Schlick approximation of Smith GGX
    ///     nDotL: dot product of surface normal and light direction
    ///     nDotV: dot product of surface normal and view direction
    ///     roughness: surface roughness
    float SchlickVisibility(float nDotL, float nDotV, float roughness)
    {
        float rough2 = roughness * roughness;
        return (SchlickG1(nDotL, rough2) * SchlickG1(nDotV, rough2)) * 0.25; // divided by four
    }
    
/// Normal Distributions
    
    /// Beckmann normal distribution
    ///     nDotH: dot-prod of surface normal and half-angle
    ///     roughness: surface roughness
    float BeckmannDistribution(in float nDotH, in float roughness)
    {
        float rough2 = roughness * roughness;
        float roughnessA = 1.0 / (4.0 * rough2 * pow(nDotH, 4.0));
        float roughnessB = nDotH * nDotH - 1.0;
        float roughnessC = rough2 * nDotH * nDotH;
        return roughnessA * exp(roughnessB / roughnessC);
    }
    

    /// Trowbridge-Reitz GGX normal distribution
    ///     nDotH: dot-prod of surface normal and half-angle
    ///     roughness: surface roughness
    float GGXDistribution(in float nDotH, in float roughness)
    {
        float rough2 = roughness * roughness;
        float tmp = roughness / max(1e-8, nDotH * nDotH * (rough2 - 1.0) + 1.0);
        return tmp * tmp * 0.3141596;
    }

#endif
