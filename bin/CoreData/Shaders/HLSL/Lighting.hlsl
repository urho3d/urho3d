#pragma warning(disable:3571)

#if defined(COMPILEVS) || defined(COMPILEGS)
    float3 GetAmbient(float zonePos)
    {
        return cAmbientStartColor + zonePos * cAmbientEndColor;
    }

    #ifdef NUMVERTEXLIGHTS
        float GetVertexLight(int index, float3 worldPos, float3 normal)
        {
            float3 lightDir = cVertexLights[index * 3 + 1].xyz;
            float3 lightPos = cVertexLights[index * 3 + 2].xyz;
            float invRange = cVertexLights[index * 3].w;
            float cutoff = cVertexLights[index * 3 + 1].w;
            float invCutoff = cVertexLights[index * 3 + 2].w;

            // Directional light
            if (invRange == 0.0)
            {
                float NdotL = max(dot(normal, lightDir), 0.0);
                return NdotL;
            }
            // Point/spot light
            else
            {
                float3 lightVec = (lightPos - worldPos) * invRange;
                float lightDist = length(lightVec);
                float3 localDir = lightVec / lightDist;
                float NdotL = max(dot(normal, localDir), 0.0);
                float atten = saturate(1.0 - lightDist * lightDist);
                float spotEffect = dot(localDir, lightDir);
                float spotAtten = saturate((spotEffect - cutoff) * invCutoff);
                return NdotL * atten * spotAtten;
            }
        }

        float GetVertexLightVolumetric(int index, float3 worldPos)
        {
            float3 lightDir = cVertexLights[index * 3 + 1].xyz;
            float3 lightPos = cVertexLights[index * 3 + 2].xyz;
            float invRange = cVertexLights[index * 3].w;
            float cutoff = cVertexLights[index * 3 + 1].w;
            float invCutoff = cVertexLights[index * 3 + 2].w;

            // Directional light
            if (invRange == 0.0)
            {
                return 1.0;
            }
            // Point/spot light
            else
            {
                float3 lightVec = (lightPos - worldPos) * invRange;
                float lightDist = length(lightVec);
                float3 localDir = lightVec / lightDist;
                float atten = saturate(1.0 - lightDist * lightDist);
                float spotEffect = dot(localDir, lightDir);
                float spotAtten = saturate((spotEffect - cutoff) * invCutoff);
                return atten * spotAtten;
            }
        }
    #endif

    #ifdef SHADOW

        #ifdef DIRLIGHT
            #define NUMCASCADES 4
        #else
            #define NUMCASCADES 1
        #endif

        void GetShadowPos(float4 projWorldPos, out float4 shadowPos[NUMCASCADES])
        {
            // Shadow projection: transform from world space to shadow space
            #if defined(DIRLIGHT)
                shadowPos[0] = mul(projWorldPos, cLightMatrices[0]);
                shadowPos[1] = mul(projWorldPos, cLightMatrices[1]);
                shadowPos[2] = mul(projWorldPos, cLightMatrices[2]);
                shadowPos[3] = mul(projWorldPos, cLightMatrices[3]);
            #elif defined(SPOTLIGHT)
                shadowPos[0] = mul(projWorldPos, cLightMatrices[1]);
            #else
                shadowPos[0] = float4(projWorldPos.xyz - cLightPos.xyz, 0.0);
            #endif
        }
    #endif
#endif

#ifdef COMPILEPS
    /// Based on http://www.frostbite.com/wp-content/uploads/2014/11/course_notes_moving_frostbite_to_pbr.pdf
    float smoothDistanceAtt(float squaredDistance, float invSqrAtt)
    {
        float factor = squaredDistance * invSqrAtt;
        float smoothFactor = saturate(1.0f - factor * factor);
        return pow(smoothFactor, 2);
    }

    float getDistanceAtt(float3 lightVec, float invSqrAtt)
    {
        float sqrDist = sqrt(dot(lightVec, lightVec));
        float attenuation = 1.0 / (max(sqrDist, 0.01));
        attenuation *= smoothDistanceAtt(sqrDist, invSqrAtt);

        return attenuation;
    }

    float getAngleAtt(float3 lightVec, float3 lightDir, float lightAngleScale, float lightAngleOffset)
    {
        float cd = dot(lightDir, lightVec);
        float attenuation = clamp(cd * lightAngleScale + lightAngleOffset, 0.0, 1.0);
        attenuation *= attenuation;

        return attenuation;
    }

    float GetDiffuse(float3 normal, float3 worldPos, out float3 lightDir)
    {
        #ifdef DIRLIGHT
            lightDir = cLightDirPS;
            return saturate(dot(normal, lightDir));
        #else
            float3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
            float lightDist = length(lightVec);
            lightDir = lightVec / lightDist;

            #ifdef PBR
                float3 L = normalize(lightVec);

                float att = 1;

                float invSqrLightDist = rsqrt(length(lightVec));
                att *= getDistanceAtt(lightVec, invSqrLightDist);
                att *= getAngleAtt(L, lightVec, 1.0 / 0.001f, -0);

                return saturate(dot(normal, lightDir)) * Sample2D(LightRampMap, float2(lightDist, 0.0)).r;
            #else
                return saturate(dot(normal, lightDir)) * Sample2D(LightRampMap, float2(lightDist, 0.0)).r;
            #endif
        #endif
    }

    float GetDiffuseVolumetric(float3 worldPos)
    {
        #ifdef DIRLIGHT
            return 1.0;
        #else
            float3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
            float lightDist = length(lightVec);
            return Sample2D(LightRampMap, float2(lightDist, 0.0)).r;
        #endif
    }

    float GetSpecular(float3 normal, float3 eyeVec, float3 lightDir, float specularPower)
    {
        float3 halfVec = normalize(normalize(eyeVec) + lightDir);
        return saturate(pow(dot(normal, halfVec), specularPower));
    }

    float GetIntensity(float3 color)
    {
        return dot(color, float3(0.299, 0.587, 0.114));
    }

    #ifdef SHADOW

        #ifdef DIRLIGHT
            #define NUMCASCADES 4
        #else
            #define NUMCASCADES 1
        #endif

        float GetShadow(float4 shadowPos)
        {
            #ifdef D3D11
                shadowPos.xyz /= shadowPos.w;
            #endif

            #ifndef LQSHADOW
                // Take four samples and average them
                // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
                #if !defined(POINTLIGHT) && !defined(D3D11)
                    float2 offsets = cShadowMapInvSize * shadowPos.w;
                #else
                    float2 offsets = cShadowMapInvSize;
                #endif
                float4 shadowPos2 = float4(shadowPos.x + offsets.x, shadowPos.yzw);
                float4 shadowPos3 = float4(shadowPos.x, shadowPos.y + offsets.y, shadowPos.zw);
                float4 shadowPos4 = float4(shadowPos.xy + offsets.xy, shadowPos.zw);

                float4 inLight = float4(
                    SampleShadow(ShadowMap, shadowPos).r,
                    SampleShadow(ShadowMap, shadowPos2).r,
                    SampleShadow(ShadowMap, shadowPos3).r,
                    SampleShadow(ShadowMap, shadowPos4).r
                );
                #ifndef SHADOWCMP
                    return cShadowIntensity.y + dot(inLight, cShadowIntensity.x);
                #else
                    #ifndef POINTLIGHT
                        return cShadowIntensity.y + dot(inLight * shadowPos.w > shadowPos.z, cShadowIntensity.x);
                    #else
                        return cShadowIntensity.y + dot(inLight > shadowPos.z, cShadowIntensity.x);
                    #endif
                #endif
            #else
                // Take one sample
                float inLight = SampleShadow(ShadowMap, shadowPos).r;
                #ifndef SHADOWCMP
                    return cShadowIntensity.y + cShadowIntensity.x * inLight;
                #else
                    #ifndef POINTLIGHT
                        return cShadowIntensity.y + cShadowIntensity.x * (inLight * shadowPos.w > shadowPos.z);
                    #else
                        return cShadowIntensity.y + cShadowIntensity.x * (inLight > shadowPos.z);
                    #endif
                #endif
            #endif
        }

        #ifdef POINTLIGHT
            float GetPointShadow(float3 lightVec)
            {
                float3 axis = SampleCube(FaceSelectCubeMap, lightVec).rgb;
                float depth = abs(dot(lightVec, axis));

                // Expand the maximum component of the light vector to get full 0.0 - 1.0 UV range from the cube map,
                // and to avoid sampling across faces. Some GPU's filter across faces, while others do not, and in this
                // case filtering across faces is wrong
                const float factor = 1.0 / 256.0;
                lightVec += factor * axis * lightVec;

                // Read the 2D UV coordinates, adjust according to shadow map size and add face offset
                float4 indirectPos = SampleCube(IndirectionCubeMap, lightVec);
                indirectPos.xy *= cShadowCubeAdjust.xy;
                indirectPos.xy += float2(cShadowCubeAdjust.z + indirectPos.z * 0.5, cShadowCubeAdjust.w + indirectPos.w);

                float4 shadowPos = float4(indirectPos.xy, cShadowDepthFade.x + cShadowDepthFade.y / depth, 1.0);
                return GetShadow(shadowPos);
            }
        #endif

        #ifdef DIRLIGHT
            float GetDirShadowFade(float inLight, float depth)
            {
                return saturate(inLight + saturate((depth - cShadowDepthFade.z) * cShadowDepthFade.w));
            }

            float GetDirShadow(const float4 iShadowPos[NUMCASCADES], float depth)
            {
                float4 shadowPos;

                if (depth < cShadowSplits.x)
                    shadowPos = iShadowPos[0];
                else if (depth < cShadowSplits.y)
                    shadowPos = iShadowPos[1];
                else if (depth < cShadowSplits.z)
                    shadowPos = iShadowPos[2];
                else
                    shadowPos = iShadowPos[3];

                return GetDirShadowFade(GetShadow(shadowPos), depth);
            }

            float GetDirShadowDeferred(float4 projWorldPos, float depth)
            {
                float4 shadowPos;
				 
                if (depth < cShadowSplits.x)
                    shadowPos = mul(projWorldPos, cLightMatricesPS[0]);
                else if (depth < cShadowSplits.y)
                    shadowPos = mul(projWorldPos, cLightMatricesPS[1]);
                else if (depth < cShadowSplits.z)
                    shadowPos = mul(projWorldPos, cLightMatricesPS[2]);
                else
                    shadowPos = mul(projWorldPos, cLightMatricesPS[3]);

                return GetDirShadowFade(GetShadow(shadowPos), depth);
            }
        #endif

        float GetShadow(float4 iShadowPos[NUMCASCADES], float depth)
        {
            #if defined(DIRLIGHT)
                return GetDirShadow(iShadowPos, depth);
            #elif defined(SPOTLIGHT)
                return GetShadow(iShadowPos[0]);
            #else
                return GetPointShadow(iShadowPos[0].xyz);
            #endif
        }

        float GetShadowDeferred(float4 projWorldPos, float depth)
        {
            #if defined(DIRLIGHT)
                return GetDirShadowDeferred(projWorldPos, depth);
            #elif defined(SPOTLIGHT)
                float4 shadowPos = mul(projWorldPos, cLightMatricesPS[1]);
                return GetShadow(shadowPos);
            #else
                float3 shadowPos = projWorldPos.xyz - cLightPosPS.xyz;
                return GetPointShadow(shadowPos);
            #endif
        }
    #endif

    #ifdef PBR

        float3 LinearToSRGB(float3 c)
        {
            return pow(c, 2.2);
        }

        float3 LinearFromSRGB(float3 c)
        {
            return pow(c, 1.0 / 2.2);
        }


        float AreaLight(out float3 lightVec, float3 view, float3 normal, float3 sqrDist, float roughness) 
        {
           float3 LobeEnergy = 1;

           float3 m = roughness;
            
            float3 R = reflect( -view, normal );
            float InvDistToLight = rsqrt( dot( sqrDist, sqrDist ) );

            lightVec = sqrDist;

            // if(cLightLengthPS > 0)
            // {
            //     // float LineAngle = saturate( cLightLengthPS * InvDistToLight );
            //     // LobeEnergy *= m / saturate( m + 0.5 * LineAngle );

            //     // // Closest point on line segment to ray
            //     // float3 L01 = float3(0,0, cLightLengthPS) - cLightPosPS.w;
            //     // float3 L0 = cLightLengthPS - L01;
            //     // float3 L1 = cLightLengthPS + L01;

            //     // float distL0 = length(L0);
            //     // float distL1 = length(L1);

            //     // float3 Ld = L1 - L0;
            //     // float L0dotLd = dot(L0, Ld);
            //     // float RdotL0 = dot(R, L0);
            //     // float RdotLd = dot(R, Ld);
            //     // float distLd = length(Ld);
            //     // float t = (RdotL0 * RdotLd - L0dotLd) / (distLd * distLd - RdotLd * RdotLd);

            //     // float3 closestPoint = L0 + Ld * saturate(t);
            //     // float3 centerToRay = dot(closestPoint, R) * R - closestPoint;
            //     // closestPoint = closestPoint + centerToRay * saturate(cLightLengthPS / length(centerToRay));
            //     // lightVec = normalize(closestPoint);
            //     // L = normalize(closestPoint);    
            //     // lightDistance = length(closestPoint);

            //     // // Calculate normalization factor for area light
            //     // LobeEnergy = saturate(cLightLengthPS / (lightDistance * 2.0f) + roughness);

            // }

            // if(cLightWidthPS > 0)
            // {
            //     // float SphereAngle = saturate( cLightWidthPS * InvDistToLight );
            //     // LobeEnergy *= ( m / saturate( m + 0.5 * SphereAngle ) ) * ( m / saturate( m + 0.5 * SphereAngle ) );

            //     // float3 ClosestPointOnRay = dot( lightVec, R ) * R  - lightVec;
            //     // float3 ClosestPointOnSphere = lightVec + ClosestPointOnRay * saturate( cLightWidthPS * rsqrt( dot( ClosestPointOnRay, ClosestPointOnRay ) ) );
            //     // lightVec = ClosestPointOnSphere;

            //     // lightVec = normalize(lightVec);
            
            //     // return LobeEnergy;
            // }
            
            return LobeEnergy;
        }
    #endif

#endif