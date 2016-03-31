#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"
#include "Fog.glsl"
#include "BRDF.glsl"
#include "IBL.glsl"

#ifdef NORMALMAP
    varying vec4 vTexCoord;
    varying vec4 vTangent;
#else
    varying vec2 vTexCoord;
#endif
varying vec3 vNormal;
varying vec4 vWorldPos;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
#ifdef PERPIXEL
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
    varying vec3 vVertexLight;
    varying vec4 vScreenPos;
    #if defined(ENVCUBEMAP) || defined(IBL)
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

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif

    #ifdef NORMALMAP
        vec3 tangent = GetWorldTangent(modelMatrix);
        vec3 bitangent = cross(tangent, vNormal) * iTangent.w;
        vTexCoord = vec4(GetTexCoord(iTexCoord), bitangent.xy);
        vTangent = vec4(tangent, bitangent.z);
    #else
        vTexCoord = GetTexCoord(iTexCoord);
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
            vSpotPos =  projWorldPos * cLightMatrices[0];
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
            vTexCoord2 = iTexCoord2;
        #else
            vVertexLight = GetAmbient(GetZonePos(worldPos));
        #endif
        
        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                vVertexLight += GetVertexLight(i, worldPos, vNormal) * cVertexLights[i * 3].rgb;
        #endif
        
        vScreenPos = GetScreenPos(gl_Position);

        #if defined(ENVCUBEMAP) || defined(IBL)
            vReflectionVec = worldPos - cCameraPos;
        #endif
    #endif
}

void PS()
{
    // Get material diffuse albedo
    #ifdef DIFFMAP
        vec4 diffInput = texture2D(sDiffMap, vTexCoord.xy);
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
        vec4 diffColor = cMatDiffColor * diffInput;
    #else
        vec4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= vColor;
    #endif
    
    // Get material specular albedo
    float roughness = 0;
    #ifdef PBR
        #ifdef SPECMAP
            vec4 specSample = texture2D(sSpecMap, vTexCoord.xy);
            vec3 specColor = specSample.rgb;

            #ifdef ROUGHNESS
                roughness = max(0.04, specSample.a);
            #else
                roughness = max(0.04, 1.0 - specSample.a);
               // roughness *= roughness;
            #endif

            roughness += cRoughnessPS;
            specColor *= cMatSpecColor.rgb;
        #elif defined(METALIC)
            vec4 roughMetalSrc = texture2D(sSpecMap, vTexCoord.xy);
            
            #ifdef ROUGHNESS
                roughness = max(0.04, roughMetalSrc.r);
            #else
                roughness = max(0.04, 1.0 - roughMetalSrc.r);
                //roughness *= roughness;
            #endif

            roughness += cRoughnessPS;
            float metalness = clamp(roughMetalSrc.g + cMetallicPS, 0.01,1.0);
        
            vec3 specColor = max(diffColor.rgb * metalness, vec3(0.08, 0.08, 0.08));
            specColor *= cMatSpecColor.rgb;
            diffColor.rgb = diffColor.rgb - diffColor.rgb * metalness;
        #else 
            roughness = cRoughnessPS;
            //roughness *= roughness;
            float metalness = clamp(cMetallicPS, 0.01, 1.0);

            //metalness = clamp(metalness, 0.01, 1.0);
         
            vec3 specColor = max(diffColor.rgb * metalness, vec3(0.08, 0.08, 0.08));
            specColor *= cMatSpecColor.rgb;
            diffColor.rgb = diffColor.rgb - diffColor.rgb * metalness;
        #endif
        roughness = pow(roughness, 2);
        roughness = clamp(roughness, 0.1, 1.0);
        
    #elif defined(SPECMAP)
        vec3 specColor = cMatSpecColor.rgb * texture2D(sSpecMap, vTexCoord.xy).rgb;
    #else
        vec3 specColor = cMatSpecColor.rgb;
    #endif

    // Get normal
    #ifdef NORMALMAP
        mat3 tbn = mat3(vTangent.xyz, vec3(vTexCoord.zw, vTangent.w), vNormal);
        vec3 normal = normalize(tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord.xy)));
    #else
        vec3 normal = normalize(vNormal);
    #endif

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

        float diff = GetDiffuse(normal, vWorldPos.xyz, lightDir);

        #ifdef SHADOW
            diff *= GetShadow(vShadowPos, vWorldPos.w);
        #endif
    
        #if defined(SPOTLIGHT)
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #elif defined(CUBEMASK)
            lightColor = textureCube(sLightCubeMap, vCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
    
        #ifdef PBR
            vec3 toCamera = normalize(cCameraPosPS - vWorldPos.xyz);
            vec3 lightVec = lightDir;
         
            vec3 diffHn = normalize(toCamera + lightDir);
            float diffvdh = max(0.0, dot(toCamera, diffHn));
            float diffndl = max(0.0, dot(normal, lightDir));
            float diffndv = max(1e-5, dot(normal, toCamera));
          
            float areaLight = 1;
            // #if defined(POINTLIGHT)               
            //     areaLight = AreaLight(lightVec, toCamera, normal, toCamera + cLightPosPS.xyz, roughness);
            // #endif
           
            vec3 diffuseTerm = BurleyDiffuse(diffColor.rgb, roughness, diffndv, diffndl, diffvdh) * diff * lightColor.rgb;

            vec3 Hn = normalize(toCamera + lightVec);
            float vdh = max(0.0, dot(toCamera, Hn));
            float ndh = max(0.0, dot(normal, Hn));
            float ndl = max(0.0, dot(normal, lightVec));
            float ndv = max(1e-5, dot(normal, toCamera));
           

            vec3 fresnelTerm = SchlickGaussianFresnel(specColor, vdh) ;
            float distTerm = GGXDistribution(ndh, roughness) * areaLight;
            float visTerm = SchlickVisibility(ndl, ndv, roughness);

            finalColor = LinearFromSRGB((diffuseTerm + distTerm * visTerm * fresnelTerm * lightColor) * diff);
           
        #else
            #ifdef SPECULAR
                float spec = GetSpecular(normal, cCameraPosPS - vWorldPos.xyz, lightDir, cMatSpecColor.a);
                finalColor = diff * lightColor * (diffColor.rgb + spec * specColor * cLightColor.a);
            #else
                finalColor = diff * lightColor * diffColor.rgb;
            #endif
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
        float specPower = cMatSpecColor.a / 255.0;

        gl_FragData[0] = vec4(normal * 0.5 + 0.5, specPower);
        gl_FragData[1] = vec4(EncodeDepth(vWorldPos.w), 0.0);
    #elif defined(DEFERRED)
        // Fill deferred G-buffer
        float specIntensity = specColor.g;
        float specPower = cMatSpecColor.a / 255.0;

        vec3 finalColor = vVertexLight * diffColor.rgb;
        #ifdef AO
            #ifdef IBL
                float aoFactor = texture2D(sEmissiveMap, vTexCoord.xy).r;
            #else
                // If using AO, the vertex light ambient is black, calculate occluded ambient here
                finalColor += texture2D(sEmissiveMap, vTexCoord2.xy).rgb * cAmbientColor * diffColor.rgb;
            #endif
        #endif
        
       #if defined(PBR) && defined(IBL)
            vec3 toCamera = normalize(vWorldPos.xyz - cCameraPosPS);
            vec3 reflection = normalize(reflect(toCamera, normal));

            float horizonOcclusion = 1.3;
            float horizon = clamp(1 + horizonOcclusion * dot(reflection, normal), 0.0, 1.0);
            horizon *= horizon;
            
            vec3 cubeColor = vVertexLight.rgb;
            vec3 iblColor = ImageBasedLighting(reflection, normal, toCamera, specColor, roughness, cubeColor);
            #ifdef AO
                finalColor.rgb += LinearFromSRGB(vVertexLight.rgb * iblColor * aoFactor));
            #else
                finalColor.rgb += LinearFromSRGB(iblColor * horizon * cubeColor);
            #endif
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

        #if defined(PBR)
            gl_FragData[0] = vec4(GetFog(finalColor, fogFactor), 1.0);
            gl_FragData[1] = fogFactor * vec4(diffColor.rgb, metalness);
            gl_FragData[2] = vec4(normal * 0.5 + 0.5, roughness);
            gl_FragData[3] = vec4(EncodeDepth(vWorldPos.w), 0.0);
        #else
            gl_FragData[0] = vec4(GetFog(finalColor, fogFactor), 1.0);
            gl_FragData[1] = fogFactor * vec4(diffColor.rgb, specIntensity);
            gl_FragData[2] = vec4(normal * 0.5 + 0.5, roughness);
            gl_FragData[3] = vec4(EncodeDepth(vWorldPos.w), 0.0);
        #endif
    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight * diffColor.rgb;
        #ifdef AO
            #ifdef PBR
                float aoFactor = texture2D(sEmissiveMap, vTexCoord.xy).r;
            #else
                // If using AO, the vertex light ambient is black, calculate occluded ambient here
                finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * cAmbientColor * diffColor.rgb;
            #endif
        #endif
        
        #ifdef MATERIAL
            // Add light pre-pass accumulation result
            // Lights are accumulated at half intensity. Bring back to full intensity now
            vec4 lightInput = 2.0 * texture2DProj(sLightBuffer, vScreenPos);
            vec3 lightSpecColor = lightInput.a * lightInput.rgb / max(GetIntensity(lightInput.rgb), 0.001);

            finalColor += lightInput.rgb * diffColor.rgb + lightSpecColor * specColor;
        #endif

        #if defined(PBR) && defined(IBL)
            vec3 toCamera = normalize(vWorldPos.xyz - cCameraPosPS);
            vec3 reflection = normalize(reflect(toCamera, normal));

            float horizonOcclusion = 1.3;
            float horizon = clamp(1 + horizonOcclusion * dot(reflection, normal), 0.0, 1.0);
            horizon *= horizon;
            
            vec3 cubeColor = vVertexLight.rgb;
            vec3 iblColor = ImageBasedLighting(reflection, normal, toCamera, specColor, roughness, cubeColor);
            #ifdef AO
                finalColor.rgb += LinearFromSRGB(vVertexLight.rgb * iblColor * aoFactor));
            #else
                finalColor.rgb += LinearFromSRGB(iblColor * horizon * cubeColor);
            #endif
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
