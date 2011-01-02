#include "../Common.hlsl"

void vs(float4 iPos : POSITION,
    #ifdef DIRLIGHT
        out float2 oScreenPos : TEXCOORD0,
    #else
        out float4 oScreenPos : TEXCOORD0,
    #endif
    out float3 oFarRay : TEXCOORD1,
    #ifdef ORTHO
        out float3 oNearRay : TEXCOORD2,
    #endif
    out float4 oPos : POSITION)
{
    evaluatePosition(iPos, oPos);
    #ifdef DIRLIGHT
        oScreenPos = calculateScreenPosPreDiv(oPos);
        oFarRay = calculateWorldFarRay(oPos);
        #ifdef ORTHO
            oNearRay = calculateWorldNearRay(oPos);
        #endif
    #else
        oScreenPos = calculateScreenPos(oPos);
        oFarRay = calculateWorldFarRay(oPos) * oPos.w;
        #ifdef ORTHO
            oNearRay = calculateWorldNearRay(oPos) * oPos.w;
        #endif
    #endif
}

void ps(
    #ifdef DIRLIGHT
        float2 iScreenPos : TEXCOORD0,
    #else
        float4 iScreenPos : TEXCOORD0,
    #endif
    float3 iWorldFarRay : TEXCOORD1,
    #ifdef ORTHO
        float3 iWorldNearRay : TEXCOORD2,
    #endif
    out float4 oColor : COLOR0)
{
    // If rendering a directional light quad, optimize out the w divide
    #ifdef DIRLIGHT
        #ifdef ORTHO
            float depth = sample(sDepthBuffer, iScreenPos).r;
            float3 worldPos = lerp(iWorldNearRay, iWorldFarRay, depth);
        #else
            #ifdef LINEAR
                float depth = sample(sDepthBuffer, iScreenPos).r;
            #else
                float depth = reconstructDepth(sample(sDepthBuffer, iScreenPos).r);
            #endif
            float3 worldPos = iWorldFarRay * depth;
        #endif
        float4 normalInput = sample(sNormalBuffer, iScreenPos);
    #else
        #ifdef ORTHO
            float depth = tex2Dproj(sDepthBuffer, iScreenPos).r;
            float3 worldPos = lerp(iWorldNearRay, iWorldFarRay, depth) / iScreenPos.w;
        #else
            #ifdef LINEAR
                float depth = tex2Dproj(sDepthBuffer, iScreenPos).r;
            #else
                float depth = reconstructDepth(tex2Dproj(sDepthBuffer, iScreenPos).r);
            #endif
            float3 worldPos = iWorldFarRay * depth / iScreenPos.w;
        #endif
        float4 normalInput = tex2Dproj(sNormalBuffer, iScreenPos);
    #endif

    #ifndef NEGATIVE
        // With specular, normalization greatly improves stability of reflections,
        // considering input is only 8 bits per axis
        #ifdef SPECULAR
            float3 normal = normalize(normalInput.rgb * 2.0 - 1.0);
        #else
            float3 normal = normalInput.rgb * 2.0 - 1.0;
        #endif

        float3 lightDir;
        float diff;

        // Accumulate lights at half intensity to allow 2x "overburn"
        #ifdef DIRLIGHT
            diff = 0.5 * evaluateDiffuseDir(normal, lightDir) * evaluateSplitFade(depth);
        #endif
        #ifdef POINTLIGHT
            float3 lightVec;
            diff = 0.5 * evaluateDiffusePoint(normal, worldPos, lightDir, lightVec);
        #endif
        #ifdef SPOTLIGHT
            float3 lightVec;
            float4 spotPos = mul(float4(worldPos, 1.0), cSpotProjPS);
            diff = 0.5 * evaluateDiffuseSpot(normal, worldPos, spotPos, lightDir, lightVec);
        #endif

        #ifdef SM3
        if (diff != 0.0)
        {
        #endif

        #ifdef SHADOW
            float4 shadowPos = mul(float4(worldPos, 1.0), cShadowProjPS);
            diff *= evaluateShadow(shadowPos);
        #endif

        #ifdef SPECULAR
            float spec = evaluateSpecular(normal, worldPos, lightDir, normalInput.a * 255.0);
            oColor = diff * float4(cLightColor.rgb, spec * cLightColor.a);
        #else
            oColor = float4(diff * cLightColor.rgb, 0.0);
        #endif

        #ifdef SM3
        }
        else
            oColor = 0.0;
        #endif
    #else
        // Negative lights are a lot simpler than normal lights: only depth input needed
        float3 lightDir;
        float diff;

        #ifdef DIRLIGHT
            diff = evaluateDiffuseDirVolumetric() * evaluateSplitFade(depth);
        #endif
        #ifdef POINTLIGHT
            float3 lightVec;
            diff = evaluateDiffusePointVolumetric(worldPos, lightDir, lightVec);
        #endif
        #ifdef SPOTLIGHT
            float3 lightVec;
            float4 spotPos = mul(float4(worldPos, 1.0), cSpotProjPS);
            diff = evaluateDiffuseSpotVolumetric(worldPos, spotPos, lightDir, lightVec);
        #endif

        float3 finalColor = 1.0 + diff * evaluateReverseFogFactor(depth) * cLightColor.rgb;
        oColor = float4(finalColor, 1.0);
    #endif
}
