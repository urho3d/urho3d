#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"
#include "Lighting.frag"

varying vec3 vTexCoord;
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

    vec3 finalColor = vVertexLighting * diffColor.rgb;
    gl_FragColor = vec4(GetFog(finalColor, vTexCoord.z), diffColor.a);
}
