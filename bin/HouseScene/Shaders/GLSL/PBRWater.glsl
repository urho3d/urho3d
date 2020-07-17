#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"
#include "Constants.glsl"
#include "Fog.glsl"
#include "PBR.glsl"
#include "IBL.glsl"
#line 30011

uniform float cWaterMetallic;
uniform float cWaterRoughness;
uniform float cWaterFlowSpeed;
uniform float cWaterTimeScale;
uniform float cWaterFresnelPower;
#ifndef GL_ES
varying vec4 vEyeVec;
#else
varying highp vec4 vEyeVec;
#endif

#if defined(NORMALMAP)
    varying vec4 vTexCoord;
    varying vec4 vTangent;
#else
    varying vec2 vTexCoord;
#endif
varying vec3 vNormal;
varying vec4 vWorldPos;
    varying vec4 vColor;
#ifdef PERPIXEL
    #ifdef SHADOW
        #ifndef GL_ES
            varying vec4 vShadowPos[NUMCASCADES];
        #else
            varying highp vec4 vShadowPos[NUMCASCADES];
        #endif
    #endif
    #ifdef SPOTLIGHT
        varying vec4 vSpotPos;
    #endif
    #ifdef POINTLIGHT
        varying vec3 vCubeMaskVec;
    #endif
#else
    varying vec3 vVertexLight;
    varying vec4 vScreenPos;
    #ifdef ENVCUBEMAP
        varying vec3 vReflectionVec;
    #endif
    #if defined(LIGHTMAP) || defined(AO)
        varying vec2 vTexCoord2;
    #endif
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vNormal = GetWorldNormal(modelMatrix);
    vWorldPos = vec4(worldPos, GetDepth(gl_Position));
    vEyeVec = vec4(cCameraPos - worldPos, GetDepth(gl_Position));

    vColor = iColor;

    #if defined(NORMALMAP) || defined(DIRBILLBOARD)
        vec4 tangent = GetWorldTangent(modelMatrix);
        vec3 bitangent = cross(tangent.xyz, vNormal) * tangent.w;
        vTexCoord = vec4(GetTexCoord(iTexCoord), bitangent.xy);
        vTangent = vec4(tangent.xyz, bitangent.z);
    #else
        vTexCoord = GetTexCoord(iTexCoord);
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        vec4 projWorldPos = vec4(worldPos, 1.0);

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            for (int i = 0; i < NUMCASCADES; i++)
                vShadowPos[i] = GetShadowPos(i, vNormal, projWorldPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            vSpotPos = projWorldPos * cLightMatrices[0];
        #endif

        #ifdef POINTLIGHT
            vCubeMaskVec = (worldPos - cLightPos.xyz) * mat3(cLightMatrices[0][0].xyz, cLightMatrices[0][1].xyz, cLightMatrices[0][2].xyz);
        #endif
    #else
        // Ambient & per-vertex lighting
        #if defined(LIGHTMAP) || defined(AO)
            // If using lightmap, disregard zone ambient light
            // If using AO, calculate ambient in the PS
            vVertexLight = vec3(0.0, 0.0, 0.0);
            #if defined(LIGHTMAP)
                vTexCoord2 = iTexCoord1;
            #else
                vTexCoord2 = GetTexCoord(iTexCoord);
            #endif
        #else
            vVertexLight = GetAmbient(GetZonePos(worldPos));
        #endif

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                vVertexLight += GetVertexLight(i, worldPos, vNormal) * cVertexLights[i * 3].rgb;
        #endif

        vScreenPos = GetScreenPos(gl_Position);

        #ifdef ENVCUBEMAP
            vReflectionVec = worldPos - cCameraPos;
        #endif
    #endif
}

void PS()
{
    // Flow direction is stored in Red and Green channels of the vertex color
    vec2 flowDir = (vec2(vColor.x, 1.0 - vColor.y) - vec2(0.5, 0.5)) * cWaterFlowSpeed;
    // Calculate sampling points based on reminder of the time value
    vec2 baseUV = vTexCoord.xy;
    float timeFactor = cElapsedTimePS * cWaterTimeScale - floor(cElapsedTimePS * cWaterTimeScale);
    vec2 uv0 = baseUV + (flowDir * timeFactor);
    vec2 uv1 = baseUV + (flowDir * (timeFactor - 1.0));

    #ifdef DIFFMAP
        // Sample diffuse overlay (foam, debree, leaves, etc.)
        vec4 overlay0 = texture2D(sDiffMap, uv0);
        vec4 overlay1 = texture2D(sDiffMap, uv1);
        vec4 overlay = mix(overlay0, overlay1, timeFactor);
    #else
        vec4 overlay = vec4(0.0, 0.0, 0.0, 0.0);
    #endif

    // Blend factor between water and diffuse overlay 
    #ifdef ALPHAMASK
        float overlayFactor = ((overlay.a < 0.5)?0.0:overlay.a) * vColor.z;
    #else
        float overlayFactor = overlay.a * vColor.z;
    #endif

    // Get normal
    #if defined(NORMALMAP) || defined(DIRBILLBOARD)
        vec3 tangent = vTangent.xyz;
        vec3 bitangent = vec3(vTexCoord.zw, vTangent.w);
        mat3 tbn = mat3(tangent, bitangent, vNormal);
    #endif

    #ifdef NORMALMAP
        //float normalScale = length(flowDir)*2.0;
        vec3 nnA = DecodeNormal(texture2D(sNormalMap, uv0));
        vec3 nnB = DecodeNormal(texture2D(sNormalMap, uv1));
        vec3 nn = mix(nnA, nnB, timeFactor);// * vec3(normalScale, normalScale, 1.0);
        //nn.rg *= 2.0;
        vec3 normal = normalize(tbn * nn);
    #else
        vec3 normal = normalize(vNormal);
    #endif

    float fresnel = pow(1.0 - clamp(dot(normalize(vEyeVec.xyz), vNormal), 0.0, 1.0), cWaterFresnelPower);

    // Do the alpha blending of diffuse overlay
    vec4 diffColor = mix(cMatDiffColor, overlay, overlay.a);
    // Blue vertex color controls intencity of diffuse overlay over the water material
    diffColor = mix(cMatDiffColor, diffColor, vColor.z);
    diffColor.a = mix(max(cMatDiffColor.a, diffColor.a), 1.0, fresnel) * vColor.a;

    #ifdef METALLIC
        vec4 roughMetalSrc = texture2D(sSpecMap, vTexCoord.xy);

        float roughness = roughMetalSrc.r + cRoughness;
        float metalness = roughMetalSrc.g + cMetallic;
    #else
        float roughness = cRoughness;
        float metalness = cMetallic;
    #endif

    metalness = mix (cWaterMetallic, metalness, overlayFactor);
    roughness = mix (cWaterRoughness, roughness, overlayFactor);

    roughness *= roughness;

    roughness = clamp(roughness, ROUGHNESS_FLOOR, 1.0);
    metalness = clamp(metalness, METALNESS_FLOOR, 1.0);

    vec3 specColor = mix(0.08 * cMatSpecColor.rgb, diffColor.rgb, metalness);
    diffColor.rgb = diffColor.rgb - diffColor.rgb * metalness;

    // Get fog factor
    #ifdef HEIGHTFOG
        float fogFactor = GetHeightFogFactor(vWorldPos.w, vWorldPos.y);
    #else
        float fogFactor = GetFogFactor(vWorldPos.w);
    #endif

    #if defined(PERPIXEL)
        // Per-pixel forward lighting
        vec3 lightColor;
        vec3 lightDir;
        vec3 finalColor;

        float atten = 1;

        #if defined(DIRLIGHT)
            atten = GetAtten(normal, vWorldPos.xyz, lightDir);
        #elif defined(SPOTLIGHT)
            atten = GetAttenSpot(normal, vWorldPos.xyz, lightDir);
        #else
            atten = GetAttenPoint(normal, vWorldPos.xyz, lightDir);
        #endif

        float shadow = 1.0;
        #ifdef SHADOW
            shadow = GetShadow(vShadowPos, vWorldPos.w);
        #endif

        #if defined(SPOTLIGHT)
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #elif defined(CUBEMASK)
            lightColor = textureCube(sLightCubeMap, vCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
        vec3 toCamera = normalize(cCameraPosPS - vWorldPos.xyz);
        vec3 lightVec = normalize(lightDir);
        float ndl = clamp((dot(normal, lightVec)), M_EPSILON, 1.0);

        vec3 BRDF = GetBRDF(vWorldPos.xyz, lightDir, lightVec, toCamera, normal, roughness, diffColor.rgb, specColor);

        finalColor.rgb = BRDF * lightColor * (atten * shadow) / M_PI;

        #ifdef AMBIENT
            finalColor += cAmbientColor.rgb * diffColor.rgb;
            finalColor += cMatEmissiveColor;
            gl_FragColor = vec4(GetFog(finalColor, fogFactor), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, fogFactor), diffColor.a);
        #endif
    #elif defined(DEFERRED)
        // Fill deferred G-buffer
        const vec3 spareData = vec3(0,0,0); // Can be used to pass more data to deferred renderer
        gl_FragData[0] = vec4(specColor, spareData.r);
        gl_FragData[1] = vec4(diffColor.rgb, spareData.g);
        gl_FragData[2] = vec4(normal * roughness, spareData.b);
        gl_FragData[3] = vec4(EncodeDepth(vWorldPos.w), 0.0);
    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight * diffColor.rgb;
        vec3 ambientOcclusion = vec3(1.0, 1.0, 1.0);
        #ifdef AO
            // If using AO, the vertex light ambient is black, calculate occluded ambient here
            ambientOcclusion = texture2D(sEmissiveMap, vTexCoord2).rgb;
            finalColor += ambientOcclusion * cAmbientColor.rgb * diffColor.rgb;
        #endif

        #ifdef MATERIAL
            // Add light pre-pass accumulation result
            // Lights are accumulated at half intensity. Bring back to full intensity now
            vec4 lightInput = 2.0 * texture2DProj(sLightBuffer, vScreenPos);
            vec3 lightSpecColor = lightInput.a * lightInput.rgb / max(GetIntensity(lightInput.rgb), 0.001);

            finalColor += lightInput.rgb * diffColor.rgb + lightSpecColor * specColor;
        #endif

        vec3 toCamera = normalize(vWorldPos.xyz - cCameraPosPS);
        vec3 reflection = normalize(reflect(toCamera, normal));

        vec3 cubeColor = vVertexLight.rgb;

        #ifdef IBL
          vec3 iblColor = ImageBasedLighting(reflection, normal, toCamera, diffColor.rgb, specColor.rgb, roughness, cubeColor);
          float gamma = 0.0;
          finalColor.rgb += iblColor * ambientOcclusion * fresnel;
        #endif

        #ifdef ENVCUBEMAP
            finalColor += cMatEnvMapColor * textureCube(sEnvCubeMap, reflect(vReflectionVec, normal)).rgb;
        #endif
        #ifdef LIGHTMAP
            finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * diffColor.rgb;
        #endif
        #ifdef EMISSIVEMAP
            finalColor += cMatEmissiveColor * texture2D(sEmissiveMap, vTexCoord.xy).rgb;
        #else
            finalColor += cMatEmissiveColor;
        #endif

        gl_FragColor = vec4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
