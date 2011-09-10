#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,
    float3 iNormal : NORMAL,
    #ifdef NORMALMAP
        float4 iTangent : TANGENT0,
    #endif
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
    out float4 oWorldPos : TEXCOORD1,
    out float3 oNormal : TEXCOORD2,
    #ifdef NORMALMAP
        out float3 oTangent : TEXCOORD3,
        out float3 oBitangent : TEXCOORD4,
    #endif
    #ifdef SHADOW
        out float4 oShadowPos : TEXCOORD5,
    #endif
    #ifdef SPOTLIGHT
        out float4 oSpotPos : TEXCOORD6,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION,
    out float2 oTexCoord : TEXCOORD0)
{
    float4 pos;

    #if defined(SKINNED)
        #ifndef NORMALMAP
            pos = GetPositionNormalSkinned(iPos, iNormal, iBlendWeights, iBlendIndices, oPos, oNormal);
        #else
            pos = GetPositionNormalTangentSkinned(iPos, iNormal, iTangent, iBlendWeights, iBlendIndices, oPos, oNormal, oTangent);
        #endif
    #elif defined(INSTANCED)
        #ifndef NORMALMAP
            pos = GetPositionNormalInstanced(iPos, iNormal, iModelInstance, oPos, oNormal);
        #else
            pos = GetPositionNormalTangentInstanced(iPos, iNormal, iTangent, iModelInstance, oPos, oNormal, oTangent);
        #endif
    #elif defined(BILLBOARD)
        pos = GetPositionBillboard(iPos, iSize, oPos);
        oNormal = float3(-cCameraRot[2][0], -cCameraRot[2][1], -cCameraRot[2][2]);
    #else
        #ifndef NORMALMAP
            pos = GetPositionNormal(iPos, iNormal, oPos, oNormal);
        #else
            pos = GetPositionNormalTangent(iPos, iNormal, iTangent, oPos, oNormal, oTangent);
        #endif
    #endif

    // Store adjusted world position and linear depth for light calculations
    oWorldPos = float4(pos.xyz - cCameraPos, GetDepth(oPos));

    #ifdef SHADOW
        // Shadow projection: transform from world space to shadow space
        oShadowPos = mul(pos, cShadowProj);
    #endif
    #ifdef SPOTLIGHT
        // Spotlight projection: transform from world space to projector texture coordinates
        oSpotPos = mul(pos, cSpotProj);
    #endif

    #ifdef NORMALMAP
        oBitangent = cross(oTangent, oNormal) * iTangent.w;
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif

    oTexCoord = GetTexCoord(iTexCoord);
}

void PS(float2 iTexCoord : TEXCOORD0,
    float4 iWorldPos : TEXCOORD1,
    #ifdef NORMALMAP
        float3 iNormal : TEXCOORD2,
        float3 iTangent : TEXCOORD3,
        float3 iBitangent : TEXCOORD4,
    #else
        float3 iNormal : TEXCOORD2,
    #endif
    #if defined(SHADOW)
        float4 iShadowPos : TEXCOORD5,
    #endif
    #ifdef SPOTLIGHT
        float4 iSpotPos : TEXCOORD6,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffColor = cMatDiffColor * tex2D(sDiffMap, iTexCoord);
    #else
        float4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= iColor;
    #endif

    #if !defined(VOLUMETRIC) && (defined(DIRLIGHT) || defined(POINTLIGHT) || defined(SPOTLIGHT))

        float3 lightColor;
        float3 lightDir;
        float3 lightVec;
        float diff;

        #ifdef NORMALMAP
            float3x3 tbn = float3x3(iTangent, iBitangent, iNormal);
            float3 normal = normalize(mul(UnpackNormal(tex2D(sNormalMap, iTexCoord)), tbn));
        #else
            float3 normal = normalize(iNormal);
        #endif

        #ifdef DIRLIGHT
            diff = GetDiffuseDir(normal, lightDir) * GetSplitFade(iWorldPos.w);
        #else
            diff = GetDiffusePointOrSpot(normal, iWorldPos.xyz, lightDir, lightVec);
        #endif

        #ifdef SHADOW
            diff *= GetShadow(iShadowPos);
        #endif

        #if defined(SPOTLIGHT)
            lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #elif defined(CUBEMASK)
            lightColor = texCUBE(sLightCubeMap, mul(lightVec, cLightVecRot)).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif

        #ifdef SPECULAR
            #ifdef SPECMAP
                float specStrength = cMatSpecProperties.x * tex2D(sSpecMap, iTexCoord).g;
            #else
                float specStrength = cMatSpecProperties.x;
            #endif
            float spec = GetSpecular(normal, iWorldPos.xyz, lightDir, cMatSpecProperties.y);
            float3 finalColor = diff * lightColor * (diffColor.rgb + spec * specStrength * cLightColor.a);
        #else
            float3 finalColor = diff * lightColor * diffColor.rgb;
        #endif

        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            oColor = float4(GetFog(finalColor, iWorldPos.w), diffColor.a);
        #else
            oColor = float4(GetLitFog(finalColor, iWorldPos.w), diffColor.a);
        #endif

    #else

        #if defined(VOLUMETRIC) && (defined(DIRLIGHT) || defined(POINTLIGHT) || defined(SPOTLIGHT))

            float3 lightColor;
            float3 lightVec;
            float diff;

            #ifdef DIRLIGHT
                diff = GetDiffuseDirVolumetric() * GetSplitFade(iWorldPos.w);
            #else
                diff = GetDiffusePointOrSpotVolumetric(iWorldPos.xyz, lightVec);
            #endif

            #if defined(SPOTLIGHT)
                lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
            #elif defined(CUBEMASK)
                lightColor = texCUBE(sLightCubeMap, mul(lightVec, cLightVecRot)).rgb * cLightColor.rgb;
            #else
                lightColor = cLightColor.rgb;
            #endif

            float3 finalColor = diff * lightColor * diffColor.rgb;

            #ifdef AMBIENT
                finalColor += cAmbientColor * diffColor.rgb;
                oColor = float4(GetFog(finalColor, iWorldPos.w), diffColor.a);
            #else
                oColor = float4(GetLitFog(finalColor, iWorldPos.w), diffColor.a);
            #endif

        #else

            #ifdef UNLIT
                oColor = float4(GetFog(diffColor.rgb, iWorldPos.w), diffColor.a);
            #endif

            #ifdef ADDITIVE
                oColor = float4(GetLitFog(diffColor.rgb, iWorldPos.w), diffColor.a);
            #endif

            #ifdef AMBIENT
                float3 finalColor = cAmbientColor * diffColor.rgb;
                oColor = float4(GetFog(finalColor, iWorldPos.w), diffColor.a);
            #endif

        #endif

    #endif
}
