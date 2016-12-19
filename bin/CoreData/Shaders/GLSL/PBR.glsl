#include "BRDF.glsl"
#ifdef COMPILEPS

    vec3 SphereLight(vec3 worldPos, vec3 lightVec, vec3 normal, vec3 toCamera, float roughness, vec3 specColor, out float ndl)
    {
        vec3 pos   = (cLightPosPS.xyz - worldPos);
        float radius = cLightRad;

        vec3 reflectVec   = reflect(-toCamera, normal);
        vec3 centreToRay  = dot(pos, reflectVec) * reflectVec - pos;
        vec3 closestPoint = pos + centreToRay * clamp(radius / length(centreToRay), 0.0, 1.0);

        vec3 l = normalize(closestPoint);
        vec3 h = normalize(toCamera + l);

        ndl       = clamp(dot(normal, l), 0.0, 1.0);
        float hdn = clamp(dot(h, normal), 0.0, 1.0);
        float hdv = dot(h, toCamera);
        float ndv = clamp(dot(normal, toCamera), 0.0, 1.0);

        float distL      = length(pos);
        float alpha      = roughness * roughness;
        float alphaPrime = clamp(radius / (distL * 2.0) + alpha, 0.0, 1.0);

        vec3 fresnelTerm = Fresnel(specColor, hdv) ;
        float distTerm     = Distribution(hdn, alphaPrime);
        float visTerm      = Visibility(ndl, ndv, roughness);

        return distTerm * visTerm * fresnelTerm ;
    }

    vec3 TubeLight(vec3 worldPos, vec3 lightVec, vec3 normal, vec3 toCamera, float roughness, vec3 specColor, out float ndl)
    {
        float radius      = cLightRad;
        float len         = cLightLength; 
        vec3 pos         = (cLightPosPS.xyz - worldPos);
        vec3 reflectVec  = reflect(-toCamera, normal);
        
        vec3 L01 = cLightDirPS * len;
        vec3 L0 = pos - 0.5 * L01;
        vec3 L1 = pos + 0.5 * L01;
        vec3 ld = L1 - L0;

        float distL0    = length( L0 );
        float distL1    = length( L1 );

        float NoL0      = dot( L0, normal ) / ( 2.0 * distL0 );
        float NoL1      = dot( L1, normal ) / ( 2.0 * distL1 );
        ndl             = ( 2.0 * clamp( NoL0 + NoL1, 0.0, 1.0 ) ) 
                        / ( distL0 * distL1 + dot( L0, L1 ) + 2.0 );
    
        float a = len * len;
        float b = dot( reflectVec, L01 );
        float t = clamp( dot( L0, b * reflectVec - L01 ) / (a - b*b), 0.0, 1.0 );
        
        vec3 closestPoint   = L0 + ld * clamp(t, 0.0, 1.0);
        vec3 centreToRay    = dot( closestPoint, reflectVec ) * reflectVec - closestPoint;
        closestPoint          = closestPoint + centreToRay * clamp(radius / length(centreToRay), 0.0, 1.0);

        vec3 l = normalize(closestPoint);
        vec3 h = normalize(toCamera + l);

        ndl       =  clamp(dot(normal, lightVec), 0.0, 1.0);
        float hdn = clamp(dot(h, normal), 0.0, 1.0);
        float hdv = dot(h, toCamera);
        float ndv = clamp(dot(normal, toCamera), 0.0 ,1.0);

        float distL      = length(closestPoint);
        float alpha      = roughness * roughness;
        float alphaPrime = clamp(radius / (distL * 2.0) + alpha, 0.0, 1.0);

        vec3 fresnelTerm = Fresnel(specColor, hdv) ;
        float distTerm     = Distribution(hdn, alphaPrime);
        float visTerm      = Visibility(ndl, ndv, roughness);

        return distTerm * visTerm * fresnelTerm ;
    }

	//Return the PBR BRDF value
	// lightDir  = the vector to the light
	// lightVev  = normalised lightDir
	// toCamera  = vector to the camera
	// normal    = surface normal of the pixel
	// roughness = roughness of the pixel
	// diffColor = the rgb color of the pixel
	// specColor = the rgb specular color of the pixel
	vec3 GetBRDF(vec3 worldPos, vec3 lightDir, vec3 lightVec, vec3 toCamera, vec3 normal, float roughness, vec3 diffColor, vec3 specColor)
	{
        vec3 Hn = normalize(toCamera + lightDir);
        float vdh = clamp((dot(toCamera, Hn)), M_EPSILON, 1.0);
        float ndh = clamp((dot(normal, Hn)), M_EPSILON, 1.0);
        float ndl = clamp((dot(normal, lightVec)), M_EPSILON, 1.0);
        float ndv = clamp((dot(normal, toCamera)), M_EPSILON, 1.0);

        vec3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, vdh);
        vec3 specularFactor = vec3(0.0, 0.0, 0.0);

        #ifdef SPECULAR
            if(cLightRad > 0.0)
            {
                if(cLightLength > 0.0)
                {
                    specularFactor = TubeLight(worldPos, lightVec, normal, toCamera, roughness, specColor, ndl);
                    specularFactor *= ndl;
                }
                else
                {
                    specularFactor = SphereLight(worldPos, lightVec, normal, toCamera, roughness, specColor, ndl);
                    specularFactor *= ndl;
                }
            }
            else
            {
                vec3 fresnelTerm = Fresnel(specColor, vdh) ;
                float distTerm = Distribution(ndh, roughness);
                float visTerm = Visibility(ndl, ndv, roughness);

                specularFactor = fresnelTerm * distTerm * visTerm  / M_PI;
            }
        #endif

        return diffuseFactor + specularFactor;
	}
#endif
