#pragma warning(disable:3571)

#ifdef COMPILEVS
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
        #ifdef TRANSLUCENT
            float NdotL = abs(dot(normal, lightDir));
        #else
            float NdotL = max(dot(normal, lightDir), 0.0);
        #endif
        return NdotL;
    }
    // Point/spot light
    else
    {
        float3 lightVec = (lightPos - worldPos) * invRange;
        float lightDist = length(lightVec);
        float3 localDir = lightVec / lightDist;
        #ifdef TRANSLUCENT
            float NdotL = abs(dot(normal, localDir));
        #else
            float NdotL = max(dot(normal, localDir), 0.0);
        #endif
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
        #ifdef TRANSLUCENT
            return abs(dot(normal, lightDir));
        #else
            return saturate(dot(normal, lightDir));
        #endif
    #else
        float3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
        float lightDist = length(lightVec);
        lightDir = lightVec / lightDist;
        #ifdef TRANSLUCENT
            return abs(dot(normal, lightDir)) * Sample2D(LightRampMap, float2(lightDist, 0.0)).r;
        #else
            return saturate(dot(normal, lightDir)) * Sample2D(LightRampMap, float2(lightDist, 0.0)).r;
        #endif
    #endif
}

float3 LinearToSRGB(float3 c)
{
	return pow(c, 2.2);
}

float3 LinearFromSRGB(float3 c)
{
	return pow(c, 1.0 / 2.2);
}

float3 GetLambertDiffuse(float3 diffuse)
{
	return diffuse * (1 / 3.141596);
}

float3 GetBurlyDiffuse(float3 diffuse, float roughness, float ndv, float NoL, float vdh)
{
	float FD90 = (0.5 + 2 * vdh * vdh) * roughness;
	float FdV = 1 + (FD90 - 1) * pow(1 - ndv, 5);
	float FdL = 1 + (FD90 - 1) * pow(1 - NoL, 5);
	return diffuse * (1 / 3.14159 * FdV * FdL) * (1 - 0.3333 * roughness);
}

float GetGGXDistrabution(float roughness, float ndh)
{
	float m = roughness * roughness;
	float m2 = m * m;
	float d = (ndh * m2 - ndh) * ndh + 1; // 2 mad
	return m2 / (3.141596*d*d);
}

float3 GetSchlickGaussianFresnel(float roughness, float3 specular, float vdh)
{
	float Fc = pow(1 - vdh, 5);
	return saturate(50.0 * specular.g) * Fc + (1 - Fc) * specular;
}

float GetSmithGGXVisability(float roughness, float ndl, float ndv)
{
	float a = roughness * roughness;
	float a2 = a*a;

	float Vis_SmithV = ndv + sqrt(ndv * (ndv - ndv * a2) + a2);
	float Vis_SmithL = ndl + sqrt(ndl * (ndl - ndl * a2) + a2);
	return rcp(Vis_SmithV * Vis_SmithL);
}


// Karis '13
float3 ImportanceSampleGGX(float2 Xi, float Roughness, float3 N)
{
	float a = Roughness * Roughness;
	float Phi = 2 * 3.141596 * Xi.x;
	float CosTheta = sqrt((1.0 - Xi.y) / (1 + (a*a - 1) * Xi.y));
	float SinTheta = sqrt(1.0 - CosTheta * CosTheta);

	float3 H;
	H.x = SinTheta * cos(Phi);
	H.y = SinTheta * sin(Phi);
	H.z = CosTheta;

	float3 UpVector = abs(N.z) < 0.999 ? float3(0, 0, 1) : float3(1, 0, 0);
	float3 TangentX = normalize(cross(UpVector, N));
	float3 TangentY = cross(N, TangentX);
	return TangentX * H.x + TangentY * H.y + N * H.z;
}


//////Testing

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
	return float2(i / n, radicalInverse_VdC(i));
}

float3 ImportanceSampleGGX2(float2 Xi, float Roughness, float3 N)
{
	float a = Roughness * Roughness;
	float Phi = 2 * 3.141596 * Xi.x;
	float CosTheta = sqrt((1 - Xi.y) / (1 + (a*a - 1) * Xi.y));
	float SinTheta = sqrt(1 - CosTheta * CosTheta);
	float3 H;
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

	return GGX(nDotL, a) * GGX(nDotV, a);
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
#if defined(PERPIXEL)
	const uint NumSamples = 16;
#else
	const uint NumSamples = 128;
#endif
	for (uint i = 0; i < NumSamples; i++)
	{
		float2 Xi = Hammersley(i, NumSamples);
		float3 H = ImportanceSampleGGX2(Xi, Roughness, float3(0.0,0.0,1.0));
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
#if defined(PERPIXEL)
	const uint NumSamples = 16;
#else
	const uint NumSamples = 128;
#endif
	float TotalWeight = 0;

	for (uint i = 0; i < NumSamples; i++)
	{
		float2 Xi = Hammersley(i, NumSamples);
		float3 H = ImportanceSampleGGX2(Xi, Roughness, N);
		float3 L = 2 * dot(V, H) * H - V;
		float NoL = saturate(dot(N, L));
		if (NoL > 0)
		{
			PrefilteredColor += SampleCubeLOD(ZoneCubeMap, float4(L, Roughness)).rgb * NoL;
			TotalWeight += NoL;
		}
	}
	return PrefilteredColor / TotalWeight;
}

float3 SpecularIBL(float3 SpecularColor, float Roughness, float3 N, float3 V)
{
	float3 SpecularLighting = 0;
#if defined(PERPIXEL)
	const uint NumSamples = 16;
#else
	const uint NumSamples = 128;
#endif
	for (uint i = 0; i < NumSamples; i++)
	{
		float2 Xi = Hammersley(i, NumSamples);
	
		float3 H = ImportanceSampleGGX(Xi, Roughness, N);
		float3 L = 2 * dot(V, H) * H - V;
		float NoV = saturate(dot(N, V));
		float NoL = saturate(dot(N, L));
		float NoH = saturate(dot(N, H));
		float VoH = saturate(dot(V, H));
		if (NoL > 0)
		{
			float3 SampleColor = SampleCubeLOD(ZoneCubeMap, float4(L, Roughness)).rgb;
			float G = G_Smith(Roughness, NoV, NoL);
			float Fc = pow(1 - VoH, 5);
			float3 F = (1 - Fc) * SpecularColor + Fc;
			// Incident light = SampleColor * NoL
			// Microfacet specular = D*G*F / (4*NoL*NoV)
			// pdf = D * NoH / (4 * VoH)
			SpecularLighting += SampleColor * F * G * VoH / (NoH * NoV);
		}
	}
	return SpecularLighting / NumSamples;
}


float3 ApproximateSpecularIBL(float3 SpecularColor, float Roughness, float3 N, float3 V)
{
	float NoV = saturate(dot(N, V));
	float3 R = 2 * dot(V, N) * N - V;
	//R.x = -R.x;
	//R.z = -R.z;
//#if defined(PERPIXEL)
//	float3 reflection = reflect(N, V);
//	return LinearToSRGB(ImageBasedLighting(reflection, N, V, SpecularColor, Roughness));
//#else
	float3 PrefilteredColor = PrefilterEnvMap(Roughness, R);
	float2 envBRDF = IntegrateBRDF(Roughness, NoV);
	float3 specIBL = SpecularIBL(SpecularColor, Roughness, N, V);
	return  PrefilteredColor * (specIBL * envBRDF.x + envBRDF.y);
//#endif
}

//////


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

#ifdef VSM_SHADOW
float ReduceLightBleeding(float min, float p_max)  
{  
    return clamp((p_max - min) / (1.0 - min), 0.0, 1.0);  
}

float Chebyshev(float2 Moments, float depth)  
{  
    //One-tailed inequality valid if depth > Moments.x  
    float p = float(depth <= Moments.x);  
    //Compute variance.  
    float Variance = Moments.y - (Moments.x * Moments.x); 

    float minVariance = cVSMShadowParams.x;
    Variance = max(Variance, minVariance);  
    //Compute probabilistic upper bound.  
    float d = depth - Moments.x;  
    float p_max = Variance / (Variance + d*d); 
    // Prevent light bleeding
    p_max = ReduceLightBleeding(cVSMShadowParams.y, p_max);

    return max(p, p_max);
}
#endif

float GetShadow(float4 shadowPos)
{
    #if defined(SIMPLE_SHADOW)
        // Take one sample
        #ifdef D3D11
            shadowPos.xyz /= shadowPos.w;
        #endif
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
    
    #elif defined(PCF_SHADOW)
        // Take four samples and average them
        // Note: in case of sampling a point light cube shadow, we optimize out the w divide as it has already been performed
        #ifdef D3D11
            shadowPos.xyz /= shadowPos.w;
        #endif
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
    
    #elif defined(VSM_SHADOW)
        float2 samples = Sample2D(ShadowMap, shadowPos.xy / shadowPos.w).rg;
        return cShadowIntensity.y + cShadowIntensity.x * Chebyshev(samples, shadowPos.z/shadowPos.w);
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
#endif