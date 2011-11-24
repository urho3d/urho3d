#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,
    float3 iNormal : NORMAL,
    float2 iTexCoord : TEXCOORD0,
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
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
    out float3 oLightVec : TEXCOORD1,
    out float2 oZonePosDepth : TEXCOORD2,
    #ifdef SPOTLIGHT
        out float4 oSpotPos : TEXCOORD3,
    #endif
    #ifdef POINTLIGHT
        out float3 oCubeMaskVec : TEXCOORD3,
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

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif

    float4 projWorldPos = float4(worldPos, 1.0);

    #ifdef DIRLIGHT
        oLightVec = cLightDir;
    #else
        oLightVec = (cLightPos.xyz - worldPos) * cLightPos.w;
    #endif

    oZonePosDepth = float2(GetZonePos(worldPos), GetDepth(oPos));

    #ifdef SPOTLIGHT
        // Spotlight projection: transform from world space to projector texture coordinates
        oSpotPos = mul(projWorldPos, cSpotProj);
    #endif

    #ifdef POINTLIGHT
        oCubeMaskVec = mul(oLightVec, cLightVecRot);
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    float3 iLightVec : TEXCOORD1,
    float2 iZonePosDepth : TEXCOORD2,
    #ifdef SPOTLIGHT
        float4 iSpotPos : TEXCOORD3,
    #endif
    #ifdef CUBEMASK
        float3 iCubeMaskVec : TEXCOORD3,
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

    float3 lightColor;
    float3 finalColor;
    float diff;

    #ifdef DIRLIGHT
        diff = GetDiffuseDirVolumetric();
    #else
        diff = GetDiffusePointOrSpotVolumetric(iLightVec);
    #endif

    #if defined(SPOTLIGHT)
        lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
    #elif defined(CUBEMASK)
        lightColor = texCUBE(sLightCubeMap, iCubeMaskVec).rgb * cLightColor.rgb;
    #else
        lightColor = cLightColor.rgb;
    #endif

    finalColor = diff * lightColor * diffColor.rgb;

    #ifdef AMBIENT
        finalColor += GetAmbient(iZonePosDepth.x) * diffColor.rgb;
        oColor = float4(GetFog(finalColor, iZonePosDepth.y), diffColor.a);
    #else
        oColor = float4(GetLitFog(finalColor, iZonePosDepth.y), diffColor.a);
    #endif
}
