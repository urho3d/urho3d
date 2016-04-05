#ifdef COMPILEPS
    #ifdef PBR
        float3 LinearToSRGB(float3 c)
        {
            return pow(c, 2.2);
        }

        float3 LinearFromSRGB(float3 c)
        {
            return pow(c, 1.0 / 2.2);
        }

        float3 OrenNayarDiffuse(in float3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
        {
            float rough2 = roughness * roughness;
            
            float vDotL = 2.0 * vDotH - 1.0;
            float majorCtrl = 1.0 - 0.5 * rough2 / (rough2 + 0.33);
            float cosRi = vDotL - nDotV * nDotL;
            float minorCtrl = 0.45 * rough2 / (rough2 + 0.09) * cosRi * (cosRi >= 0 ? min(1, nDotL / nDotV) : nDotL);
            return diffuseColor / 3.141596 * ( nDotL * majorCtrl + minorCtrl);
        }

        float3 LambertianDiffuse(in float3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
        {
            return diffuseColor * nDotL;
        }

        float3 BurleyDiffuse(in float3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
        {
            
            float energyBias = lerp(0, 0.5, roughness);
            float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);
            float fd90 = energyBias + 2.0 * vDotH * vDotH * roughness;
            float f0 = 1.0;
            float lightScatter = f0 + (fd90 - f0) * pow(1.0f - nDotL, 5.0f);
            float viewScatter = f0 + (fd90 - f0) * pow(1.0f - nDotV, 5.0f);
            
            return diffuseColor * lightScatter * viewScatter * energyFactor;
        }
        
        /// Fresnel Terms
        float3 SchlickFresnel(in float3 specular, in float vDotH)
        {
            return specular + (float3(1.0, 1.0, 1.0) - specular) * pow(1.0 - vDotH, 5.0);
        }
        
        /// Fresnel factor, spherical gaussian in Schlick approximation; https://seblagarde.wordpress.com/2012/06/03/spherical-gaussien-approximation-for-blinn-phong-phong-and-fresnel/
        float3 SchlickGaussianFresnel(in float3 specular, in float vDotH)
        {
            float sphericalGaussian = pow(2, (-5.55473 * vDotH - 6.98316) * vDotH);
            return specular + (float3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
        }
        
        // Visibility terms
        float SmithGGXVisibility(in float nDotL, in float nDotV, in float roughness)
        {
            float a = roughness * roughness;
            float a2 = a*a;

            float Vis_SmithV = nDotV + sqrt(nDotV * (nDotV - nDotV * a2) + a2);
            float Vis_SmithL = nDotL + sqrt(nDotL * (nDotL - nDotL * a2) + a2);
            return rcp(Vis_SmithV * Vis_SmithL);
        }
        
        
        float SchlickG1(in float factor, in float rough2)
        {
            return 1.0 / (factor * (1.0 - rough2) + rough2);
        }
        
        float SchlickVisibility(float nDotL, float nDotV, float roughness)
        {
            const float rough2 = roughness * roughness;
            return (SchlickG1(nDotL, rough2) * SchlickG1(nDotV, rough2)) * 0.25; // divided by four
        }
        
        /// Normal Distributions    
        float BlinnPhongDistribution(in float nDotH, in float roughness)
        {
            const float specPower = max((2.0 / (roughness * roughness)) - 2.0, 1e-4f); // Calculate specular power from roughness
            return pow(saturate(nDotH), specPower);
        }
        
        float BeckmannDistribution(in float nDotH, in float roughness)
        {
            const float rough2 = roughness * roughness;
            const float roughnessA = 1.0 / (4.0 * rough2 * pow(nDotH, 4));
            const float roughnessB = nDotH * nDotH - 1.0;
            const float roughnessC = rough2 * nDotH * nDotH;
            return roughnessA * exp(roughnessB / roughnessC);
        }
        
        float GGXDistribution(in float nDotH, in float roughness)
        {
            float rough2 = roughness * roughness;
            float tmp = roughness / max(1e-8, nDotH * nDotH * (rough2 - 1.0) + 1.0);
            return tmp * tmp * 0.3141596;
        }
    #endif
#endif
