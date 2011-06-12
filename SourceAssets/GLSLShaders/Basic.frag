#include "Uniforms.frag"
#include "Samplers.frag"

#if defined(DIFFMAP) || defined(ALPHAMAP)
    varying vec2 vTexCoord;
#endif
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif

void main()
{
    vec4 diffColor = cMatDiffColor;

    #ifdef VERTEXCOLOR
        diffColor *= vColor;
    #endif

    #if (!defined(DIFFMAP)) && (!defined(ALPHAMAP))
        gl_FragColor = diffColor;
    #endif
    #ifdef DIFFMAP
        gl_FragColor = diffColor * texture2D(sDiffMap, vTexCoord);
    #endif
    #ifdef ALPHAMAP
        float alphaInput = texture2D(sDiffMap, vTexCoord).a;
        gl_FragColor = vec4(diffColor.rgb, diffColor.a * alphaInput);
    #endif
}
