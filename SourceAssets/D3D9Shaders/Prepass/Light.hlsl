#include "../Uniforms.hlsl"
#include "../Samplers.hlsl"
#include "../Transform.hlsl"
#include "../ScreenPos.hlsl"
#include "../Lighting.hlsl"

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
    out float4 oPos : POSITION)
{
    GetPosition(iPos, oPos);
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
    out float4 oColor : COLOR0)
{
    // If rendering a directional light quad, optimize out the w divide
    #ifdef DIRLIGHT
        #ifdef ORTHO
            float depth = Sample(sDepthBuffer, iScreenPos).r;
            float3 worldPos = lerp(iNearRay, iFarRay, depth);
        #else
            float depth = Sample(sDepthBuffer, iScreenPos).r;
            float3 worldPos = iFarRay * depth;
        #endif
        float4 normalInput = Sample(sNormalBuffer, iScreenPos);
    #else
        #ifdef ORTHO
            float depth = tex2Dproj(sDepthBuffer, iScreenPos).r;
            float3 worldPos = lerp(iNearRay, iFarRay, depth) / iScreenPos.w;
        #else
            float depth = tex2Dproj(sDepthBuffer, iScreenPos).r;
            float3 worldPos = iFarRay * depth / iScreenPos.w;
        #endif
        float4 normalInput = tex2Dproj(sNormalBuffer, iScreenPos);
    #endif

    // With specular, normalization greatly improves stability of reflections,
    // considering input is only 8 bits per axis
    #ifdef SPECULAR
        float3 normal = normalize(normalInput.rgb * 2.0 - 1.0);
    #else
        float3 normal = normalInput.rgb * 2.0 - 1.0;
    #endif

    float3 lightColor;
    float3 lightDir;
    float diff;

    // Accumulate lights at half intensity to allow 2x "overburn"
    #ifdef DIRLIGHT
        diff = 0.5 * GetDiffuseDir(normal, lightDir) * GetSplitFade(depth);
    #else
        float3 lightVec;
        diff = 0.5 * GetDiffusePointOrSpot(normal, worldPos, lightDir, lightVec);
    #endif

    #ifdef SM3
    if (diff > 0.0)
    {
    #endif

    #ifdef SHADOW
        float4 shadowPos = mul(float4(worldPos, 1.0), cShadowProjPS);
        diff *= GetShadow(shadowPos);
    #endif

    #ifdef SPOTLIGHT
        float4 spotPos = mul(float4(worldPos, 1.0), cSpotProjPS);
        float3 shapeColor = spotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, spotPos).rgb : 0.0;
        lightColor = shapeColor * cLightColor.rgb;
    #else
        #ifdef CUBEMASK
            float3 shapeColor = texCUBE(sLightCubeMap, mul(lightVec, cLightVecRot)).rgb;
            lightColor = shapeColor * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
    #endif

    #ifdef SPECULAR
        #if defined(SPOTLIGHT) || defined(CUBEMASK)
            float spec = shapeColor.g * GetSpecular(normal, worldPos, lightDir, normalInput.a * 255.0);
        #else
            float spec = GetSpecular(normal, worldPos, lightDir, normalInput.a * 255.0);
        #endif
        oColor = diff * float4(lightColor, spec * cLightColor.a);
    #else
        oColor = diff * float4(lightColor, 0.0);
    #endif

    #ifdef SM3
    }
    else
        oColor = 0.0;
    #endif
}
