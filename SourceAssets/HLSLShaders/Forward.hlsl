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
    out float4 oLightVec : TEXCOORD1,
    #ifdef LIGHT
        #ifndef NORMALMAP
            out float3 oNormal : TEXCOORD2,
        #endif
        #ifdef SPECULAR
            out float3 oEyeVec : TEXCOORD3,
        #endif
        #ifdef SHADOW
            #if defined(DIRLIGHT)
                out float4 oShadowPos[4] : TEXCOORD4,
            #elif defined(SPOTLIGHT)
                out float4 oShadowPos : TEXCOORD4,
            #else
                out float3 oShadowPos : TEXCOORD4,
            #endif
        #endif
        #ifdef SPOTLIGHT
            out float4 oSpotPos : TEXCOORD5,
        #endif
        #ifdef POINTLIGHT
            out float3 oCubeMaskVec : TEXCOORD5,
        #endif
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION,
    out float2 oTexCoord : TEXCOORD0)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetTexCoord(iTexCoord);

    #ifdef LIGHT

        #ifdef NORMALMAP
            float3 oNormal;
            float3 oTangent;
            float3 oBitangent;
        #endif

        oNormal = GetWorldNormal(modelMatrix);
        float3 centeredWorldPos = worldPos - cCameraPos;

        #ifdef DIRLIGHT
            oLightVec = float4(cLightDir, GetDepth(oPos));
        #elif defined(LIGHT)
            oLightVec = float4((cLightPos - centeredWorldPos) * cLightAtten, GetDepth(oPos));
        #else
            oLightVec = float4(0.0, 0.0, 0.0, GetDepth(oPos));
        #endif
    
        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            GetShadowPos(worldPos, oShadowPos);
        #endif
    
        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            float4 projWorldPos = float4(worldPos, 1.0);
            oSpotPos = mul(projWorldPos, cSpotProj);
        #endif

        #ifdef POINTLIGHT
            oCubeMaskVec = mul(oLightVec.xyz, cLightVecRot);
        #endif

        #ifdef NORMALMAP
            oTangent = GetWorldTangent(modelMatrix);
            oBitangent = cross(oTangent, oNormal) * iTangent.w;
            float3x3 tbn = float3x3(oTangent, oBitangent, oNormal);
            #ifdef LIGHT
                oLightVec.xyz = mul(tbn, oLightVec.xyz);
            #endif
            #ifdef SPECULAR
                oEyeVec = mul(tbn, -centeredWorldPos);
            #endif
        #elif defined(SPECULAR)
            oEyeVec = -centeredWorldPos;
        #endif

    #else

        oLightVec = float4(0.0, 0.0, 0.0, GetDepth(oPos));

    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    float4 iLightVec : TEXCOORD1,
    #ifndef NORMALMAP
        float3 iNormal : TEXCOORD2,
    #endif
    #ifdef SPECULAR
        float3 iEyeVec : TEXCOORD3,
    #endif
    #ifdef SHADOW
        #if defined(DIRLIGHT)
            float4 iShadowPos[4] : TEXCOORD4,
        #elif defined(SPOTLIGHT)
            float4 iShadowPos : TEXCOORD4,
        #else
            float3 iShadowPos : TEXCOORD4,
        #endif
    #endif
    #ifdef SPOTLIGHT
        float4 iSpotPos : TEXCOORD5,
    #endif
    #ifdef CUBEMASK
        float3 iCubeMaskVec : TEXCOORD5,
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

    float3 finalColor = 0.0;

    #if !defined(VOLUMETRIC) && defined(LIGHT)

        float3 lightColor;
        float3 lightDir;
        float diff;

        #ifdef NORMALMAP
            float3 normal = DecodeNormal(tex2D(sNormalMap, iTexCoord));
        #else
            float3 normal = normalize(iNormal);
        #endif

        #ifdef DIRLIGHT
            #ifdef NORMALMAP
                lightDir = normalize(iLightVec.xyz);
            #else
                lightDir = iLightVec.xyz;
            #endif
            diff = GetDiffuseDir(normal, lightDir);
        #else
            diff = GetDiffusePointOrSpot(normal, iLightVec.xyz, lightDir);
        #endif

        #ifdef SHADOW
            #if defined(DIRLIGHT)
                float4 shadowPos = GetDirShadowPos(iShadowPos, iLightVec.w);
                diff *= saturate(GetShadow(shadowPos) + GetShadowFade(iLightVec.w));
            #elif defined(SPOTLIGHT)
                diff *= GetShadow(iShadowPos);
            #else
                diff *= GetCubeShadow(iShadowPos);
            #endif
        #endif

        #if defined(SPOTLIGHT)
            lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #elif defined(CUBEMASK)
            lightColor = texCUBE(sLightCubeMap, iCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif

        #ifdef SPECULAR
            #ifdef SPECMAP
                float specStrength = cMatSpecProperties.x * tex2D(sSpecMap, iTexCoord).g;
            #else
                float specStrength = cMatSpecProperties.x;
            #endif
            float spec = GetSpecular(normal, iEyeVec, lightDir, cMatSpecProperties.y);
            finalColor = diff * lightColor * (diffColor.rgb + spec * specStrength * cLightColor.a);
        #else
            finalColor = diff * lightColor * diffColor.rgb;
        #endif

    #elif defined(VOLUMETRIC) && defined(LIGHT)

        float3 lightColor;
        float diff;

        #ifdef DIRLIGHT
            diff = GetDiffuseDirVolumetric();
        #else
            diff = GetDiffusePointOrSpotVolumetric(iLightVec.xyz);
        #endif

        #if defined(SPOTLIGHT)
            lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #elif defined(CUBEMASK)
            lightColor = texCUBE(sLightCubeMap, iCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif

        finalColor = diff * lightColor * diffColor.rgb;

    #elif defined(UNLIT)

        finalColor = diffColor.rgb;

    #endif

    #ifdef AMBIENT
        finalColor += cAmbientColor * diffColor.rgb;
    #endif

    #if defined(LIGHT) && !defined(AMBIENT)
        oColor = float4(GetLitFog(finalColor, iLightVec.w), diffColor.a);
    #else
        oColor = float4(GetFog(finalColor, iLightVec.w), diffColor.a);
    #endif
}
