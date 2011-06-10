#include "Uniforms.vert"
#include "Transform.vert"

#ifdef DIFFMAP
    varying vec2 vTexCoord;
#endif
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif

void main()
{
    GetPosition(iPosition, gl_Position);
    #ifdef DIFFMAP
        vTexCoord = iTexCoord;
    #endif
    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}
