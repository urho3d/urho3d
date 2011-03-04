#include "Common.hlsl"

void vs(float4 iPos : POSITION,
    #ifndef UNLIT
        float3 iNormal : NORMAL,
    #endif
    #ifdef NORMALMAP
        float4 iTangent : TANGENT0,
    #endif
    float2 iTexCoord : TEXCOORD0,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        #ifndef SM3
            int iInstanceNumber : TEXCOORD2,
        #else
            float4x3 iModelInstance : TEXCOORD2,
        #endif
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
    out float4 oPos : POSITION,
    out float2 oTexCoord : TEXCOORD0)
{
    float4 pos;
    
    #ifdef UNLIT
        float3 iNormal = float3(0, 0, -1);
    #endif

    #ifndef SKINNED
        #ifndef INSTANCED
            #ifndef NORMALMAP
                pos = evaluatePositionNormal(iPos, iNormal, oPos, oNormal);
            #else
                pos = evaluatePositionNormalTangent(iPos, iNormal, iTangent, oPos, oNormal, oTangent);
            #endif
        #else
            #ifndef SM3
                #ifndef NORMALMAP
                    pos = evaluatePositionNormalInstanced(iPos, iNormal, cModelInstances[iInstanceNumber], oPos, oNormal);
                #else
                    pos = evaluatePositionNormalTangentInstanced(iPos, iNormal, iTangent, cModelInstances[iInstanceNumber], oPos, oNormal, oTangent);
                #endif
            #else
                #ifndef NORMALMAP
                    pos = evaluatePositionNormalInstanced(iPos, iNormal, iModelInstance, oPos, oNormal);
                #else
                    pos = evaluatePositionNormalTangentInstanced(iPos, iNormal, iTangent, iModelInstance, oPos, oNormal, oTangent);
                #endif
            #endif
        #endif
    #else
        #ifndef NORMALMAP
            pos = evaluatePositionNormalSkinned(iPos, iNormal, iBlendWeights, iBlendIndices, oPos, oNormal);
        #else
            pos = evaluatePositionNormalTangentSkinned(iPos, iNormal, iTangent, iBlendWeights, iBlendIndices, oPos, oNormal, oTangent);
        #endif
    #endif
    
    // Store world-oriented view position for light calculations
    oWorldPos = float4(adjustWorldPos(pos), calculateDepth(oPos));

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
    
    oTexCoord = evaluateTexCoord(iTexCoord);
}

void ps(float2 iTexCoord : TEXCOORD0,
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
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffColor = cMatDiffColor * tex2D(sDiffMap, iTexCoord);
    #else
        float4 diffColor = cMatDiffColor;
    #endif

    #ifdef AMBIENT
        float3 finalColor = cAmbientColorPS * diffColor.rgb;
        oColor = float4(evaluateFog(finalColor, iWorldPos.w), diffColor.a);
    #endif
    
    #ifdef UNLIT
        oColor = float4(evaluateFog(diffColor.rgb, iWorldPos.w), diffColor.a);
    #endif
    
    #if (defined(DIRLIGHT)) || (defined(POINTLIGHT)) || (defined(SPOTLIGHT))
        float3 lightColor;
        float3 lightDir;
        float3 lightVec;
        float diff;

        #ifndef NEGATIVE
            // Normal (positive) lighting
            #ifdef NORMALMAP
                float3x3 tbn = float3x3(iTangent, iBitangent, iNormal);
                float3 normal = normalize(mul(unpackNormal(tex2D(sNormalMap, iTexCoord)), tbn));
            #else
                float3 normal = normalize(iNormal);
            #endif

            #ifdef DIRLIGHT
                diff = evaluateDiffuseDir(normal, lightDir) * evaluateSplitFade(iWorldPos.w);
            #else
                diff = evaluateDiffusePointOrSpot(normal, iWorldPos.xyz, lightDir, lightVec);
            #endif

            #ifdef SM3
            if (diff != 0.0)
            {
            #endif

            #ifdef SHADOW
                diff *= evaluateShadow(iShadowPos);
            #endif

            #ifdef SPOTLIGHT
                lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
            #else
                #ifdef CUBEMASK
                    lightColor = texCUBE(sLightCubeMap, mul(lightVec, cLightVecRot)).rgb * cLightColor.rgb;
                #else
                    lightColor = cLightColor.rgb;
                #endif
            #endif
            
            #ifdef SPECULAR
                #ifdef SPECMAP
                    float specStrength = cMatSpecProperties.x * tex2D(sSpecMap, iTexCoord).r;
                #else
                    float specStrength = cMatSpecProperties.x;
                #endif
                float spec = evaluateSpecular(normal, iWorldPos.xyz, lightDir, cMatSpecProperties.y);

                float3 finalColor = diff * lightColor * (diffColor.rgb + spec * specStrength * cLightColor.a);
                oColor = float4(evaluateLitFog(finalColor, iWorldPos.w), diffColor.a);
            #else
                float3 finalColor = diff * lightColor * diffColor.rgb;
                oColor = float4(evaluateLitFog(finalColor, iWorldPos.w), diffColor.a);
            #endif
            
            #ifdef SM3
            }
            else
                oColor = float4(0.0, 0.0, 0.0, diffColor.a);
            #endif
        #else
            // Negative lighting
            #ifdef DIRLIGHT
                diff = evaluateDiffuseDirVolumetric() * evaluateSplitFade(iWorldPos.w);
            #else
                diff = evaluateDiffusePointOrSpotVolumetric(iWorldPos.xyz, lightVec);
            #endif

            #ifdef SPOTLIGHT
                lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
            #else
                #ifdef CUBEMASK
                    lightColor = texCUBE(sLightCubeMap, mul(lightVec, cLightVecRot)).rgb * cLightColor.rgb;
                #else
                    lightColor = cLightColor.rgb;
                #endif
            #endif
            
            float3 finalColor = 1.0 + diff * diffColor.a * evaluateReverseFogFactor(iWorldPos.w) * lightColor;
            oColor = float4(finalColor, 1.0);
        #endif
    #endif
}
