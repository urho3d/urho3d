#ifdef COMPILEPS
  #ifdef PBR

    // Following BRDF methods are based upon research Frostbite EA
    //[Lagrade et al. 2014, "Moving Frostbite to Physically Based Rendering"]
    
    //Schlick Fresnel
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    float3 SchlickFresnel(float3 specular, float VdotH)
    {
        return specular + (float3(1.0, 1.0, 1.0) - specular) * pow(1.0 - VdotH, 5.0);
    }

    //Schlick Gaussian Fresnel 
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    float3 SchlickGaussianFresnel(in float3 specular, in float VdotH)
    {
        float sphericalGaussian = pow(2.0, (-5.55473 * VdotH - 6.98316) * VdotH);
        return specular + (float3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
    }

    //Get Fresnel
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    float3 Fresnel(float3 specular, float VdotH)
    {
        return SchlickFresnel(specular, VdotH);
    }

    // Smith GGX corrected Visibility
    // NdotL        = the dot product of the normal and direction to the light
    // NdotV        = the dot product of the normal and the camera view direction
    // roughness    = the roughness of the pixel
    float SmithGGXSchlickVisibility(float NdotL, float NdotV, float roughness)
    {
        float rough2 = roughness * roughness;
        float lambdaV = NdotL  * sqrt((-NdotV * rough2 + NdotV) * NdotV + rough2);   
        float lambdaL = NdotV  * sqrt((-NdotL * rough2 + NdotL) * NdotL + rough2);
    
        return 0.5 / (lambdaV + lambdaL);
    }

    // Get Visibility
    // NdotL        = the dot product of the normal and direction to the light
    // NdotV        = the dot product of the normal and the camera view direction
    // roughness    = the roughness of the pixel
    float Visibility(float NdotL, float NdotV, float roughness)
    {
        return SmithGGXSchlickVisibility(NdotL, NdotV, roughness);
    }

    // GGX Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float GGXDistribution(float NdotH, float roughness)
    {
        float rough2 = roughness * roughness;
        float tmp =  (NdotH * rough2 - NdotH) * NdotH + 1;
        return rough2 / (tmp * tmp);
    }

    // Blinn Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float BlinnPhongDistribution(in float NdotH, in float roughness)
    {
        const float specPower = max((2.0 / (roughness * roughness)) - 2.0, 1e-4f); // Calculate specular power from roughness
        return pow(saturate(NdotH), specPower);
    }

    // Beckmann Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float BeckmannDistribution(in float NdotH, in float roughness)
    {
        const float rough2 = roughness * roughness;
        const float roughnessA = 1.0 / (4.0 * rough2 * pow(NdotH, 4.0));
        const float roughnessB = NdotH * NdotH - 1.0;
        const float roughnessC = rough2 * NdotH * NdotH;
        return roughnessA * exp(roughnessB / roughnessC);
    }

    // Get Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float Distribution(float NdotH, float roughness)
    {
        return GGXDistribution(NdotH, roughness);
    }

    // Lambertian Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    float3 LambertianDiffuse(float3 diffuseColor, float NdotL)
    {
        return diffuseColor * NdotL;
    }

    // Burley Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    float3 BurleyDiffuse(float3 diffuseColor, float roughness, float NdotV, float NdotL, float VdotH)
    {
        const float energyBias = lerp(0, 0.5, roughness);
        const float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);
        const float fd90 = energyBias + 2.0 * VdotH * VdotH * roughness;
        const float f0 = 1.0;
        const float lightScatter = f0 + (fd90 - f0) * pow(1.0f - NdotL, 5.0f);
        const float viewScatter = f0 + (fd90 - f0) * pow(1.0f - NdotV, 5.0f);

        return diffuseColor * lightScatter * viewScatter * energyFactor;
    }

    //Get Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    float3 Diffuse(float3 diffuseColor, float roughness, float NdotV, float NdotL, float VdotH)
    {
        //return LambertianDiffuse(diffuseColor, NdotL);
        return BurleyDiffuse(diffuseColor, roughness, NdotV, NdotL, VdotH);
    }

  #endif
#endif
