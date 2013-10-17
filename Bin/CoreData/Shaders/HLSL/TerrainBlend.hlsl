#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"

sampler2D sWeightMap0 : register(S0);
sampler2D sDetailMap1 : register(S1);
sampler2D sDetailMap2 : register(S2);
sampler2D sDetailMap3 : register(S3);

uniform float2 cDetailTiling;

void VS(float4 iPos : POSITION,
    float3 iNormal : NORMAL,
    float2 iTexCoord : TEXCOORD0,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD2,
    #endif
    #ifdef BILLBOARD
        float2 iSize : TEXCOORD1,
    #endif
    out float2 oTexCoord : TEXCOORD0,
    #ifdef HEIGHTFOG
        out float3 oWorldPos : TEXCOORD8,
    #endif
    out float3 oNormal : TEXCOORD2,
    #ifdef PERPIXEL
        out float4 oLightVec : TEXCOORD1,
        #ifdef SPECULAR
            out float3 oEyeVec : TEXCOORD3,
        #endif
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
        out float4 oVertexLight : TEXCOORD1,
        out float4 oScreenPos : TEXCOORD3,
    #endif
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetTexCoord(iTexCoord);
    oNormal = GetWorldNormal(modelMatrix);

    #ifdef HEIGHTFOG
        oWorldPos = worldPos;
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        float4 projWorldPos = float4(worldPos, 1.0);

        #ifdef DIRLIGHT
            oLightVec = float4(cLightDir, GetDepth(oPos));
        #else
            oLightVec = float4((cLightPos.xyz - worldPos) * cLightPos.w, GetDepth(oPos));
        #endif

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            GetShadowPos(projWorldPos, oShadowPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            oSpotPos = mul(projWorldPos, cLightMatrices[0]);
        #endif

        #ifdef POINTLIGHT
            oCubeMaskVec = mul(oLightVec.xyz, (float3x3)cLightMatrices[0]);
        #endif

        #ifdef SPECULAR
            oEyeVec = cCameraPos - worldPos;
        #endif
    #else
        // Ambient & per-vertex lighting
        oVertexLight = float4(GetAmbient(GetZonePos(worldPos)), GetDepth(oPos));

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                oVertexLight.rgb += GetVertexLight(i, worldPos, oNormal) * cVertexLights[i * 3].rgb;
        #endif

        oScreenPos = GetScreenPos(oPos);
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    #ifdef HEIGHTFOG
        float3 iWorldPos : TEXCOORD8,
    #endif
    #ifdef PERPIXEL
        float4 iLightVec : TEXCOORD1,
        float3 iNormal : TEXCOORD2,
        #ifdef SPECULAR
            float3 iEyeVec : TEXCOORD3,
        #endif
        #ifdef SHADOW
            float4 iShadowPos[NUMCASCADES] : TEXCOORD4,
        #endif
        #ifdef SPOTLIGHT
            float4 iSpotPos : TEXCOORD5,
        #endif
        #ifdef CUBEMASK
            float3 iCubeMaskVec : TEXCOORD5,
        #endif
    #else
        float4 iVertexLight : TEXCOORD1,
        float3 iNormal : TEXCOORD2,
        float4 iScreenPos : TEXCOORD3,
    #endif
    #ifdef PREPASS
        out float4 oDepth : COLOR1,
    #endif
    #ifdef DEFERRED
        out float4 oAlbedo : COLOR1,
        out float4 oNormal : COLOR2,
        out float4 oDepth : COLOR3,
    #endif
    out float4 oColor : COLOR0)
{
    // Get material diffuse albedo
    float3 weights = tex2D(sWeightMap0, iTexCoord).rgb;
    float sumWeights = weights.r + weights.g + weights.b;
    weights /= sumWeights;
    float2 detailTexCoord = cDetailTiling * iTexCoord;
    float4 diffColor = cMatDiffColor * (weights.r * tex2D(sDetailMap1, detailTexCoord) +
        weights.g * tex2D(sDetailMap2, detailTexCoord) + weights.b * tex2D(sDetailMap3, detailTexCoord));

    // Get material specular albedo
    float3 specColor = cMatSpecColor.rgb;

    #if defined(PERPIXEL)
        // Per-pixel forward lighting
        float3 lightDir;
        float3 lightColor;
        float3 finalColor;
        float diff;

        float3 normal = normalize(iNormal);
        
        diff = GetDiffuse(normal, iLightVec.xyz, lightDir);
    
        #ifdef SHADOW
            diff *= GetShadow(iShadowPos, iLightVec.w);
        #endif
    
        #if defined(SPOTLIGHT)
            lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #elif defined(CUBEMASK)
            lightColor = texCUBE(sLightCubeMap, iCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
    
        #ifdef SPECULAR
            float spec = GetSpecular(normal, iEyeVec, lightDir, cMatSpecColor.a);
            finalColor = diff * lightColor * (diffColor.rgb + spec * specColor * cLightColor.a);
        #else
            finalColor = diff * lightColor * diffColor.rgb;
        #endif

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(iLightVec.w, iWorldPos.y);
        #else
            float fogFactor = GetFogFactor(iLightVec.w);
        #endif
    
        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            oColor = float4(GetFog(finalColor, fogFactor), diffColor.a);
        #else
            oColor = float4(GetLitFog(finalColor, fogFactor), diffColor.a);
        #endif
    #elif defined(PREPASS)
        // Fill light pre-pass G-Buffer
        float3 normal = iNormal;

        float specPower = cMatSpecColor.a / 255.0;

        oColor = float4(normal * 0.5 + 0.5, specPower);
        oDepth = iVertexLight.a;
    #elif defined(DEFERRED)
        // Fill deferred G-buffer
        float3 normal = iNormal;

        // If using SM2, light volume shader may not have instructions left to normalize the normal. Therefore do it here
        #if !defined(SM3)
            normal = normalize(normal);
        #endif

        float specIntensity = specColor.g;
        float specPower = cMatSpecColor.a / 255.0;

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(iVertexLight.a, iWorldPos.y);
        #else
            float fogFactor = GetFogFactor(iVertexLight.a);
        #endif

        oColor = float4(GetFog(iVertexLight.rgb * diffColor.rgb, fogFactor), 1.0);
        oAlbedo = fogFactor * float4(diffColor.rgb, specIntensity);
        oNormal = float4(normal * 0.5 + 0.5, specPower);
        oDepth = iVertexLight.a;
    #else
        // Ambient & per-vertex lighting
        float3 finalColor = iVertexLight.rgb * diffColor.rgb;

        #ifdef MATERIAL
            // Add light pre-pass accumulation result
            // Lights are accumulated at half intensity. Bring back to full intensity now
            float4 lightInput = 2.0 * tex2Dproj(sLightBuffer, iScreenPos);
            float3 lightSpecColor = lightInput.a * (lightInput.rgb / GetIntensity(lightInput.rgb));

            finalColor += lightInput.rgb * diffColor.rgb + lightSpecColor * specColor;
        #endif

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(iVertexLight.a, iWorldPos.y);
        #else
            float fogFactor = GetFogFactor(iVertexLight.a);
        #endif

        oColor = float4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
