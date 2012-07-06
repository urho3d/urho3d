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
    #if PERPIXEL
        out float4 oLightVec : TEXCOORD1,
        #ifdef SPOTLIGHT
            out float4 oSpotPos : TEXCOORD2,
        #endif
        #ifdef POINTLIGHT
            out float3 oCubeMaskVec : TEXCOORD2,
        #endif
    #else
        out float4 oVertexLight : TEXCOORD1,
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

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        float4 projWorldPos = float4(worldPos, 1.0);
    
        #ifdef DIRLIGHT
            oLightVec = float4(cLightDir, GetDepth(oPos));
        #else
            oLightVec = float4((cLightPos.xyz - worldPos) * cLightPos.w, GetDepth(oPos));
        #endif
    
        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            oSpotPos = mul(projWorldPos, cLightMatrices[0]);
        #endif
    
        #ifdef POINTLIGHT
            oCubeMaskVec = mul(oLightVec.xyz, (float3x3)cLightMatrices[0]);
        #endif
    #else
        // Ambient & per-vertex lighting
        oVertexLight = float4(GetAmbient(GetZonePos(worldPos)), GetDepth(oPos));

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                oVertexLight.rgb += GetVertexLightVolumetric(i, worldPos) * cVertexLights[i * 3].rgb;
        #endif
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    #ifdef PERPIXEL
        float4 iLightVec : TEXCOORD1,
        #ifdef SPOTLIGHT
            float4 iSpotPos : TEXCOORD2,
        #endif
        #ifdef CUBEMASK
            float3 iCubeMaskVec : TEXCOORD2,
        #endif
    #else
        float4 iVertexLight : TEXCOORD1,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oColor : COLOR0)
{
    // Get material diffuse albedo
    #ifdef DIFFMAP
        float4 diffInput = tex2D(sDiffMap, iTexCoord);
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
        float4 diffColor = cMatDiffColor * diffInput;
    #else
        float4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= iColor;
    #endif

    #if PERPIXEL
        // Per-pixel forward lighting
        float3 lightColor;
        float3 finalColor;
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
        oColor = float4(GetLitFog(finalColor, iLightVec.w), diffColor.a);
    #else
        // Ambient & per-vertex lighting
        float3 finalColor = iVertexLight.rgb * diffColor.rgb;
        oColor = float4(GetFog(finalColor, iVertexLight.a), diffColor.a);
    #endif
}
