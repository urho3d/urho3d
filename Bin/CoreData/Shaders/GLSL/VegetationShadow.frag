#include "Uniforms.frag"
#include "Samplers.frag"

varying vec2 vTexCoord;

void main()
{
    #ifdef ALPHAMASK
        float alpha = texture2D(sDiffMap, vTexCoord).a;
        if (alpha < 0.5)
            discard;
    #endif

    gl_FragColor = vec4(1.0);
}
