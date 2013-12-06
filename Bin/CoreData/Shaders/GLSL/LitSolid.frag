#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"
#include "Fog.frag"

varying vec2 vTexCoord;
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
    #ifdef LIGHTMAP
        varying vec2 vTexCoord2;
    #endif
#endif

void main()
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

        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            gl_FragColor = vec4(GetFog(finalColor, vLightVec.w), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, vLightVec.w), diffColor.a);
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

        #ifdef ENVCUBEMAP
            normal = normalize(normal);
            finalColor = cMatEnvMapColor * textureCube(sEnvCubeMap, reflect(vReflectionVec, normal)).rgb;
        #endif
        #ifdef LIGHTMAP
            finalColor += texture2D(sEmissiveMap, vTexCoord2).rgb * diffColor.rgb;
        #endif
        #ifdef EMISSIVE
            finalColor += cMatEmissiveColor * texture2D(sEmissiveMap, vTexCoord).rgb;
        #endif

        gl_FragData[0] = vec4(GetFog(finalColor, vVertexLight.a), 1.0);
        gl_FragData[1] = GetFogFactor(vVertexLight.a) * vec4(diffColor.rgb, specIntensity);
        gl_FragData[2] = vec4(normal * 0.5 + 0.5, specPower);
        gl_FragData[3] = vec4(EncodeDepth(vVertexLight.a), 0.0);


    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight.rgb * diffColor.rgb;

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
        #ifdef EMISSIVE
            finalColor += cMatEmissiveColor * texture2D(sEmissiveMap, vTexCoord).rgb;
        #endif

        gl_FragColor = vec4(GetFog(finalColor, vVertexLight.a), diffColor.a);
    #endif
}
