#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl" 
#include "BDRF.hlsl"

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
    float roughness = 0;
   
    roughness = normalInput.a;
    float metalness = clamp(albedoInput.a, 0.1, 1.0);

    float f0 = lerp(float3(0.03,0.03,0.03), albedoInput.rgb, metalness).r;
    float3 specColor = max(albedoInput.rgb * metalness, float3(0.08, 0.08, 0.08));
    specColor *= cMatSpecColor.rgb;

    float3 normal = normalize(normalInput.rgb * 2.0 - 1.0);
    
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

    float3 toCamera = normalize(-worldPos);
    float3 lightVec = lightDir;
 
   
    float3 diffHn = normalize(toCamera + lightDir);
    float diffvdh = max(0.0, dot(toCamera, diffHn));
    float diffndl = max(0.0, dot(normal, lightDir));
    float diffndv = max(1e-5, dot(normal, toCamera));
  
    float areaLight = 1;
    // #if defined(POINTLIGHT)               
    //     areaLight = AreaLight(lightVec, toCamera, normal, -worldPos + cLightPosPS.xyz, roughness);
    // #endif
   
    float3 diffuseTerm = BurleyDiffuse(albedoInput.rgb, roughness, diffndv, diffndl, diffvdh) * diff * lightColor.rgb;
 

    float3 Hn = normalize(toCamera + lightVec);
    float vdh = max(0.0, dot(toCamera, Hn));
    float ndh = max(0.0, dot(normal, Hn));
    float ndl = max(0.0, dot(normal, lightVec));
    float ndv = max(1e-5, dot(normal, toCamera));
   

    float3 fresnelTerm = SchlickGaussianFresnel(f0, vdh) ;
    float distTerm = GGXDistribution(ndh, roughness) * areaLight;
    float visTerm = SchlickVisibility(ndl, ndv, roughness);

    oColor.a = 1;
    oColor.rgb = LinearFromSRGB((diffuseTerm + distTerm * visTerm * fresnelTerm * lightColor) * diff);  
}
