#line 20001
#ifdef COMPILEPS
  #ifdef PBR
    // Following BRDF methods are based upon research Frostbite EA
    //[Lagrade et al. 2014, "Moving Frostbite to Physically Based Rendering"]
    
    //Schlick Fresnel
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    vec3 SchlickFresnel(vec3 specular, float VdotH)
    {
        return specular + (vec3(1.0, 1.0, 1.0) - specular) * pow(1.0 - VdotH, 5.0);
    }

    //Get Fresnel
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    vec3 Fresnel(vec3 specular, float VdotH)
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
    vec3 LambertianDiffuse(vec3 diffuseColor, float NdotL)
    {
        return diffuseColor * NdotL;
    }

    // Burley Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    vec3 BurleyDiffuse(vec3 diffuseColor, float roughness, float NdotV, float NdotL, float VdotH)
    {
        float energyBias = mix(roughness, 0, 0.5);
        float energyFactor = mix(roughness, 1.0, 1.0 / 1.51);
        float fd90 = energyBias + 2.0 * VdotH * VdotH * roughness;
        float f0 = 1.0;
        float lightScatter = f0 + (fd90 - f0) * pow(1.0f - NdotL, 5.0f);
        float viewScatter = f0 + (fd90 - f0) * pow(1.0f - NdotV, 5.0f);

        return diffuseColor * lightScatter * viewScatter * energyFactor;
    }

    //Get Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    vec3 Diffuse(vec3 diffuseColor, float roughness, float NdotV, float NdotL, float VdotH)
    {
        //return LambertianDiffuse(diffuseColor, NdotL);
        return BurleyDiffuse(diffuseColor, roughness, NdotV, NdotL, VdotH);
    }

  #endif
#endif
