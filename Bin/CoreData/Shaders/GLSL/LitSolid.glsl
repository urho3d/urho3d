#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"
#include "Fog.glsl"

varying vec2 vTexCoord;
#ifdef HEIGHTFOG
    varying vec3 vWorldPos;
#endif
#ifdef PERPIXEL
    varying vec4 vLightVec;
    #ifdef SPECULAR
        varying vec3 vEyeVec;
    #endif
    #ifndef NORMALMAP
        varying vec3 vNormal;
    #endif
    #ifdef SHADOW
        varying vec4 vShadowPos[NUMCASCADES];
    #endif
    #ifdef SPOTLIGHT
        varying vec4 vSpotPos;
    #endif
    #ifdef POINTLIGHT
        varying vec3 vCubeMaskVec;
    #endif
#else
    varying vec4 vVertexLight;
    varying vec3 vNormal;
    #ifdef NORMALMAP
        varying vec3 vTangent;
        varying vec3 vBitangent;
    #endif
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
    vTexCoord = GetTexCoord(iTexCoord);
    
    #ifdef HEIGHTFOG
        vWorldPos = worldPos;
    #endif

    #if defined(PERPIXEL) && defined(NORMALMAP)
        vec3 vNormal;
        vec3 vTangent;
        vec3 vBitangent;
    #endif

    vNormal = GetWorldNormal(modelMatrix);
    #ifdef NORMALMAP
        vTangent = GetWorldTangent(modelMatrix);
        vBitangent = cross(vTangent, vNormal) * iTangent.w;
    #endif
    
    #ifdef PERPIXEL
        // Per-pixel forward lighting
        vec4 projWorldPos = vec4(worldPos, 1.0);

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            for (int i = 0; i < NUMCASCADES; i++)
                vShadowPos[i] = GetShadowPos(i, projWorldPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            vSpotPos = cLightMatrices[0] * projWorldPos;
        #endif
    
        #ifdef POINTLIGHT
            vCubeMaskVec = mat3(cLightMatrices[0][0].xyz, cLightMatrices[0][1].xyz, cLightMatrices[0][2].xyz) * (cLightPos.xyz - worldPos);
        #endif
    
        #ifdef NORMALMAP
            mat3 tbn = mat3(vTangent, vBitangent, vNormal);
            #ifdef DIRLIGHT
                vLightVec = vec4(cLightDir * tbn, GetDepth(gl_Position));
            #else
                vLightVec = vec4((cLightPos.xyz - worldPos) * tbn * cLightPos.w, GetDepth(gl_Position));
            #endif
            #ifdef SPECULAR
                vEyeVec = (cCameraPos - worldPos) * tbn;
            #endif
        #else
            #ifdef DIRLIGHT
                vLightVec = vec4(cLightDir, GetDepth(gl_Position));
            #else
                vLightVec = vec4((cLightPos.xyz - worldPos) * cLightPos.w, GetDepth(gl_Position));
            #endif
            #ifdef SPECULAR
                vEyeVec = cCameraPos - worldPos;
            #endif
        #endif
    #else
        // Ambient & per-vertex lighting
        #if defined(LIGHTMAP) || defined(AO)
            // If using lightmap, disregard zone ambient light
            // If using AO, calculate ambient in the PS
            vVertexLight = vec4(0.0, 0.0, 0.0, GetDepth(gl_Position));
            vTexCoord2 = iTexCoord2;
        #else
            vVertexLight = vec4(GetAmbient(GetZonePos(worldPos)), GetDepth(gl_Position));
        #endif
        
        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                vVertexLight.rgb += GetVertexLight(i, worldPos, vNormal) * cVertexLights[i * 3].rgb;
        #endif
        
        vScreenPos = GetScreenPos(gl_Position);

        #ifdef ENVCUBEMAP
            vReflectionVec = worldPos - cCameraPos;
        #endif
    #endif
}

void PS()
{
    // Get material diffuse albedo
    #ifdef DIFFMAP
        vec4 diffInput = texture2D(sDiffMap, vTexCoord);
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
        vec4 diffColor = cMatDiffColor * diffInput;
    #else
        vec4 diffColor = cMatDiffColor;
    #endif
    
    // Get material specular albedo
    #ifdef SPECMAP
        vec3 specColor = cMatSpecColor.rgb * texture2D(sSpecMap, vTexCoord).rgb;
    #else
        vec3 specColor = cMatSpecColor.rgb;
    #endif

    #if defined(PERPIXEL)
        // Per-pixel forward lighting
        vec3 lightColor;
        vec3 lightDir;
        vec3 finalColor;
        float diff;

        #ifdef NORMALMAP
            vec3 normal = DecodeNormal(texture2D(sNormalMap, vTexCoord));
        #else
            vec3 normal = normalize(vNormal);
        #endif
    
        diff = GetDiffuse(normal, vLightVec.xyz, lightDir);
    
        #ifdef SHADOW
            diff *= GetShadow(vShadowPos, vLightVec.w);
        #endif
    
        #if defined(SPOTLIGHT)
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #elif defined(CUBEMASK)
            lightColor = textureCube(sLightCubeMap, vCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
    
        #ifdef SPECULAR
            float spec = GetSpecular(normal, vEyeVec, lightDir, cMatSpecColor.a);
            finalColor = diff * lightColor * (diffColor.rgb + spec * specColor * cLightColor.a);
        #else
            finalColor = diff * lightColor * diffColor.rgb;
        #endif

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(vLightVec.w, vWorldPos.y);
        #else
            float fogFactor = GetFogFactor(vLightVec.w);
        #endif

        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            finalColor += cMatEmissiveColor;
            gl_FragColor = vec4(GetFog(finalColor, fogFactor), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, fogFactor), diffColor.a);
        #endif
    #elif defined(PREPASS)
        // Fill light pre-pass G-Buffer
        #ifdef NORMALMAP
            mat3 tbn = mat3(vTangent, vBitangent, vNormal);
            vec3 normal = tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord.xy));
        #else
            vec3 normal = vNormal;
        #endif

        float specPower = cMatSpecColor.a / 255.0;

        gl_FragData[0] = vec4(normal * 0.5 + 0.5, specPower);
        gl_FragData[1] = vec4(EncodeDepth(vVertexLight.a), 0.0);
    #elif defined(DEFERRED)
        // Fill deferred G-buffer
        #ifdef NORMALMAP
            mat3 tbn = mat3(vTangent, vBitangent, vNormal);
            vec3 normal = tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord));
        #else
            vec3 normal = vNormal;
        #endif

        float specIntensity = specColor.g;
        float specPower = cMatSpecColor.a / 255.0;

        vec3 finalColor = vVertexLight.rgb * diffColor.rgb;
        #ifdef AO
            // If using AO, the vertex light ambient is black, calculate occluded ambient here
            finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * cAmbientColor * diffColor.rgb;
        #endif

        #ifdef ENVCUBEMAP
            normal = normalize(normal);
            finalColor = cMatEnvMapColor * textureCube(sEnvCubeMap, reflect(vReflectionVec, normal)).rgb;
        #endif
        #ifdef LIGHTMAP
            finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * diffColor.rgb;
        #endif
        #ifdef EMISSIVEMAP
            finalColor += cMatEmissiveColor * texture2D(sEmissiveMap, vTexCoord).rgb;
        #else
            finalColor += cMatEmissiveColor;
        #endif

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(vVertexLight.a, vWorldPos.y);
        #else
            float fogFactor = GetFogFactor(vVertexLight.a);
        #endif

        gl_FragData[0] = vec4(GetFog(finalColor, fogFactor), 1.0);
        gl_FragData[1] = fogFactor * vec4(diffColor.rgb, specIntensity);
        gl_FragData[2] = vec4(normal * 0.5 + 0.5, specPower);
        gl_FragData[3] = vec4(EncodeDepth(vVertexLight.a), 0.0);


    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight.rgb * diffColor.rgb;
        #ifdef AO
            // If using AO, the vertex light ambient is black, calculate occluded ambient here
            finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * cAmbientColor * diffColor.rgb;
        #endif
        
        #ifdef MATERIAL
            // Add light pre-pass accumulation result
            // Lights are accumulated at half intensity. Bring back to full intensity now
            vec4 lightInput = 2.0 * texture2DProj(sLightBuffer, vScreenPos);
            vec3 lightSpecColor = lightInput.a * lightInput.rgb / max(GetIntensity(lightInput.rgb), 0.001);

            finalColor += lightInput.rgb * diffColor.rgb + lightSpecColor * specColor;
        #endif

        #ifdef ENVCUBEMAP
            #ifdef NORMALMAP
                mat3 tbn = mat3(vTangent, vBitangent, vNormal);
                vec3 normal = tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord));
            #else
                vec3 normal = vNormal;
            #endif
            normal = normalize(normal);
            finalColor += cMatEnvMapColor * textureCube(sEnvCubeMap, reflect(vReflectionVec, normal)).rgb;
        #endif
        #ifdef LIGHTMAP
            finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * diffColor.rgb;
        #endif
        #ifdef EMISSIVEMAP
            finalColor += cMatEmissiveColor * texture2D(sEmissiveMap, vTexCoord).rgb;
        #else
            finalColor += cMatEmissiveColor;
        #endif

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(vVertexLight.a, vWorldPos.y);
        #else
            float fogFactor = GetFogFactor(vVertexLight.a);
        #endif

        gl_FragColor = vec4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
