#include "Uniforms.vert"
#include "Transform.vert"

#ifdef ALPHAMASK
varying vec2 vTexCoord;
#endif

void main()
{
    #if defined(SKINNED)
        GetPositionSkinned(iPosition, iBlendWeights, iBlendIndices, gl_Position);
    #else
        GetPosition(iPosition, gl_Position);
    #endif

    #ifdef ALPHAMASK
        vTexCoord = GetTexCoord(iTexCoord);
    #endif
}

