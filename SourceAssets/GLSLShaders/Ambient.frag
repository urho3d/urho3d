#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"
#include "Lighting.frag"

varying vec4 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec3 vVertexLighting;

void main()
{
    #ifdef DIFFMAP
        vec4 diffColor = cMatDiffColor * texture2D(sDiffMap, vTexCoord.xy);
    #else
        vec4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= vColor;
    #endif

    vec3 finalColor = (GetAmbient(vTexCoord.z) + vVertexLighting) * diffColor.rgb;

    gl_FragColor = vec4(GetFog(finalColor, vTexCoord.w), diffColor.a);
}
