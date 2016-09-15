#include "BRDF.hlsl"
#ifdef COMPILEPS

    #define LightRad 0.3
    #define LightLengh 1

    float3 SphereLight(float3 worldPos, float3 lightVec, float3 normal, float3 toCamera, float roughness, float3 specColor, out float ndl)
    {
        float3 pos   = (cLightPosPS.xyz - worldPos);
        float radius = LightRad;

        float3 reflectVec  = reflect(-toCamera, normal);
        float3 centreToRay = dot(pos, reflectVec) * reflectVec - pos;
        float3 closestPoint = pos + centreToRay * saturate(radius / length(centreToRay));

        float3 l = normalize(closestPoint);
        float3 h = normalize(toCamera + l);

        ndl       = saturate(dot(normal, l));
        float hdn = saturate(dot(h, normal));
        float hdv = dot(h, toCamera);
        float ndv = saturate(dot(normal, toCamera));

        float distL      = length(pos);
        float alpha      = roughness * roughness;
        float alphaPrime = saturate(radius / (distL * 2.0) + alpha);

        const float3 fresnelTerm = Fresnel(specColor, hdv) ;
        const float distTerm     = Distribution(hdn, alphaPrime);
        const float visTerm      = Visibility(ndl, ndv, roughness);

        return distTerm * visTerm * fresnelTerm ;
    }

    float3 TubeLight(float3 worldPos, float3 lightVec, float3 normal, float3 toCamera, float roughness, float3 specColor, out float ndl)
    {
        float3 pos   = (cLightPosPS.xyz - worldPos);
        float3 reflectVec  = reflect(-toCamera, normal);
        
        float3 tubeStart  = pos * (lightVec * LightLengh);
        float3 tubeEnd    = pos * (lightVec * LightLengh);
        float3 L0         = pos - 0.5 * tubeStart;
        float3 L1         = pos + 0.5 * tubeEnd;
        float distL0      = length( L0 );
        float distL1      = length( L1 );
        
        float NoL0      = dot( L0, normal ) / ( 2.0 * distL0 );
        float NoL1      = dot( L1, normal ) / ( 2.0 * distL1 );
        ndl             = ( 2.0 * saturate( NoL0 + NoL1) ) 
                        / ( distL0 * distL1 + dot( L0, L1 ) + 2.0 );
        
        float3 Ld         = L1 - L0;
        float RoL0        = dot( reflectVec, L0 );
        float RoLd        = dot( reflectVec, Ld );
        float L0oLd       = dot( L0, Ld );
        float distLd      = length( Ld );
        float t           = ( RoL0 * RoLd - L0oLd ) 
                          / ( distLd * distLd - RoLd * RoLd );
        
        float3 closestPoint   = L0 + Ld * saturate( t);
        float3 centerToRay    = dot( closestPoint, reflectVec ) * reflectVec - closestPoint;
        closestPoint          = closestPoint + centerToRay * saturate( LightRad / length( centerToRay ));
        float3 l              = normalize( closestPoint );
        float3 h              = normalize( toCamera + l );
        
        float HoN       = saturate( dot( h, normal ) );
        float HoV       = dot( h, toCamera );
        float ndv       = saturate(dot(normal, toCamera));
        
        float distLight     = length( closestPoint );
        float alpha         = roughness * roughness;
        float alphaPrime    = saturate( LightRad / ( distLight * 2.0 ) + alpha);

        const float3 fresnelTerm = Fresnel(specColor, HoV) ;
        const float distTerm     = Distribution(HoN, alphaPrime);
        const float visTerm      = Visibility(ndl, ndv, roughness);

        return distTerm * visTerm * fresnelTerm ;
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

        const float3 diffuseFactor = Diffuse(diffColor, roughness, ndv, ndl, vdh)  * ndl;
        float3 specularFactor = 0;

        #ifdef SPECULAR
            if(LightRad > 0.0)
            {
                if(LightLengh > 0.0)
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
                const float3 fresnelTerm = Fresnel(specColor, vdh) ;
                const float distTerm = Distribution(ndh, roughness);
                const float visTerm = Visibility(ndl, ndv, roughness);
                specularFactor = distTerm * visTerm * fresnelTerm * ndl/ M_PI;
            }

        #endif

        return diffuseFactor + specularFactor;
	}
#endif
