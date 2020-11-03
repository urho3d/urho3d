#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Constants.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"
#include "PBR.hlsl"
#include "IBL.hlsl"

#ifndef D3D11

// D3D9 uniforms and samplers
#ifdef COMPILEVS
uniform float2 cDetailTiling;
#else
sampler2D sWeightMap0 : register(s0);
sampler2D sDetailMap1 : register(s1);
sampler2D sDetailMap2 : register(s2);
sampler2D sDetailMap3 : register(s3);
#endif

#else

// D3D11 constant buffers and samplers
#ifdef COMPILEVS
cbuffer CustomVS : register(b6)
{
    float2 cDetailTiling;
}
#else
Texture2D tWeightMap0 : register(t0);
Texture2D tDetailMap1 : register(t1);
Texture2D tDetailMap2 : register(t2);
Texture2D tDetailMap3 : register(t3);
SamplerState sWeightMap0 : register(s0);
SamplerState sDetailMap1 : register(s1);
SamplerState sDetailMap2 : register(s2);
SamplerState sDetailMap3 : register(s3);
#endif

#endif
void VS(float4 iPos : POSITION,
        float3 iNormal : NORMAL,
        float2 iTexCoord : TEXCOORD0,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD4,
    #endif
    #if defined(BILLBOARD) || defined(DIRBILLBOARD)
        float2 iSize : TEXCOORD1,
    #endif
    out float2 oTexCoord : TEXCOORD0,
    out float3 oNormal : TEXCOORD1,
    out float4 oWorldPos : TEXCOORD2,
    out float2 oDetailTexCoord : TEXCOORD3,
    #ifdef PERPIXEL
        #ifdef SHADOW
            out float4 oShadowPos[NUMCASCADES] : TEXCOORD4,
        #endif
        #ifdef SPOTLIGHT
            out float4 oSpotPos : TEXCOORD5,
        #endif
        #ifdef POINTLIGHT
            out float3 oCubeMaskVec : TEXCOORD5,
        #endif
    #else
        out float3 oVertexLight : TEXCOORD4,
        out float4 oScreenPos : TEXCOORD5,
    #endif
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    #if defined(D3D11) && defined(CLIPPLANE)
        out float oClip : SV_CLIPDISTANCE0,
    #endif
    out float4 oPos : OUTPOSITION)
{
    const float4x3 modelMatrix = iModelMatrix;
    const float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oNormal = GetWorldNormal(modelMatrix);
    oWorldPos = float4(worldPos, GetDepth(oPos));
    oTexCoord = GetTexCoord(iTexCoord);
    oDetailTexCoord = cDetailTiling * oTexCoord;

    #if defined(D3D11) && defined(CLIPPLANE)
        oClip = dot(oPos, cClipPlane);
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        const float4 projWorldPos = float4(worldPos.xyz, 1.0);

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            GetShadowPos(projWorldPos, oNormal, oShadowPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            oSpotPos = mul(projWorldPos, cLightMatrices[0]);
        #endif

        #ifdef POINTLIGHT
            oCubeMaskVec = mul(worldPos - cLightPos.xyz, (float3x3)cLightMatrices[0]);
        #endif
    #else
        oVertexLight = GetAmbient(GetZonePos(worldPos));

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                oVertexLight += GetVertexLight(i, worldPos, oNormal) * cVertexLights[i * 3].rgb;
        #endif

        oScreenPos = GetScreenPos(oPos);
    #endif
}

void PS(
    float2 iTexCoord : TEXCOORD0,
    float3 iNormal : TEXCOORD1,
    float4 iWorldPos : TEXCOORD2,
    float2 iDetailTexCoord : TEXCOORD3,
    #ifdef PERPIXEL
        #ifdef SHADOW
            float4 iShadowPos[NUMCASCADES] : TEXCOORD4,
        #endif
        #ifdef SPOTLIGHT
            float4 iSpotPos : TEXCOORD5,
        #endif
        #ifdef POINTLIGHT
            float3 iCubeMaskVec : TEXCOORD5,
        #endif
    #else
        float3 iVertexLight : TEXCOORD4,
        float4 iScreenPos : TEXCOORD5,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #if defined(D3D11) && defined(CLIPPLANE)
        float iClip : SV_CLIPDISTANCE0,
    #endif
    #ifdef PREPASS
        out float4 oDepth : OUTCOLOR1,
    #endif
    #ifdef DEFERRED
        out float4 oAlbedo : OUTCOLOR1,
        out float4 oNormal : OUTCOLOR2,
        out float4 oDepth : OUTCOLOR3,
        #ifndef D3D11
            float2 iFragPos : VPOS,
        #else
            float4 iFragPos : SV_Position,
        #endif
    #endif
    out float4 oColor : OUTCOLOR0)
{
    // Get material diffuse albedo
    float3 weights = Sample2D(WeightMap0, iTexCoord).rgb;
    float sumWeights = weights.r + weights.g + weights.b;
    weights /= sumWeights;
    float4 diffColor = cMatDiffColor * (
        weights.r * Sample2D(DetailMap1, iDetailTexCoord) +
        weights.g * Sample2D(DetailMap2, iDetailTexCoord) +
        weights.b * Sample2D(DetailMap3, iDetailTexCoord)
    );

    // Get material specular albedo
    #ifdef METALLIC // METALNESS
        float4 roughMetalSrc = Sample2D(RoughMetalFresnel, iTexCoord.xy);

        float roughness = roughMetalSrc.r + cRoughness;
        float metalness = roughMetalSrc.g + cMetallic;
    #else
        float roughness = cRoughness;
        float metalness = cMetallic;
    #endif

    roughness *= roughness;

    roughness = clamp(roughness, ROUGHNESS_FLOOR, 1.0);
    metalness = clamp(metalness, METALNESS_FLOOR, 1.0);

    float3 specColor = lerp(0.08 * cMatSpecColor.rgb, diffColor.rgb, metalness);
    diffColor.rgb = diffColor.rgb - diffColor.rgb * metalness; // Modulate down the diffuse

    // Get normal
    const float3 normal = normalize(iNormal);

    // Get fog factor
    #ifdef HEIGHTFOG
        const float fogFactor = GetHeightFogFactor(iWorldPos.w, iWorldPos.y);
    #else
        const float fogFactor = GetFogFactor(iWorldPos.w);
    #endif

    #if defined(PERPIXEL)
        // Per-pixel forward lighting
        float3 lightDir;
        float3 lightColor;
        float3 finalColor;
        float atten = 1;

        #if defined(DIRLIGHT)
            atten = GetAtten(normal, iWorldPos.xyz, lightDir);
        #elif defined(SPOTLIGHT)
            atten = GetAttenSpot(normal, iWorldPos.xyz, lightDir);
        #else
            atten = GetAttenPoint(normal, iWorldPos.xyz, lightDir);
        #endif

        float shadow = 1.0;

        #ifdef SHADOW
            shadow *= GetShadow(iShadowPos, iWorldPos.w);
        #endif

        #if defined(SPOTLIGHT)
            lightColor = iSpotPos.w > 0.0 ? Sample2DProj(LightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #elif defined(CUBEMASK)
            lightColor = SampleCube(LightCubeMap, iCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif

        const float3 toCamera = normalize(cCameraPosPS - iWorldPos.xyz);

        const float3 lightVec = normalize(lightDir);
        const float ndl = clamp((dot(normal, lightVec)), M_EPSILON, 1.0);


        float3 BRDF = GetBRDF(iWorldPos.xyz, lightDir, lightVec, toCamera, normal, roughness, diffColor.rgb, specColor);
        finalColor.rgb = BRDF * lightColor * (atten * shadow) / M_PI;

        #ifdef AMBIENT
            finalColor += cAmbientColor.rgb * diffColor.rgb;
            finalColor += cMatEmissiveColor;
            oColor = float4(GetFog(finalColor, fogFactor), diffColor.a);
        #else
            oColor = float4(GetLitFog(finalColor, fogFactor), diffColor.a);
        #endif
    #elif defined(DEFERRED)
        // Fill deferred G-buffer
        const float3 spareData = 0; // Can be used to pass more data to deferred renderer
        oColor = float4(specColor, spareData.r);
        oAlbedo = float4(diffColor.rgb, spareData.g);
        oNormal = float4(normalize(normal) * roughness, spareData.b);
        oDepth = iWorldPos.w;
    #else
        // Ambient & per-vertex lighting
        float3 finalColor = iVertexLight * diffColor.rgb;
        #ifdef MATERIAL
            // Add light pre-pass accumulation result
            // Lights are accumulated at half intensity. Bring back to full intensity now
            float4 lightInput = 2.0 * Sample2DProj(LightBuffer, iScreenPos);
            float3 lightSpecColor = lightInput.a * lightInput.rgb / max(GetIntensity(lightInput.rgb), 0.001);

            finalColor += lightInput.rgb * diffColor.rgb + lightSpecColor * specColor;
        #endif

        const float3 toCamera = normalize(iWorldPos.xyz - cCameraPosPS);

        const float3 reflection = normalize(reflect(toCamera, normal));
        float3 cubeColor = iVertexLight.rgb;

        #ifdef IBL
            const float3 iblColor = ImageBasedLighting(reflection, normal, toCamera, diffColor, specColor, roughness, cubeColor);
            finalColor += iblColor;
        #endif

        finalColor += cMatEmissiveColor;

        oColor = float4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
