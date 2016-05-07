#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Lighting.hlsl"
#include "Constants.hlsl"
#include "Fog.hlsl"
#include "BDRF.hlsl"
#include "IBL.hlsl"

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
    #if defined(LIGHTMAP) || defined(AO)
        float2 iTexCoord2 : TEXCOORD1,
    #endif
    #if defined(NORMALMAP) || defined(DIRBILLBOARD) || defined(IBL)
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
    #if defined(NORMALMAP) || defined(DIRBILLBOARD) || defined(IBL)
        out float4 oTexCoord : TEXCOORD0,
        out float4 oTangent : TEXCOORD3,
    #else
        out float2 oTexCoord : TEXCOORD0,
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
        #ifdef ENVCUBEMAP
            out float3 oReflectionVec : TEXCOORD6,
        #endif
        #if defined(LIGHTMAP) || defined(AO)
            out float2 oTexCoord2 : TEXCOORD7,
        #endif
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
        const float2 iTexCoord = float2(0.0, 0.0);
    #endif

    const float4x3 modelMatrix = iModelMatrix;
    const float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oNormal = GetWorldNormal(modelMatrix);
    oWorldPos = float4(worldPos, GetDepth(oPos));

    #if defined(D3D11) && defined(CLIPPLANE)
        oClip = dot(oPos, cClipPlane);
    #endif

    #ifdef VERTEXCOLOR
        oColor = iColor;
    #endif

    #if defined(NORMALMAP) || defined(DIRBILLBOARD) || defined(IBL)
        const float3 tangent = GetWorldTangent(modelMatrix);
        const float3 bitangent = cross(tangent, oNormal) * iTangent.w;
        oTexCoord = float4(GetTexCoord(iTexCoord), bitangent.xy);
        oTangent = float4(tangent, bitangent.z);
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
        #if defined(LIGHTMAP) || defined(AO)
            // If using lightmap, disregard zone ambient light
            // If using AO, calculate ambient in the PS
            oVertexLight = float3(0.0, 0.0, 0.0);
            oTexCoord2 = iTexCoord2;
        #else
            oVertexLight = GetAmbient(GetZonePos(worldPos));
        #endif

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                oVertexLight += GetVertexLight(i, worldPos, oNormal) * cVertexLights[i * 3].rgb;
        #endif

        oScreenPos = GetScreenPos(oPos);

        #ifdef ENVCUBEMAP
            oReflectionVec = worldPos - cCameraPos;
        #endif
    #endif
}

void PS(
    #if defined(NORMALMAP) || defined(DIRBILLBOARD) || defined(IBL)
        float4 iTexCoord : TEXCOORD0,
        float4 iTangent : TEXCOORD3,
    #else
        float2 iTexCoord : TEXCOORD0,
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
        #ifdef ENVCUBEMAP
            float3 iReflectionVec : TEXCOORD6,
        #endif
        #if defined(LIGHTMAP) || defined(AO)
            float2 iTexCoord2 : TEXCOORD7,
        #endif
    #endif
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
    // Get material diffuse albedo
    #ifdef DIFFMAP
        const float4 diffInput = Sample2D(DiffMap, iTexCoord.xy);
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

    // Get material specular albedo
    #ifdef METALLIC // METALNESS
        const float4 roughMetalSrc = Sample2D(RoughMetalFresnel, iTexCoord.xy);

        const float roughness = clamp(pow(roughMetalSrc.r + cRoughnessPS, 2.0), ROUGHNESS_FLOOR, 1.0);
        const float metalness = clamp(roughMetalSrc.g + cMetallicPS, METALNESS_FLOOR, 1.0);
    #else
        const float roughness = clamp(pow(cRoughnessPS, 2.0), ROUGHNESS_FLOOR, 1.0);
        const float metalness = clamp(cMetallicPS, METALNESS_FLOOR, 1.0);
    #endif

    float3 specColor = lerp(0.08 * cMatSpecColor.rgb, diffColor.rgb, metalness);
    specColor *= cMatSpecColor.rgb;
    diffColor.rgb = diffColor.rgb - diffColor.rgb * metalness; // Modulate down the diffuse

    // Get normal
    #if defined(NORMALMAP) || defined(DIRBILLBOARD) || defined(IBL)
        const float3 tangent = normalize(iTangent.xyz);
        const float3 bitangent = normalize(float3(iTexCoord.zw, iTangent.w));
        const float3x3 tbn = float3x3(tangent, bitangent, iNormal);
    #endif

    #ifdef NORMALMAP
        const float3 nn = DecodeNormal(Sample2D(NormalMap, iTexCoord.xy));
        //nn.rg *= 2.0;
        const float3 normal = normalize(mul(nn, tbn));
    #else
        const float3 normal = normalize(iNormal);
    #endif

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

        float diff = GetDiffuse(normal, iWorldPos.xyz, lightDir);

        #ifdef SHADOW
            diff *= GetShadow(iShadowPos, iWorldPos.w);
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

        const float3 Hn = normalize(toCamera + lightDir);
        const float vdh = clamp(abs(dot(toCamera, Hn)), M_EPSILON, 1.0);
        const float ndh = clamp(abs(dot(normal, Hn)), M_EPSILON, 1.0);
        const float ndl = clamp(abs(dot(normal, lightVec)), M_EPSILON, 1.0);
        const float ndv = clamp(abs(dot(normal, toCamera)), M_EPSILON, 1.0);

        const float3 diffuseFactor = BurleyDiffuse(diffColor.rgb, roughness, ndv, ndl, vdh);
        float3 specularFactor = 0;

        #ifdef SPECULAR
            const float3 fresnelTerm = Fresnel(specColor, vdh) ;
            const float distTerm = Distribution(ndh, roughness);
            const float visTerm = Visibility(ndl, ndv, roughness);

            specularFactor = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv);
        #endif

        finalColor.rgb = (diffuseFactor + specularFactor) * lightColor * diff;

        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
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
        #ifdef AO
            // If using AO, the vertex light ambient is black, calculate occluded ambient here
            finalColor += Sample2D(EmissiveMap, iTexCoord2).rgb * cAmbientColor * diffColor.rgb;
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
            const float3 iblColor = ImageBasedLighting(reflection, tangent, bitangent, normal, toCamera, diffColor, specColor, roughness, cubeColor);
            const float gamma = 0;
            finalColor += iblColor * (cubeColor + gamma);
        #endif

        #ifdef ENVCUBEMAP
            finalColor += cMatEnvMapColor * SampleCube(EnvCubeMap, reflect(iReflectionVec, normal)).rgb;
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
