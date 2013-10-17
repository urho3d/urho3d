#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"
#include "Fog.frag"

varying vec2 vTexCoord;
#ifdef HEIGHTFOG
    varying vec3 vWorldPos;
#endif
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
    
        diff = GetDiffuseVolumetric(vLightVec.xyz);

        #if defined(SPOTLIGHT)
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #elif defined(CUBEMASK)
            lightColor = textureCube(sLightCubeMap, vCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif
    
        finalColor = diff * lightColor * diffColor.rgb;

        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(vLightVec.w, vWorldPos.y);
        #else
            float fogFactor = GetFogFactor(vLightVec.w);
        #endif
        
        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            gl_FragColor = vec4(GetFog(finalColor, fogFactor), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, fogFactor), diffColor.a);
        #endif
    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight.rgb * diffColor.rgb;
        
        #ifdef HEIGHTFOG
            float fogFactor = GetHeightFogFactor(vVertexLight.a, vWorldPos.y);
        #else
            float fogFactor = GetFogFactor(vVertexLight.a);
        #endif

        gl_FragColor = vec4(GetFog(finalColor, fogFactor), diffColor.a);
    #endif
}
