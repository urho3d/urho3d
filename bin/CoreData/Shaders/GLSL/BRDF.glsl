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

    //Schlick Gaussian Fresnel
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    vec3 SchlickGaussianFresnel(in vec3 specular, in float VdotH)
    {
        float sphericalGaussian = pow(2.0, (-5.55473 * VdotH - 6.98316) * VdotH);
        return specular + (vec3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
    }

    vec3 SchlickFresnelCustom(vec3 specular, float LdotH)
    {
        float ior = 0.25;
        float airIor = 1.000277;
        float f0 = (ior - airIor) / (ior + airIor);
        float max_ior = 2.5;
        f0 = clamp(f0 * f0, 0.0, (max_ior - airIor) / (max_ior + airIor));
        return specular * (f0   + (1.0 - f0) * pow(2.0, (-5.55473 * LdotH - 6.98316) * LdotH));
    }

    //Get Fresnel
    //specular  = the rgb specular color value of the pixel
    //VdotH     = the dot product of the camera view direction and the half vector 
    vec3 Fresnel(vec3 specular, float VdotH, float LdotH)
    {
        return SchlickFresnelCustom(specular, LdotH);
        //return SchlickFresnel(specular, VdotH);
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

    float NeumannVisibility(float NdotV, float NdotL) 
    {
        return NdotL * NdotV / max(1e-7, max(NdotL, NdotV));
    }

    // Get Visibility
    // NdotL        = the dot product of the normal and direction to the light
    // NdotV        = the dot product of the normal and the camera view direction
    // roughness    = the roughness of the pixel
    float Visibility(float NdotL, float NdotV, float roughness)
    {
        return NeumannVisibility(NdotV, NdotL);
        //return SmithGGXSchlickVisibility(NdotL, NdotV, roughness);
    }

    // Blinn Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float BlinnPhongDistribution(in float NdotH, in float roughness)
    {
        float specPower = max((2.0 / (roughness * roughness)) - 2.0, 1e-4); // Calculate specular power from roughness
        return pow(clamp(NdotH, 0.0, 1.0), specPower);
    }

    // Beckmann Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float BeckmannDistribution(in float NdotH, in float roughness)
    {
        float rough2 = roughness * roughness;
        float roughnessA = 1.0 / (4.0 * rough2 * pow(NdotH, 4.0));
        float roughnessB = NdotH * NdotH - 1.0;
        float roughnessC = rough2 * NdotH * NdotH;
        return roughnessA * exp(roughnessB / roughnessC);
    }

    // GGX Distribution
    // NdotH        = the dot product of the normal and the half vector
    // roughness    = the roughness of the pixel
    float GGXDistribution(float NdotH, float roughness)
    {
        float rough2 = roughness * roughness;
        float tmp =  (NdotH * rough2 - NdotH) * NdotH + 1.0;
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
    vec3 LambertianDiffuse(vec3 diffuseColor)
    {
        return diffuseColor * (1.0 / M_PI) ;
    }

    // Custom Lambertian Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    vec3 CustomLambertianDiffuse(vec3 diffuseColor, float NdotV, float roughness)
    {
        return diffuseColor * (1.0 / M_PI) * pow(NdotV, 0.5 + 0.3 * roughness);
    }

    // Burley Diffuse
    // diffuseColor = the rgb color value of the pixel
    // roughness    = the roughness of the pixel
    // NdotV        = the normal dot with the camera view direction
    // NdotL        = the normal dot with the light direction
    // VdotH        = the camera view direction dot with the half vector
    vec3 BurleyDiffuse(vec3 diffuseColor, float roughness, float NdotV, float NdotL, float VdotH)
    {
        float energyBias = mix(roughness, 0.0, 0.5);
        float energyFactor = mix(roughness, 1.0, 1.0 / 1.51);
        float fd90 = energyBias + 2.0 * VdotH * VdotH * roughness;
        float f0 = 1.0;
        float lightScatter = f0 + (fd90 - f0) * pow(1.0 - NdotL, 5.0);
        float viewScatter = f0 + (fd90 - f0) * pow(1.0 - NdotV, 5.0);

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
        //return LambertianDiffuse(diffuseColor);
        return CustomLambertianDiffuse(diffuseColor, NdotV, roughness);
        //return BurleyDiffuse(diffuseColor, roughness, NdotV, NdotL, VdotH);
    }

  #endif
#endif
