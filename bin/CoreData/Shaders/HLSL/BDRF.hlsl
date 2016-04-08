#ifdef COMPILEPS
  #ifdef PBR
    /// Diffuse factors

    /// Oren-Nayar diffuse factor
    ///     diffuseColor: input rgb
    ///     roughness: roughness of the surface
    ///     NdotV: dot prod of surface normal and view direction
    ///     NdotL: dot prod of surface normal and light direction
    ///     VdotH: dot prod of view direction and half-angle
    float3 OrenNayarDiffuse(in float3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        const float rough2 = roughness * roughness;

        const float VdotL = 2.0 * VdotH - 1.0;
        const float majorCtrl = 1.0 - 0.5 * rough2 / (rough2 + 0.33);
        const float cosRi = VdotL - NdotV * NdotL;
        const float minorCtrl = 0.4545 * rough2 / (rough2 + 0.09) * cosRi * (cosRi >= 0.0 ? min(1., NdotL / NdotV) : NdotL);
        return diffuseColor / M_PI * ( NdotL * majorCtrl + minorCtrl);
    }

    /// Lambertian diffuse factor
    ///     diffuseColor: input rgb
    ///     roughness: roughness of the surface
    ///     NdotV: dot prod of surface normal and view direction
    ///     NdotL: dot prod of surface normal and light direction
    ///     VdotH: dot prod of view direction and half-angle
    float3 LambertianDiffuse(in float3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        return diffuseColor * NdotL;
    }

    float3 BurleyDiffuse(in float3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        const float energyBias = lerp(0, 0.5, roughness);
        const float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);
        const float fd90 = energyBias + 2.0 * VdotH * VdotH * roughness;
        const float f0 = 1.0;
        const float lightScatter = f0 + (fd90 - f0) * pow(1.0f - NdotL, 5.0f);
        const float viewScatter = f0 + (fd90 - f0) * pow(1.0f - NdotV, 5.0f);

        return diffuseColor * lightScatter * viewScatter * energyFactor;
    }

    float3 Diffuse(in float3 diffuseColor, in float roughness, in float NdotV, in float NdotL, in float VdotH)
    {
        return BurleyDiffuse(diffuseColor, roughness, NdotV, NdotL, VdotH);
    }

    /// Specular BRDF
    float3 CookTorranceBRDF(in float D, in float3 F, in float G, in float NdotL, in float NdotV)
    {
        return D * F * G / (4.0 *  max(NdotL * NdotV, M_EPSILON));
    }

    float3 SpecularBRDF(in float D, in float3 F, in float G, in float NdotL, in float NdotV)
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
    float3 SchlickFresnel(in float3 specular, in float VdotH)
    {
        return specular + (float3(1.0, 1.0, 1.0) - specular) * pow(1.0 - VdotH, 5.0);
    }

    /// Fresnel factor, spherical gaussian in Schlick approximation; https://seblagarde.wordpress.com/2012/06/03/spherical-gaussien-approximation-for-blinn-phong-phong-and-fresnel/
    float3 SchlickGaussianFresnel(in float3 specular, in float VdotH)
    {
        float sphericalGaussian = pow(2.0, (-5.55473 * VdotH - 6.98316) * VdotH);
        return specular + (float3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
    }

    float3 Fresnel(in float3 specular, in float VdotH)
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
        float a = roughness * roughness;
        float a2 = a*a;

        float Vis_SmithV = NdotV + sqrt(NdotV * (NdotV - NdotV * a2) + a2);
        float Vis_SmithL = NdotL + sqrt(NdotL * (NdotL - NdotL * a2) + a2);
        return rcp(Vis_SmithV * Vis_SmithL);
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
        const float k = roughness * roughness;
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

    float SmithGGXSchlickVisibility2(in float NdotL, in float NdotV, in float roughness)
    {
        const float rough = roughness + 1.0;
        const float a = rough * rough;
        const float k =  a / 8.0;
        return (SchlickG(NdotL, k) * SchlickG(NdotV, k));
    }

    float SchlickBeckmannVisibility(in float NdotL, in float NdotV, in float roughness)
    {
        const float a = roughness * roughness;
        const float k =  a * sqrt(2.0 / M_PI);
        return (SchlickG(NdotL, k) * SchlickG(NdotV, k));
    }

    float Visibility(in float NdotL, in float NdotV, in float roughness)
    {
        return SmithGGXVisibility2(NdotL, NdotV, roughness);
    }

    /// Normal Distributions

    float BlinnPhongDistribution(in float NdotH, in float roughness)
    {
        const float specPower = max((2.0 / (roughness * roughness)) - 2.0, 1e-4f); // Calculate specular power from roughness
        return pow(saturate(NdotH), specPower);
    }

    /// Beckmann normal distribution
    ///     NdotH: dot-prod of surface normal and half-angle
    ///     roughness: surface roughness
    float BeckmannDistribution(in float NdotH, in float roughness)
    {
        const float rough2 = roughness * roughness;
        const float roughnessA = 1.0 / (4.0 * rough2 * pow(NdotH, 4.0));
        const float roughnessB = NdotH * NdotH - 1.0;
        const float roughnessC = rough2 * NdotH * NdotH;
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
