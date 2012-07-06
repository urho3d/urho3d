#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"
#include "Fog.frag"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
#ifdef PERPIXEL
    varying vec4 vLightVec;
    #ifdef SPOTLIGHT
        varying vec4 vSpotPos;
    #endif
    #ifdef POINTLIGHT
        varying vec3 vCubeMaskVec;
    #endif
#else
    varying vec4 vVertexLight;
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

    #ifdef VERTEXCOLOR
        diffColor *= vColor;
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        vec3 lightColor;
        vec3 finalColor;
        float diff;
    
        #ifdef DIRLIGHT
            diff = GetDiffuseDirVolumetric();
        #else
            diff = GetDiffusePointOrSpotVolumetric(vLightVec.xyz);
        #endif
    
        #if defined(SPOTLIGHT)
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #elif defined(CUBEMASK)
            lightColor = textureCube(sLightCubeMap, vCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
    
        finalColor = diff * lightColor * diffColor.rgb;
        
        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            gl_FragColor = vec4(GetFog(finalColor, vLightVec.w), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, vLightVec.w), diffColor.a);
        #endif
    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight.rgb * diffColor.rgb;
        gl_FragColor = vec4(GetFog(finalColor, vVertexLight.a), diffColor.a);
    #endif
}
