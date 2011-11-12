#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"
#include "Fog.frag"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec3 vLightVec;
varying vec2 vZonePosDepth;
#ifdef SPOTLIGHT
    varying vec4 vSpotPos;
#endif
#ifdef POINTLIGHT
    varying vec3 vCubeMaskVec;
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

    vec3 lightColor;
    vec3 lightVec;
    vec3 finalColor;
    float diff;

    #ifdef DIRLIGHT
        diff = GetDiffuseDirVolumetric();
    #else
        diff = GetDiffusePointOrSpotVolumetric(vLightVec);
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
        finalColor += GetAmbient(vZonePosDepth.x) * diffColor.rgb;
        gl_FragColor = vec4(GetFog(finalColor, vZonePosDepth.y), diffColor.a);
    #else
        gl_FragColor = vec4(GetLitFog(finalColor, vZonePosDepth.y), diffColor.a);
    #endif
}
