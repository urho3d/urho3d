#include "BRDF.hlsl"
#ifdef COMPILEPS

    float3 GetSpecularDominantDir(float3 normal, float3 reflection, float roughness)
    {
        const float smoothness = 1.0 - roughness;
        const float lerpFactor = smoothness * (sqrt(smoothness) + roughness);
        return lerp(normal, reflection, lerpFactor);
    }

    float3 SphereLight(float3 worldPos, float3 lightVec, float3 normal, float3 toCamera, float roughness, float3 specColor, float3 diffColor, out float ndl)
    {
        float specEnergy = 1.0f;

        float radius = cLightRad / 100;
        float rough2 = max(roughness, 0.08);
        rough2 *= rough2;

        float radius2           = radius * radius;
        float distToLightSqrd   = dot(lightVec,lightVec);
        float invDistToLight    = rsqrt(distToLightSqrd);
        float sinAlphaSqr       = saturate(radius2 / distToLightSqrd);
        float sinAlpha          = sqrt(sinAlphaSqr);

        ndl       = dot(normal, (lightVec * invDistToLight));

        if(ndl < sinAlpha)
        {
            ndl = max(ndl, -sinAlpha);
            ndl = ((sinAlpha + ndl) * (sinAlpha + ndl)) / (4 * sinAlpha);
        }

        float sphereAngle = saturate(radius * invDistToLight);
                            
        specEnergy = rough2 / (rough2 + 0.5f * sphereAngle);
        specEnergy *= specEnergy;                           

        float3 R = 2 * dot(toCamera, normal) * normal - toCamera;
        R = GetSpecularDominantDir(normal, R, roughness);

        // Find closest point on sphere to ray
        float3 closestPointOnRay = dot(lightVec, R) * R;
        float3 centerToRay = closestPointOnRay - lightVec;
        float invDistToRay = rsqrt(dot(centerToRay, centerToRay));
        float3 closestPointOnSphere = lightVec + centerToRay * saturate(radius * invDistToRay);

        lightVec = closestPointOnSphere;
        float3 L = normalize(lightVec);

        float3 h = normalize(toCamera + L);
        float hdn = saturate(dot(h, normal));
        float hdv = dot(h, toCamera);
        float ndv = saturate(dot(normal, toCamera));
        float hdl = saturate(dot(h, lightVec));

        const float3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, hdv)  * ndl;
        const float3 fresnelTerm = Fresnel(specColor, hdv, hdl) ;
        const float distTerm = Distribution(hdn, roughness);
        const float visTerm = Visibility(ndl, ndv, roughness);
        float3 specularFactor = distTerm * visTerm * fresnelTerm * ndl/ M_PI;
        return diffuseFactor + specularFactor;

    }

    float3 TubeLight(float3 worldPos, float3 lightVec, float3 normal, float3 toCamera, float roughness, float3 specColor, float3 diffColor, out float ndl)
    {
        float radius      = cLightRad / 100;
        float len         = cLightLength / 10; 
        float3 pos         = (cLightPosPS.xyz - worldPos);
        float3 reflectVec  = reflect(-toCamera, normal);
        
        float3 L01 = cLightDirPS * len;
        float3 L0 = pos - 0.5 * L01;
        float3 L1 = pos + 0.5 * L01;
        float3 ld = L1 - L0;

        float distL0    = length( L0 );
        float distL1    = length( L1 );

        float NoL0      = dot( L0, normal ) / ( 2.0 * distL0 );
        float NoL1      = dot( L1, normal ) / ( 2.0 * distL1 );
        ndl             = ( 2.0 * clamp( NoL0 + NoL1, 0.0, 1.0 ) ) 
                        / ( distL0 * distL1 + dot( L0, L1 ) + 2.0 );
    
        float a = len * len;
        float b = dot( reflectVec, L01 );
        float t = saturate( dot( L0, b * reflectVec - L01 ) / (a - b*b) );
        
        float3 closestPoint   = L0 + ld * saturate( t);
        float3 centreToRay    = dot( closestPoint, reflectVec ) * reflectVec - closestPoint;
        closestPoint          = closestPoint + centreToRay * saturate(radius / length(centreToRay));

        float3 l = normalize(closestPoint);
        float3 h = normalize(toCamera + l);

        ndl       =  saturate(dot(normal, lightVec));
        float hdn = saturate(dot(h, normal));
        float hdv = dot(h, toCamera);
        float ndv = saturate(dot(normal, toCamera));
        float hdl = saturate(dot(h, lightVec));

        float distL      = length(closestPoint);
        float alpha      = max(roughness, 0.08) * max(roughness, 0.08);
        float alphaPrime = saturate(radius / (distL * 2.0) + alpha);

       const float3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, hdv)  * ndl;
       const float3 fresnelTerm = Fresnel(specColor, hdv, hdl) ;
       const float distTerm = Distribution(hdn, roughness);
       const float visTerm = Visibility(ndl, ndv, roughness);
       float3 specularFactor = distTerm * visTerm * fresnelTerm * ndl/ M_PI;
       return diffuseFactor + specularFactor;
    }

	//Return the PBR BRDF value
	// lightDir  = the vector to the light
	// lightVec  = normalised lightDir
	// toCamera  = vector to the camera
	// normal    = surface normal of the pixel
	// roughness = roughness of the pixel
	// diffColor = the rgb color of the pixel
	// specColor = the rgb specular color of the pixel
	float3 GetBRDF(float3 worldPos, float3 lightDir, float3 lightVec, float3 toCamera, float3 normal, float roughness, float3 diffColor, float3 specColor)
	{

        const float3 Hn = normalize(toCamera + lightDir);
        const float vdh = clamp((dot(toCamera, Hn)), M_EPSILON, 1.0);
        const float ndh = clamp((dot(normal, Hn)), M_EPSILON, 1.0);
        float ndl = clamp((dot(normal, lightVec)), M_EPSILON, 1.0);
        const float ndv = clamp((dot(normal, toCamera)), M_EPSILON, 1.0);
        const float ldh = clamp((dot(lightVec, Hn)), M_EPSILON, 1.0);

        const float3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, vdh)  * ndl;
        float3 specularFactor = 0;

        #ifdef SPECULAR
            if(cLightRad > 0.0)
            {
                if(cLightLength > 0.0)
                {
                    return TubeLight(worldPos, lightVec, normal, toCamera, roughness, specColor, diffColor, ndl);
                    
                }
                else
                {
                    return SphereLight(worldPos, lightVec, normal, toCamera, roughness, specColor, diffColor, ndl);
                }
            }
            else
            {
                const float3 fresnelTerm = Fresnel(specColor, vdh, ldh) ;
                const float distTerm = Distribution(ndh, roughness);
                const float visTerm = Visibility(ndl, ndv, roughness);
                specularFactor = distTerm * visTerm * fresnelTerm * ndl/ M_PI;
                return diffuseFactor + specularFactor;
            }

        #endif

        return diffuseFactor + specularFactor;
	}
#endif
