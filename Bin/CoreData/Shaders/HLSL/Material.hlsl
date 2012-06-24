#pragma warning(disable:3557)

#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,   
    #ifdef NUMVERTEXLIGHTS
        float3 iNormal : NORMAL,
    #endif
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
    float2 iTexCoord : TEXCOORD0,
    out float2 oTexCoord : TEXCOORD0,
    out float4 oVertexLighting : TEXCOORD1,
    out float4 oScreenPos : TEXCOORD2,
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetTexCoord(iTexCoord);
    oScreenPos = GetScreenPos(oPos);

    oVertexLighting = float4(GetAmbient(GetZonePos(worldPos)), GetDepth(oPos));
    #ifdef NUMVERTEXLIGHTS
    float3 normal = GetWorldNormal(modelMatrix);
    for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
        oVertexLighting.rgb += GetVertexLight(i, worldPos, normal) * cVertexLights[i * 3].rgb;
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    float4 iVertexLighting : TEXCOORD1,
    float4 iScreenPos : TEXCOORD2,
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffInput = tex2D(sDiffMap, iTexCoord);
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
        float3 diffColor = cMatDiffColor.rgb * diffInput.rgb;
    #else
        float3 diffColor = cMatDiffColor.rgb;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= iColor.rgb;
    #endif

    #ifdef SPECMAP
        float3 specColor = cMatSpecColor.rgb * tex2D(sSpecMap, iTexCoord).g;
    #else
        float3 specColor = cMatSpecColor.rgb;
    #endif

    // Lights are accumulated at half intensity. Bring back to full intensity now
    float4 lightInput = 2.0 * tex2Dproj(sLightBuffer, iScreenPos);
    float3 lightSpecColor = lightInput.a * (lightInput.rgb / GetIntensity(lightInput.rgb));

    float3 finalColor = (iVertexLighting.rgb + lightInput.rgb) * diffColor + lightSpecColor * specColor;
    oColor = float4(GetFog(finalColor, iVertexLighting.a), 1.0);
}
