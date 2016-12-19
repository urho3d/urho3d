#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl"
#include "Constants.hlsl"
#include "PBR.hlsl"
#line 9

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
        float3 depth = Sample2DLod0(DepthBuffer, iScreenPos).r;
        #ifdef HWDEPTH
            depth = ReconstructDepth(depth);
        #endif
        #ifdef ORTHO
            float3 worldPos = lerp(iNearRay, iFarRay, depth);
        #else
            float3 worldPos = iFarRay * depth;
        #endif
        const float4 albedoInput = Sample2DLod0(AlbedoBuffer, iScreenPos);
        const float4 normalInput = Sample2DLod0(NormalBuffer, iScreenPos);
        const float4 specularInput = Sample2DLod0(SpecMap, iScreenPos);
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
        const float4 albedoInput = Sample2DProj(AlbedoBuffer, iScreenPos);
        const float4 normalInput = Sample2DProj(NormalBuffer, iScreenPos);
        const float4 specularInput = Sample2DProj(SpecMap, iScreenPos);
    #endif

    // Position acquired via near/far ray is relative to camera. Bring position to world space
    float3 eyeVec = -worldPos;
    worldPos += cCameraPosPS;

    float3 normal = normalInput.rgb;
    const float roughness = length(normal);
    normal = normalize(normal);

    const float3 specColor = specularInput.rgb;

    const float4 projWorldPos = float4(worldPos, 1.0);

    float3 lightDir;
     float atten = 1;

        #if defined(DIRLIGHT)
            atten = GetAtten(normal, worldPos, lightDir);
        #elif defined(SPOTLIGHT)
            atten = GetAttenSpot(normal, worldPos, lightDir);
        #else
            atten = GetAttenPoint(normal, worldPos, lightDir);
        #endif

    float shadow = 1;
    #ifdef SHADOW
        shadow *= GetShadowDeferred(projWorldPos, normal, depth);
    #endif

    #if defined(SPOTLIGHT)
        const float4 spotPos = mul(projWorldPos, cLightMatricesPS[0]);
        const float3 lightColor = spotPos.w > 0.0 ? Sample2DProj(LightSpotMap, spotPos).rgb * cLightColor.rgb : 0.0;
    #elif defined(CUBEMASK)
        const float3 lightColor = texCUBE(sLightCubeMap, mul(worldPos - cLightPosPS.xyz, (float3x3)cLightMatricesPS[0])).rgb * cLightColor.rgb;
    #else
        const float3 lightColor = cLightColor.rgb;
    #endif

    const float3 toCamera = normalize(eyeVec);
    const float3 lightVec = normalize(lightDir);
    const float ndl = clamp(abs(dot(normal, lightVec)), M_EPSILON, 1.0);

    float3 BRDF = GetBRDF(worldPos, lightDir, lightVec, toCamera, normal, roughness, albedoInput.rgb, specColor);

    oColor.a = 1;
    oColor.rgb  = BRDF * lightColor * shadow * atten / M_PI;
}
