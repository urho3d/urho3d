#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl"
#include "DeferredGBuffer.hlsl"

void VS(float4 iPos : POSITION,
#ifdef DIRLIGHT
	out float2 oScreenPos : TEXCOORD0,
#else
	out float4 oScreenPos : TEXCOORD0,
#endif
	out float3 oFarRay : TEXCOORD1,
#ifdef ORTHO
	out float3 oNearRay : TEXCOORD2,
#endif
	out float4 oPos : OUTPOSITION)
{
	float4x3 modelMatrix = iModelMatrix;
	float3 worldPos = GetWorldPos(modelMatrix);
	oPos = GetClipPos(worldPos);
#ifdef DIRLIGHT
	oScreenPos = GetScreenPosPreDiv(oPos);
	oFarRay = GetFarRay(oPos);
#ifdef ORTHO
	oNearRay = GetNearRay(oPos);
#endif
#else
	oScreenPos = GetScreenPos(oPos);
	oFarRay = GetFarRay(oPos) * oPos.w;
#ifdef ORTHO
	oNearRay = GetNearRay(oPos) * oPos.w;
#endif
#endif
}


void PS(
    #ifdef DIRLIGHT
        float2 iScreenPos : TEXCOORD0,
    #else
        float4 iScreenPos : TEXCOORD0,
    #endif
    float3 iFarRay : TEXCOORD1,
    #ifdef ORTHO
        float3 iNearRay : TEXCOORD2,
    #endif

        float2 iFragPos : VPOS,

    out float4 oColor : OUTCOLOR0)
{
    // If rendering a directional light quad, optimize out the w divide
    #ifdef DIRLIGHT
        float depth = Sample2DLod0(DepthBuffer, iScreenPos).r;
        #ifdef HWDEPTH
            depth = ReconstructDepth(depth);
        #endif
        #ifdef ORTHO
            float3 worldPos = lerp(iNearRay, iFarRay, depth);
        #else
            float3 worldPos = iFarRay * depth;
        #endif
        float4 albedoInput = Sample2DLod0(AlbedoBuffer, iScreenPos);
        float4 normalInput = Sample2DLod0(NormalBuffer, iScreenPos);
    #else
        float depth = Sample2DProj(DepthBuffer, iScreenPos).r;
        #ifdef HWDEPTH
            depth = ReconstructDepth(depth);
        #endif
        #ifdef ORTHO
            float3 worldPos = lerp(iNearRay, iFarRay, depth) / iScreenPos.w;
        #else
            float3 worldPos = iFarRay * depth / iScreenPos.w;
        #endif
        float4 albedoInput = Sample2DProj(AlbedoBuffer, iScreenPos);
        float4 normalInput = Sample2DProj(NormalBuffer, iScreenPos);
    #endif
    
 
        float3 normal = DecodeGBufferNormal(normalInput.xy, iFarRay);
        const float roughness = normalInput.b;
        #ifdef DIRLIGHT
            float3 specColor = 0;
            float3 albedoColor = 0;
            DecodeYCoCgElements(iScreenPos.xy, albedoInput, albedoColor, specColor);
            albedoInput.rgb = albedoColor;
            albedoInput.a = 1;
        #else
            float3 specColor = 0;
            float3 albedoColor = 0;
            DecodeYCoCgElements(iScreenPos.xy/iScreenPos.w, albedoInput, albedoColor, specColor);
            albedoInput.rgb = albedoColor;
            albedoInput.a = 1;
        #endif
        albedoInput.a = 1.0;

    
    float4 projWorldPos = float4(worldPos, 1.0);
    float3 lightColor;
    float3 lightDir;

    float diff = GetDiffuse(normal, worldPos, lightDir);

    #ifdef SHADOW
        diff *= GetShadowDeferred(projWorldPos, depth);
    #endif

    #if defined(SPOTLIGHT)
        float4 spotPos = mul(projWorldPos, cLightMatricesPS[0]);
        lightColor = spotPos.w > 0.0 ? Sample2DProj(LightSpotMap, spotPos).rgb * cLightColor.rgb : 0.0;
    #elif defined(CUBEMASK)
        lightColor = texCUBE(sLightCubeMap, mul(worldPos - cLightPosPS.xyz, (float3x3)cLightMatricesPS[0])).rgb * cLightColor.rgb;
    #else
        lightColor = cLightColor.rgb;
    #endif

    #ifdef PBR          
        float3 toCamera = normalize(-worldPos.xyz);
        
        const float3 Hn = normalize(toCamera + lightDir);
        const float vdh = max(0.0, dot(toCamera, Hn));
        const float ndh = max(0.0, dot(normal, Hn));
        const float ndl = max(0.0, dot(normal, lightDir));
        const float ndv = max(1e-5, dot(normal, toCamera));
        
        const float3 diffuseTerm = LambertianDiffuse(albedoInput.rgb, roughness, ndv, ndl, vdh) * lightColor * diff;
        const float3 fresnelTerm = SchlickFresnel(specColor, vdh);
        const float distTerm = GGXDistribution(ndh, roughness);
        const float visTerm = SchlickVisibility(ndl, ndv, roughness);
        
        oColor.a = 1;
        oColor.rgb = LinearFromSRGB((diffuseTerm + distTerm * visTerm * fresnelTerm * lightColor) * diff);
    #else
        #ifdef SPECULAR
            float spec = GetSpecular(normal, -worldPos, lightDir, normalInput.a * 255.0);
            oColor = diff * float4(lightColor * (albedoInput.rgb + spec * cLightColor.a * albedoInput.aaa), 0.0);
        #else
            oColor = diff * float4(lightColor * albedoInput.rgb, 0.0);
        #endif
    #endif
}
