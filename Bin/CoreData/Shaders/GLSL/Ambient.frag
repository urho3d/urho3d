#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"
#include "Lighting.frag"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec4 vVertexLighting;

void main()
{
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

    vec3 finalColor = vVertexLighting.rgb * diffColor.rgb;
    gl_FragColor = vec4(GetFog(finalColor, vVertexLighting.a), diffColor.a);
}
