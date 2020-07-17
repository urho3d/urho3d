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

// D3D9 uniforms
uniform float cWaterMetallic;
uniform float cWaterRoughness;
uniform float cWaterFlowSpeed;
uniform float cWaterTimeScale;
uniform float cWaterFresnelPower;
#else

// D3D11 constant buffer
cbuffer CustomVS : register(b6)
{
    float cWaterMetallic;
    float cWaterRoughness;
    float cWaterFlowSpeed;
    float cWaterTimeScale;
    float cWaterFresnelPower;
}

#endif


void VS(float4 iPos : POSITION,
    #if !defined(BILLBOARD) && !defined(TRAILFACECAM)
        float3 iNormal : NORMAL,
    #endif
    #ifndef NOUV
        float2 iTexCoord : TEXCOORD0,
    #endif
    #ifdef VERTEXCOLOR
        float4 iColor : COLOR0,
    #endif
    #if defined(LIGHTMAP)
        float2 iTexCoord2 : TEXCOORD1,
    #endif
    #if (defined(NORMALMAP) || defined(TRAILFACECAM) || defined(TRAILBONE)) && !defined(BILLBOARD) && !defined(DIRBILLBOARD)
        float4 iTangent : TANGENT,
    #endif
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
    #ifndef NORMALMAP
        out float2 oTexCoord : TEXCOORD0,
    #else
        out float4 oTexCoord : TEXCOORD0,
        out float4 oTangent : TEXCOORD3,
    #endif
    out float3 oNormal : TEXCOORD1,
    out float4 oWorldPos : TEXCOORD2,
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
        #if defined(LIGHTMAP)
            out float2 oTexCoord2 : TEXCOORD7,
        #endif
    #endif
        #ifdef VERTEXCOLOR
        out float4 oColor : COLOR0,
    #endif
    out float4 oEyeVec : TEXCOORD6,
    #if defined(D3D11) && defined(CLIPPLANE)
        out float oClip : SV_CLIPDISTANCE0,
    #endif
    out float4 oPos : OUTPOSITION)
{
    // Define a 0,0 UV coord if not expected from the vertex data
    #ifdef NOUV
        const float2 iTexCoord = float2(0.0, 0.0);
    #endif

    const float4x3 modelMatrix = iModelMatrix;
    const float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oNormal = GetWorldNormal(modelMatrix);
    oWorldPos = float4(worldPos, GetDepth(oPos));
    oEyeVec = float4(cCameraPos - worldPos, GetDepth(oPos));

    #if defined(D3D11) && defined(CLIPPLANE)
        oClip = dot(oPos, cClipPlane);
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif

    #if defined(NORMALMAP)
        const float4 tangent = GetWorldTangent(modelMatrix);
        const float3 bitangent = cross(tangent.xyz, oNormal) * tangent.w;
        oTexCoord = float4(GetTexCoord(iTexCoord), bitangent.xy);
        oTangent = float4(tangent.xyz, bitangent.z);
    #else
        oTexCoord = GetTexCoord(iTexCoord);
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
        // Ambient & per-vertex lighting
        #if defined(LIGHTMAP)
            // If using lightmap, disregard zone ambient light
            oVertexLight = float3(0.0, 0.0, 0.0);
            oTexCoord2 = iTexCoord2;
        #elif defined(AO)
            // If using AO, calculate ambient in the PS
            oVertexLight = float3(0.0, 0.0, 0.0);
        #else
            oVertexLight = GetAmbient(GetZonePos(worldPos));
        #endif

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                oVertexLight += GetVertexLight(i, worldPos, oNormal) * cVertexLights[i * 3].rgb;
        #endif

        oScreenPos = GetScreenPos(oPos);
    #endif
}

void PS(
    #ifndef NORMALMAP
        float2 iTexCoord : TEXCOORD0,
    #else
        float4 iTexCoord : TEXCOORD0,
        float4 iTangent : TEXCOORD3,
    #endif
    float3 iNormal : TEXCOORD1,
    float4 iWorldPos : TEXCOORD2,
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
        #if defined(LIGHTMAP)
            float2 iTexCoord2 : TEXCOORD7,
        #endif
    #endif
    float4 vEyeVec : TEXCOORD6,
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
    // Flow direction is stored in Red and Green channels of the vertex color
    const float2 flowDir = (float2(iColor.x, 1.0 - iColor.y) - float2(0.5, 0.5)) * cWaterFlowSpeed;
    // Calculate sampling points based on reminder of the time value
    const float2 baseUV = iTexCoord.xy;
    const float timeFactor = cElapsedTimePS * cWaterTimeScale - floor(cElapsedTimePS * cWaterTimeScale);
    const float2 uv0 = baseUV + (flowDir * timeFactor);
    const float2 uv1 = baseUV + (flowDir * (timeFactor - 1.0));

    #ifdef DIFFMAP
        // Sample diffuse overlay (foam, debree, leaves, etc.)
        const float4 overlay0 = Sample2D(DiffMap, uv0);
        const float4 overlay1 = Sample2D(DiffMap, uv1);
        const float4 overlay = lerp(overlay0, overlay1, timeFactor);
    #else
    const float4 overlay = float4(0.0, 0.0, 0.0, 0.0);
    #endif

    // Blend factor between water and diffuse overlay 
    #ifdef ALPHAMASK
        const float overlayFactor = ((overlay.a < 0.5)?0.0:overlay.a) * iColor.b;
    #else
        const float overlayFactor = overlay.a * iColor.b;
    #endif

    // Get normal
    #if defined(NORMALMAP)
        const float3 tangent = normalize(iTangent.xyz);
        const float3 bitangent = normalize(float3(iTexCoord.zw, iTangent.w));
        const float3x3 tbn = float3x3(tangent, bitangent, iNormal);
    #endif

    #ifdef NORMALMAP
        //float normalScale = length(flowDir)*2.0;
        const float3 nnA = DecodeNormal(Sample2D(NormalMap, uv0));
        const float3 nnB = DecodeNormal(Sample2D(NormalMap, uv1));
        const float3 nn = lerp(nnA, nnB, timeFactor);// * float3(normalScale, normalScale, 1.0);
        //nn.rg *= 2.0;
        const float3 normal = normalize(mul(nn, tbn));
    #else
        const float3 normal = normalize(iNormal);
    #endif

    const float fresnel = pow(1.0 - clamp(dot(normalize(vEyeVec.xyz), iNormal), 0.0, 1.0), cWaterFresnelPower);

    // Do the alpha blending of diffuse overlay
    float4 diffColor = lerp(cMatDiffColor, overlay, overlay.a);
    // Blue vertex color controls intencity of diffuse overlay over the water material
    diffColor = lerp(cMatDiffColor, diffColor, iColor.b);
    diffColor.a = lerp(max(cMatDiffColor.a, diffColor.a), 1.0, fresnel) * iColor.a;

    // Get material specular albedo
    #ifdef METALLIC // METALNESS
        float4 roughMetalSrc = Sample2D(RoughMetalFresnel, iTexCoord.xy);

        float roughness = roughMetalSrc.r + cRoughness;
        float metalness = roughMetalSrc.g + cMetallic;
    #else
        float roughness = cRoughness;
        float metalness = cMetallic;
    #endif

    metalness = lerp(cWaterMetallic, metalness, overlayFactor);
    roughness = lerp(cWaterRoughness, roughness, overlayFactor);

    roughness *= roughness;

    roughness = clamp(roughness, ROUGHNESS_FLOOR, 1.0);
    metalness = clamp(metalness, METALNESS_FLOOR, 1.0);

    float3 specColor = lerp(0.08 * cMatSpecColor.rgb, diffColor.rgb, metalness);
    diffColor.rgb = diffColor.rgb - diffColor.rgb * metalness; // Modulate down the diffuse

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
        float3 ambientOcclusion = float3(1.0, 1.0, 1.0);
        #ifdef AO
            // If using AO, the vertex light ambient is black, calculate occluded ambient here
            ambientOcclusion = Sample2D(EmissiveMap, iTexCoord2).rgb;
            finalColor += ambientOcclusion * cAmbientColor.rgb * diffColor.rgb;
        #endif

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
            const float gamma = 0;
            finalColor += iblColor * ambientOcclusion;
        #endif

        #ifdef LIGHTMAP
            finalColor += Sample2D(EmissiveMap, iTexCoord2).rgb * diffColor.rgb;
        #endif
        #ifdef EMISSIVEMAP
            finalColor += cMatEmissiveColor * Sample2D(EmissiveMap, iTexCoord.xy).rgb;
        #else
            finalColor += cMatEmissiveColor;
        #endif

        oColor = float4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
