#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"
#include "Lighting.frag"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec2 vZonePosDepth;

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

    gl_FragColor = vec4(GetFog(GetAmbient(vZonePosDepth.x) * diffColor.rgb, vZonePosDepth.y), diffColor.a);
}
