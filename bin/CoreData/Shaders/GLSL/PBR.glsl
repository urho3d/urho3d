#include "BRDF.glsl"
#ifdef COMPILEPS

	//Return the PBR BRDF value
	// lightDir  = the vector to the light
	// lightVev  = normalised lightDir
	// toCamera  = vector to the camera
	// normal    = surface normal of the pixel
	// roughness = roughness of the pixel
	// diffColor = the rgb color of the pixel
	// specColor = the rgb specular color of the pixel
	vec3 GetBRDF(vec3 lightDir, vec3 lightVec, vec3 toCamera, vec3 normal, float roughness, vec3 diffColor, vec3 specColor)
	{
        vec3 Hn = normalize(toCamera + lightDir);
        float vdh = clamp((dot(toCamera, Hn)), M_EPSILON, 1.0);
        float ndh = clamp((dot(normal, Hn)), M_EPSILON, 1.0);
        float ndl = clamp((dot(normal, lightVec)), M_EPSILON, 1.0);
        float ndv = clamp((dot(normal, toCamera)), M_EPSILON, 1.0);

        vec3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, vdh);
        vec3 specularFactor = vec3(0.0, 0.0, 0.0);

        #ifdef SPECULAR
            vec3 fresnelTerm = Fresnel(specColor, vdh) ;
            float distTerm = Distribution(ndh, roughness);
            float visTerm = Visibility(ndl, ndv, roughness);

            specularFactor = fresnelTerm * distTerm * visTerm  / M_PI;
        #endif

        return diffuseFactor + specularFactor;
	}
#endif
