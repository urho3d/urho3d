#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "Lighting.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,
    #ifndef BILLBOARD
        float3 iNormal : NORMAL,
    #endif
    #ifndef NOUV
        float2 iTexCoord : TEXCOORD0,
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
    #ifdef BILLBOARD
        float2 iSize : TEXCOORD1,
    #endif
    out float2 oTexCoord : TEXCOORD0,
    out float4 oWorldPos : TEXCOORD3,
    #if PERPIXEL
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
    #endif
    #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    #if defined(D3D11) && defined(CLIPPLANE)
        out float oClip : SV_CLIPDISTANCE0,
    #endif
    out float4 oPos : OUTPOSITION)
{
    // Define a 0,0 UV coord if not expected from the vertex data
    #ifdef NOUV
    float2 iTexCoord = float2(0.0, 0.0);
    #endif
    
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetTexCoord(iTexCoord);
    oWorldPos = float4(worldPos, GetDepth(oPos));

    #if defined(D3D11) && defined(CLIPPLANE)
        oClip = dot(oPos, cClipPlane);
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        float4 projWorldPos = float4(worldPos.xyz, 1.0);

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            GetShadowPos(projWorldPos, oShadowPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            oSpotPos = mul(projWorldPos, cLightMatrices[0]);
        #endif

        #ifdef POINTLIGHT
            oCubeMaskVec = mul(worldPos - cLightPos.xyz, (float3x3)cLightMatrices[0]);
        #endif
    #else
        // Ambient & per-vertex lighting
        oVertexLight = GetAmbient(GetZonePos(worldPos));

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                oVertexLight += GetVertexLightVolumetric(i, worldPos) * cVertexLights[i * 3].rgb;
        #endif
    #endif
}

void PS(float2 iTexCoord : TEXCOORD0,
    float4 iWorldPos : TEXCOORD3,
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
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #if defined(D3D11) && defined(CLIPPLANE)
        float iClip : SV_CLIPDISTANCE0,
    #endif
    out float4 oColor : OUTCOLOR0)
{
    // Get material diffuse albedo
    #ifdef DIFFMAP
        float4 diffInput = Sample2D(DiffMap, iTexCoord);
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

    // Get fog factor
    #ifdef HEIGHTFOG
        float fogFactor = GetHeightFogFactor(iWorldPos.w, iWorldPos.y);
    #else
        float fogFactor = GetFogFactor(iWorldPos.w);
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        float3 lightColor;
        float3 finalColor;
        
        float diff = GetDiffuseVolumetric(iWorldPos.xyz);

        #ifdef SHADOW
            diff *= GetShadow(iShadowPos, iWorldPos.w);
        #endif

        #if defined(SPOTLIGHT)
            lightColor = iSpotPos.w > 0.0 ? Sample2DProj(LightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #elif defined(CUBEMASK)
            lightColor = texCUBE(sLightCubeMap, iCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif

        finalColor = diff * lightColor * diffColor.rgb;
        oColor = float4(GetLitFog(finalColor, fogFactor), diffColor.a);
    #else
        // Ambient & per-vertex lighting
        float3 finalColor = iVertexLight * diffColor.rgb;

        oColor = float4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
