#include "Uniforms.frag"
#include "Samplers.frag"

#ifdef ALPHAMASK
    varying vec2 vTexCoord;
#endif

void main()
{
    #ifdef ALPHAMASK
        float alpha = texture2D(sDiffMap, vTexCoord).a;
    #else
        const float alpha = 1.0;
    #endif

    gl_FragColor = vec4(alpha);
}
