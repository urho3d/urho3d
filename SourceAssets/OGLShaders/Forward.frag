#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"
#include "Fog.frag"

varying vec4 vWorldPos;
varying vec2 vTexCoord;
varying vec3 vNormal;
#ifdef NORMALMAP
varying vec3 vTangent;
varying vec3 vBitangent;
#endif
#ifdef SHADOW
varying vec4 vShadowPos;
#endif
#ifdef SPOTLIGHT
varying vec4 vSpotPos;
#endif
#ifdef VERTEXCOLOR
varying vec4 vColor;
#endif

void main()
{
    #ifdef DIFFMAP
        vec4 diffColor = cMatDiffColor * texture2D(sDiffMap, vTexCoord);
    #else
        vec4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= vColor;
    #endif

    #if (!defined(VOLUMETRIC)) && ((defined(DIRLIGHT)) || (defined(POINTLIGHT)) || (defined(SPOTLIGHT)))

        vec3 lightColor;
        vec3 lightDir;
        vec3 lightVec;
        float diff;

        #ifdef NORMALMAP
            mat3 tbn = mat3(vTangent, vBitangent, vNormal);
            vec3 normal = normalize(tbn * UnpackNormal(texture2D(sNormalMap, vTexCoord)));
        #else
            vec3 normal = normalize(vNormal);
        #endif

        #ifdef DIRLIGHT
            diff = GetDiffuseDir(normal, lightDir) * GetSplitFade(vWorldPos.w);
        #else
            diff = GetDiffusePointOrSpot(normal, vWorldPos.xyz, lightDir, lightVec);
        #endif

        #ifdef SHADOW
            diff *= GetShadow(vShadowPos);
        #endif

        #ifdef SPOTLIGHT
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #else
            #ifdef CUBEMASK
                lightColor = textureCube(sLightCubeMap, cLightVecRot * lightVec).rgb * cLightColor.rgb;
            #else
                lightColor = cLightColor.rgb;
            #endif
        #endif

        #ifdef SPECULAR
            #ifdef SPECMAP
                float specStrength = cMatSpecProperties.x * texture2D(sSpecMap, vTexCoord).g;
            #else
                float specStrength = cMatSpecProperties.x;
            #endif
            float spec = GetSpecular(normal, vWorldPos.xyz, lightDir, cMatSpecProperties.y);
            vec3 finalColor = diff * lightColor * (diffColor.rgb + spec * specStrength * cLightColor.a);
        #else
            vec3 finalColor = diff * lightColor * diffColor.rgb;
        #endif

        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            gl_FragColor = vec4(GetFog(finalColor, vWorldPos.w), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, vWorldPos.w), diffColor.a);
        #endif

    #else

        #if (defined(VOLUMETRIC)) && ((defined(DIRLIGHT)) || (defined(POINTLIGHT)) || (defined(SPOTLIGHT)))

            vec3 lightColor;
            vec3 lightVec;
            float diff;

            #ifdef DIRLIGHT
                diff = GetDiffuseDirVolumetric() * GetSplitFade(vWorldPos.w);
            #else
                diff = GetDiffusePointOrSpotVolumetric(vWorldPos.xyz, lightVec);
            #endif

            #ifdef SPOTLIGHT
                lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
            #else
                #ifdef CUBEMASK
                    lightColor = textureCube(sLightCubeMap, cLightVecRot * lightVec).rgb * cLightColor.rgb;
                #else
                    lightColor = cLightColor.rgb;
                #endif
            #endif

            vec3 finalColor = diff * lightColor * diffColor.rgb;

            #ifdef AMBIENT
                finalColor += cAmbientColor * diffColor.rgb;
                gl_FragColor = vec4(GetFog(finalColor, vWorldPos.w), diffColor.a);
            #else
                gl_FragColor = vec4(GetLitFog(finalColor, vWorldPos.w), diffColor.a);
            #endif

        #else

            #ifdef UNLIT
                gl_FragColor = vec4(GetFog(diffColor.rgb, vWorldPos.w), diffColor.a);
            #endif

            #ifdef ADDITIVE
                gl_FragColor = vec4(GetLitFog(diffColor.rgb, vWorldPos.w), diffColor.a);
            #endif

            #ifdef AMBIENT
                vec3 finalColor = cAmbientColor * diffColor.rgb;
                gl_FragColor = vec4(GetFog(finalColor, vWorldPos.w), diffColor.a);
            #endif

        #endif

    #endif
}
