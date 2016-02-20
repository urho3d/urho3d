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
    float GetDiffuse(float3 normal, float3 worldPos, out float3 lightDir)
    {
        #ifdef DIRLIGHT
            lightDir = cLightDirPS;
            return saturate(dot(normal, lightDir));
        #else
            float3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
            float lightDist = length(lightVec);
            lightDir = lightVec / lightDist;
            return saturate(dot(normal, lightDir)) * Sample2D(LightRampMap, float2(lightDist, 0.0)).r;
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

    /// Diffuse factors

        float3 OrenNayarDiffuse(in float3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
        {
            const float rough2 = roughness * roughness;
            
            const float vDotL = 2.0 * vDotH - 1.0;
            const float majorCtrl = 1.0 - 0.5 * rough2 / (rough2 + 0.33);
            const float cosRi = vDotL - nDotV * nDotL;
            const float minorCtrl = 0.45 * rough2 / (rough2 + 0.09) * cosRi * (cosRi >= 0 ? min(1, nDotL / nDotV) : nDotL);
            return diffuseColor / 3.141596 * ( nDotL * majorCtrl + minorCtrl);
        }

        float3 LambertianDiffuse(in float3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float vDotH)
        {
            return diffuseColor * nDotL;
        }

		float3 BurleyDiffuse(in float3 diffuseColor, in float roughness, in float nDotV, in float nDotL, in float lDotH)
		{
			float energyBias = lerp(0, 0.5, roughness);
			float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);
			float fd90 = energyBias + 2.0 * lDotH * lDotH * roughness;
			float3 f0 = float3 (1.0f, 1.0f, 1.0f);
			float lightScatter = (f0 + (fd90 - f0) * pow(1.0f - nDotL, 5.0f)).r;
			float viewScatter = (f0 + (fd90 - f0) * pow(1.0f - nDotV, 5.0f)).r;
			
			return diffuseColor * lightScatter * viewScatter * energyFactor;
		}
        
    /// Fresnel Terms

        float3 SchlickFresnel(in float3 specular, in float vDotH)
        {
            return specular + (float3(1.0, 1.0, 1.0) - specular) * pow(1.0 - vDotH, 5.0);
        }
        
        /// Fresnel factor, spherical gaussian in Schlick approximation; https://seblagarde.wordpress.com/2012/06/03/spherical-gaussien-approximation-for-blinn-phong-phong-and-fresnel/
        float3 SchlickGaussianFresnel(in float3 specular, in float vDotH, in float roughness)
        {
            float specularPower = exp2(10 * (1 - roughness) + 1);
            float sphericalGaussian = pow(2, (-5.55473 * vDotH - 6.98316) * vDotH);
            return specular + (float3(1.0, 1.0, 1.0) - specular) * sphericalGaussian;
        }
        
    // Visibility terms

        /// Smith GGX Visibility
        ///     nDotL: dot-prod of surface normal and light direction
        ///     nDotV: dot-prod of surface normal and view direction
        ///     roughness: surface roughness
        float SmithGGXVisibility(in float nDotL, in float nDotV, in float roughness)
        {
			float a = roughness * roughness;
			float a2 = a*a;

			float Vis_SmithV = nDotV + sqrt(nDotV * (nDotV - nDotV * a2) + a2);
			float Vis_SmithL = nDotL + sqrt(nDotL * (nDotL - nDotL * a2) + a2);
			return rcp(Vis_SmithV * Vis_SmithL);
        }
        
        
        float SchlickG1(in float factor, in float rough2)
        {
            return 1.0 / (factor * (1.0 - rough2) + rough2);
        }
        
        /// Schlick approximation of Smith GGX
        ///     nDotL: dot product of surface normal and light direction
        ///     nDotV: dot product of surface normal and view direction
        ///     roughness: surface roughness
        float SchlickVisibility(float nDotL, float nDotV, float roughness)
        {
            const float rough2 = roughness * roughness;
            return (SchlickG1(nDotL, rough2) * SchlickG1(nDotV, rough2)) * 0.25; // divided by four
        }
        
    /// Normal Distributions
        
        float BlinnPhongDistribution(in float nDotH, in float roughness)
        {
            const float specPower = max((2.0 / (roughness * roughness)) - 2.0, 1e-4f); // Calculate specular power from roughness
            return pow(saturate(nDotH), specPower);
        }
        
        /// Beckmann normal distribution
        ///     nDotH: dot-prod of surface normal and half-angle
        ///     roughness: surface roughness
        float BeckmannDistribution(in float nDotH, in float roughness)
        {
            const float rough2 = roughness * roughness;
            const float roughnessA = 1.0 / (4.0 * rough2 * pow(nDotH, 4));
            const float roughnessB = nDotH * nDotH - 1.0;
            const float roughnessC = rough2 * nDotH * nDotH;
            return roughnessA * exp(roughnessB / roughnessC);
        }
        
        /// Trowbridge-Reitz GGX normal distribution
        ///     nDotH: dot-prod of surface normal and half-angle
        ///     roughness: surface roughness
        float GGXDistribution(in float nDotH, in float roughness)
        {
			float m = roughness * roughness;
			float m2 = m * m;
			float d = (nDotH * m2 - nDotH) * nDotH + 1; // 2 mad
			return m2 / (3.141596*d*d);
        }
        
    /// Functions
        
        #ifdef IBL      /// Image based lighting shading

		float radicalInverse_VdC(uint bits)
		{
			bits = (bits << 16u) | (bits >> 16u);
			bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
			bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
			bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
			bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);

			return float(bits) * 2.3283064365386963e-10; // / 0x100000000
		}

		float2 Hammersley(uint i, uint n)
		{
			return float2((float)i / (float)n, radicalInverse_VdC(i));
		}

		float3 ImportanceSampleGGX(float2 Xi, float Roughness, float3 N)
		{
			float a = Roughness * Roughness;
			float Phi = 2 * 3.14159 * Xi.x;
			float CosTheta = sqrt((1 - Xi.y) / (1 + (a*a - 1) * Xi.y));
			float SinTheta = sqrt(1 - CosTheta * CosTheta);
			float3 H = 0;
			H.x = SinTheta * cos(Phi);
			H.y = SinTheta * sin(Phi);
			H.z = CosTheta;

			float3 UpVector = abs(N.z) < 0.999 ? float3(0, 0, 1) : float3(1, 0, 0);
			float3 TangentX = normalize(cross(UpVector, N));
			float3 TangentY = cross(N, TangentX);
			// Tangent to world space
			return TangentX * H.x + TangentY * H.y + N * H.z;


		}

		float GGX(float nDotV, float a)
		{
			float aa = a*a;
			float oneMinusAa = 1 - aa;
			float nDotV2 = 2 * nDotV;
			float root = aa + oneMinusAa * nDotV * nDotV;
			return nDotV2 / (nDotV + sqrt(root));
		}

		float G_Smith(float a, float nDotV, float nDotL)
		{

			return GGX(nDotL, a * a) * GGX(nDotV, a * a);
		}

		float2 IntegrateBRDF(float Roughness, float NoV)
		{
			float3 V;
			V.x = sqrt(1.0f - NoV * NoV); // sin
			V.y = 0;
			V.z = NoV;
			// cos
			float A = 0;
			float B = 0;

			const uint NumSamples = 128;

			for (uint i = 0; i < NumSamples; i++)
			{
				float2 Xi = Hammersley(i, NumSamples);
				float3 H = ImportanceSampleGGX(Xi, Roughness, float3(0.0, 0.0, 1.0));
				float3 L = 2 * dot(V, H) * H - V;
				float NoL = saturate(L.z);
				float NoH = saturate(H.z);
				float VoH = saturate(dot(V, H));
				if (NoL > 0)
				{
					float G = G_Smith(Roughness, NoV, NoL);
					float G_Vis = G * VoH / (NoH * NoV);
					float Fc = pow(1 - VoH, 5);
					A += (1 - Fc) * G_Vis;
					B += Fc * G_Vis;
				}
			}
			return float2(A, B) / NumSamples;
		}

		float3 PrefilterEnvMap(float Roughness, float3 R)
		{
			float3 N = R;
			float3 V = R;

			float3 PrefilteredColor = 0;
			const uint NumSamples = 128;

			float TotalWeight = 0;

			for (uint i = 0; i < NumSamples; i++)
			{
				float2 Xi = Hammersley(i, NumSamples);
				float3 H = ImportanceSampleGGX(Xi, Roughness, N);
				float3 L = 2 * dot(V, H) * H - V;
				float NoL = saturate(dot(N, L));
				if (NoL > 0)
				{
					PrefilteredColor += SampleCubeLOD(ZoneCubeMap, float4(L, Roughness * 9)).rgb * NoL;
					TotalWeight += NoL;
				}
			}
			return PrefilteredColor / TotalWeight;
		}

		float3 ApproximateSpecularIBL(float3 SpecularColor, float Roughness, float3 N, float3 V)
		{
			float NoV = saturate(dot(N, V));
			float3 R = 2 * dot(V, N) * N - V;
			float3 PrefilteredColor = PrefilterEnvMap(Roughness, R);
			float2 envBRDF = IntegrateBRDF(Roughness, NoV);
			return   PrefilteredColor * (SpecularColor * envBRDF.x + envBRDF.y);
		}


        #endif

    #endif

#endif