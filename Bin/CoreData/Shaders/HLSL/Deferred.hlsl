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
    out float2 oTexCoord : TEXCOORD0,
    out float4 oVertexLighting : TEXCOORD1,
    out float3 oNormal : TEXCOORD2,
    #ifdef NORMALMAP
        out float3 oTangent : TEXCOORD3,
        out float3 oBitangent : TEXCOORD4,
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

    oVertexLighting = float4(GetAmbient(GetZonePos(worldPos)), GetDepth(oPos));
    #ifdef NUMVERTEXLIGHTS
    float3 normal = GetWorldNormal(modelMatrix);
    for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
        oVertexLighting.rgb += GetVertexLight(i, worldPos, normal) * cVertexLights[i * 3].rgb;
    #endif

    oNormal = GetWorldNormal(modelMatrix);
    #ifdef NORMALMAP
        oTangent = GetWorldTangent(modelMatrix);
        oBitangent = cross(oTangent, oNormal) * iTangent.w;
    #endif
    
    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif
}

void PS(
    float2 iTexCoord : TEXCOORD0,
    float4 iVertexLighting : TEXCOORD1,
    float3 iNormal : TEXCOORD2,
    #ifdef NORMALMAP
        float3 iTangent : TEXCOORD3,
        float3 iBitangent : TEXCOORD4,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    out float4 oAlbedo : COLOR1,
    out float4 oNormal : COLOR2,
    #ifndef HWDEPTH
        out float4 oDepth : COLOR3,
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

    #ifdef NORMALMAP
        float3x3 tbn = float3x3(iTangent, iBitangent, iNormal);
        float3 normal = mul(DecodeNormal(tex2D(sNormalMap, iTexCoord)), tbn);
    #else
        float3 normal = iNormal;
    #endif
    
    // If using SM2, light volume shader may not have instructions left to normalize the normal. Therefore do it here
    #if !defined(SM3)
        normal = normalize(normal);
    #endif

    #ifdef SPECMAP
        float specIntensity = cMatSpecColor.g * tex2D(sSpecMap, iTexCoord).g;
    #else
        float specIntensity = cMatSpecColor.g;
    #endif

    float specPower = cMatSpecColor.a / 255.0;

    oColor = float4(GetFog(iVertexLighting.rgb * diffColor, iVertexLighting.a), 1.0);
    oAlbedo = GetFogFactor(iVertexLighting.a) * float4(diffColor, specIntensity);
    oNormal = float4(normal * 0.5 + 0.5, specPower);
    #ifndef HWDEPTH
        oDepth = iVertexLighting.a;
    #endif
}
