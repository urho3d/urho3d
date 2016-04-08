#line 20001
#ifdef COMPILEPS
  #ifdef PBR
    /// Diffuse factors

    /// Oren-Nayar diffuse factor
    ///     diffuseColor: input rgb
    ///     roughness: roughness of the surface
    ///     NdotV: dot prod of surface normal and view direction
    ///     NdotL: dot prod of surface normal and light direction
    ///     VdotH: dot prod of view direction and half-angle
    vec3 OrenNayarDiffuse(in vec3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        float rough2 = roughness * roughness;

        float VdotL = 2.0 * VdotH - 1.0;
        float majorCtrl = 1.0 - 0.5 * rough2 / (rough2 + 0.33);
        float cosRi = VdotL - NdotV * NdotL;
        float minorCtrl = 0.4545 * rough2 / (rough2 + 0.09) * cosRi * (cosRi >= 0.0 ? min(1.0, NdotL / NdotV) : NdotL);
        return diffuseColor / M_PI * (NdotL * majorCtrl + minorCtrl);
    }

    /// Lambertian diffuse factor
    ///     diffuseColor: input rgb
    ///     roughness: roughness of the surface
    ///     NdotV: dot prod of surface normal and view direction
    ///     NdotL: dot prod of surface normal and light direction
    ///     VdotH: dot prod of view direction and half-angle
    vec3 LambertianDiffuse(in vec3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        return diffuseColor * NdotL;
    }

    vec3 BurleyDiffuse(in vec3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        float energyBias = mix(0.0, 0.5, roughness);
        float energyFactor = mix(1.0, 1.0 / 1.51, roughness);
        float fd90 = energyBias + 2.0 * VdotH * VdotH * roughness;
        const float f0 = 1.0;
        float lightScatter = f0 + (fd90 - f0) * pow(1.0 - NdotL, 5.0);
        float viewScatter = f0 + (fd90 - f0) * pow(1.0f - NdotV, 5.0);

        return diffuseColor * lightScatter * viewScatter * energyFactor;
    }

    vec3 Diffuse(in vec3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        return BurleyDiffuse(diffuseColor, roughness, NdotV, NdotL, VdotH);
    }

    /// Specular BRDF
    vec3 CookTorranceBRDF(in float D, in vec3 F, in float G, in float NdotL, in float NdotV)
    {
        return D * F * G / (4.0 *  max(NdotL * NdotV, M_EPSILON));
    }

    vec3 SpecularBRDF(in float D, in vec3 F, in float G, in float NdotL, in float NdotV)
    {
        return CookTorranceBRDF(D, F, G, NdotL, NdotV);
    }

    /// Specular probability density function (for importance sampling)
    float CookTorrancePDF(in float D, in float NdotH, in float VdotH)
    {
        return D * NdotH / (4.0 * VdotH);
    }

    float ImportanceSamplePDF(in float D, in float NdotH, in float VdotH)
    {
        return CookTorrancePDF(D, NdotH, VdotH);
    }

    /// Fresnel Terms

    /// Fresnel factor
    ///     specular: Specular color input
    ///     VdotH: dot product of view direction and half-angle
    vec3 SchlickFresnel(in vec3 specular, in float VdotH)
    {
        return specular + (vec3(1.0, 1.0, 1.0) - specular) * pow(1.0 - VdotH, 5.0);
    }

    /// Fresnel factor, spherical gaussian in Schlick approximation; https://seblagarde.wordpress.com/2012/06/03/spherical-gaussien-approximation-for-blinn-phong-phong-and-fresnel/
    ///     specular: specular color of the surface
    ///     VdotH: dot product of view direction and half-angle
    vec3 SchlickGaussianFresnel(in vec3 specular, in float VdotH)
    {
        float sphericalGaussian = pow(2.0, (-5.55473 * VdotH - 6.98316) * VdotH);
        return specular + (vec3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
    }

    vec3 Fresnel(in vec3 specular, in float VdotH)
    {
        return SchlickFresnel(specular, VdotH);
    }

    /// Visibility terms

    /// Smith GGX Visibility
    ///     NdotL: dot-prod of surface normal and light direction
    ///     NdotV: dot-prod of surface normal and view direction
    ///     roughness: surface roughness
    float SmithGGXVisibility(in float NdotL, in float NdotV, in float roughness)
    {
        // BUG ?
        float rough2 = roughness * roughness;
        float gSmithV = NdotV + sqrt(NdotV * (NdotV - NdotV * rough2) + rough2);
        float gSmithL = NdotL + sqrt(NdotL * (NdotL - NdotL * rough2) + rough2);
        return 1.0 / ( gSmithV * gSmithL );
    }

    float SmithGGXG(in float factor, in float k)
    {
        return 2.0 * factor / (factor + sqrt(k + (1.0 - k) * (factor * factor))) ;
    }

    float SchlickG(in float factor, in float k)
    {
        return factor / (factor * (1.0 - k) + k);
    }

    float SmithGGXVisibility2(in float NdotL, in float NdotV, in float roughness)
    {
        float k = roughness * roughness;
        return (SmithGGXG(NdotL, k) * SmithGGXG(NdotV, k));
    }

    /// Schlick approximation of Smith GGX
    ///     NdotL: dot product of surface normal and light direction
    ///     NdotV: dot product of surface normal and view direction
    ///     roughness: surface roughness
    float SmithGGXSchlickVisibility(float NdotL, float NdotV, float roughness)
    {
        float rough2 = roughness * roughness;
        return (SchlickG(NdotL, rough2) * SchlickG(NdotV, rough2)) * 0.25; // divided by four
    }

    float SmithGGXSchlickVisibility2(float NdotL, float NdotV, float roughness)
    {
        float rough = roughness + 1.0;
        float a = rough * rough;
        float k =  a / 8.0;
        return (SchlickG(NdotL, k) * SchlickG(NdotV, k));
    }

    float SchlickBeckmannVisibility(in float NdotL, in float NdotV, in float roughness)
    {
        float a = roughness * roughness;
        float k =  a * sqrt(2.0 / M_PI);
        return (SchlickG(NdotL, k) * SchlickG(NdotV, k));
    }

    float Visibility(in float NdotL, in float NdotV, in float roughness)
    {
        return SmithGGXVisibility2(NdotL, NdotV, roughness);
    }

    /// Normal Distributions

    float BlinnPhongDistribution(in float NdotH, in float roughness)
    {
        float specPower = max((2.0 / (roughness * roughness)) - 2.0, 1e-4); // Calculate specular power from roughness
        return pow(clamp(NdotH, 0.0, 1.0), specPower);
    }

    /// Beckmann normal distribution
    ///     NdotH: dot-prod of surface normal and half-angle
    ///     roughness: surface roughness
    float BeckmannDistribution(in float NdotH, in float roughness)
    {
        float rough2 = roughness * roughness;
        float roughnessA = 1.0 / (4.0 * rough2 * pow(NdotH, 4.0));
        float roughnessB = NdotH * NdotH - 1.0;
        float roughnessC = rough2 * NdotH * NdotH;
        return roughnessA * exp(roughnessB / roughnessC);
    }

    /// Trowbridge-Reitz GGX normal distribution
    ///     NdotH: dot-prod of surface normal and half-angle
    ///     roughness: surface roughness
    float GGXDistribution(in float NdotH, in float roughness)
    {
        float rough2 = roughness * roughness;
        float tmp = roughness / max(M_EPSILON, NdotH * NdotH * (rough2 - 1.0) + 1.0);
        return tmp * tmp / M_PI;
    }

    float Distribution(in float NdotH, in float roughness)
    {
        return GGXDistribution(NdotH, roughness);
    }
  #endif
#endif
