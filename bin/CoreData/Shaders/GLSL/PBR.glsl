#include "BRDF.glsl"
#ifdef COMPILEPS
#line 100
    vec3 GetSpecularDominantDir(vec3 normal, vec3 reflection, float roughness)
    {
        float smoothness = 1.0 - roughness;
        float lerpFactor = smoothness * (sqrt(smoothness) + roughness);
        return mix(normal, reflection, lerpFactor);
    }

    vec3 SphereLight(vec3 worldPos, vec3 lightVec, vec3 normal, vec3 toCamera, float roughness, vec3 specColor, vec3 diffColor, out float ndl)
    {
        float specEnergy = 1.0f;

        float radius = cLightRad / 100;
        float rough2 = max(roughness, 0.08);
        rough2 *= rough2;

        float radius2           = radius * radius;
        float distToLightSqrd   = dot(lightVec,lightVec);
        float invDistToLight    = inversesqrt(distToLightSqrd);
        float sinAlphaSqr       = clamp(radius2 / distToLightSqrd, 0.0, 1.0);
        float sinAlpha          = sqrt(sinAlphaSqr);

        ndl       = dot(normal, (lightVec * invDistToLight));

        if(ndl < sinAlpha)
        {
            ndl = max(ndl, -sinAlpha);
            ndl = ((sinAlpha + ndl) * (sinAlpha + ndl)) / (4 * sinAlpha);
        }

        float sphereAngle = clamp(radius * invDistToLight, 0.0, 1.0);
                            
        specEnergy = rough2 / (rough2 + 0.5f * sphereAngle);
        specEnergy *= specEnergy;                           

        vec3 R = 2 * dot(toCamera, normal) * normal - toCamera;
        R = GetSpecularDominantDir(normal, R, roughness);

        // Find closest point on sphere to ray
        vec3 closestPointOnRay = dot(lightVec, R) * R;
        vec3 centerToRay = closestPointOnRay - lightVec;
        float invDistToRay = inversesqrt(dot(centerToRay, centerToRay));
        vec3 closestPointOnSphere = lightVec + centerToRay * clamp(radius * invDistToRay, 0.0, 1.0);

        lightVec = closestPointOnSphere;
        vec3 L = normalize(lightVec);

        vec3 h = normalize(toCamera + L);
        float hdn = clamp(dot(h, normal), 0.0, 1.0);
        float hdv = dot(h, toCamera);
        float ndv = clamp(dot(normal, toCamera),0.0, 1.0);
        float hdl = clamp(dot(h, lightVec), 0.0, 1.0);

        vec3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, hdv)  * ndl;
        vec3 fresnelTerm = Fresnel(specColor, hdv, hdl) ;
        float distTerm = Distribution(hdn, roughness);
        float visTerm = Visibility(ndl, ndv, roughness);
        vec3 specularFactor = distTerm * visTerm * fresnelTerm * ndl/ M_PI;
        return diffuseFactor + specularFactor;
    }

    vec3 TubeLight(vec3 worldPos, vec3 lightVec, vec3 normal, vec3 toCamera, float roughness, vec3 specColor, vec3 diffColor, out float ndl)
    {
        float radius      = cLightRad / 100;
        float len         = cLightLength / 10; 
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

        ndl       = clamp(dot(normal, lightVec), 0.0, 1.0);
        float hdn = clamp(dot(h, normal), 0.0, 1.0);
        float hdv = dot(h, toCamera);
        float ndv = clamp(dot(normal, toCamera), 0.0, 1.0);
        float hdl = clamp(dot(h, lightVec), 0.0, 1.0);

        float distL      = length(closestPoint);
        float alpha      = max(roughness, 0.08) * max(roughness, 0.08);
        float alphaPrime = clamp(radius / (distL * 2.0) + alpha, 0.0, 1.0);

        vec3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, hdv)  * ndl;
        vec3 fresnelTerm = Fresnel(specColor, hdv, hdl) ;
        float distTerm = Distribution(hdn, roughness);
        float visTerm = Visibility(ndl, ndv, roughness);
        vec3 specularFactor = distTerm * visTerm * fresnelTerm * ndl/ M_PI;
        return diffuseFactor + specularFactor;
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
        float vdh = clamp(dot(toCamera, Hn), M_EPSILON, 1.0);
        float ndh = clamp(dot(normal, Hn), M_EPSILON, 1.0);
        float ndl = clamp(dot(normal, lightVec), M_EPSILON, 1.0);
        float ldh = clamp(dot(lightVec, Hn), M_EPSILON, 1.0);
        float ndv = abs(dot(normal, toCamera)) + 1e-5;

        vec3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, vdh);
        vec3 specularFactor = vec3(0.0, 0.0, 0.0);

        #ifdef SPECULAR
            if(cLightRad > 0.0)
            {
                if(cLightLength > 0.0)
                {
                    specularFactor = TubeLight(worldPos, lightVec, normal, toCamera, roughness, specColor, diffColor, ndl);
                    specularFactor *= ndl;
                }
                else
                {
                    specularFactor = SphereLight(worldPos, lightVec, normal, toCamera, roughness, specColor, diffColor, ndl);
                    specularFactor *= ndl;
                }
            }
            else
            {
                vec3 fresnelTerm = Fresnel(specColor, vdh, ldh) ;
                float distTerm = Distribution(ndh, roughness);
                float visTerm = Visibility(ndl, ndv, roughness);

                specularFactor = fresnelTerm * distTerm * visTerm  / M_PI;
                return diffuseFactor + specularFactor;
            }
        #endif

        return diffuseFactor + specularFactor;
	}
#endif
