#include "BRDF.hlsl"
#ifdef COMPILEPS

	//Return the PBR BRDF value
	// lightDir  = the vector to the light
	// lightVev  = normalised lightDir
	// toCamera  = vector to the camera
	// normal    = surface normal of the pixel
	// roughness = roughness of the pixel
	// diffColor = the rgb color of the pixel
	// specColor = the rgb specular color of the pixel
	float3 GetBRDF(float3 lightDir, float3 lightVec, float3 toCamera, float3 normal, float roughness, float3 diffColor, float3 specColor)
	{

        const float3 Hn = normalize(toCamera + lightDir);
        const float vdh = clamp((dot(toCamera, Hn)), M_EPSILON, 1.0);
        const float ndh = clamp((dot(normal, Hn)), M_EPSILON, 1.0);
        const float ndl = clamp((dot(normal, lightVec)), M_EPSILON, 1.0);
        const float ndv = clamp((dot(normal, toCamera)), M_EPSILON, 1.0);

        const float3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, vdh);
        float3 specularFactor = 0;

        #ifdef SPECULAR
            const float3 fresnelTerm = Fresnel(specColor, vdh) ;
            const float distTerm = Distribution(ndh, roughness);
            const float visTerm = Visibility(ndl, ndv, roughness);

            specularFactor = distTerm * visTerm * fresnelTerm / M_PI;
        #endif

        return diffuseFactor + specularFactor;
	}
#endif
