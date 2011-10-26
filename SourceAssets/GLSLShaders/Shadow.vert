#include "Uniforms.vert"
#include "Transform.vert"

#ifdef ALPHAMASK
    varying vec2 vTexCoord;
#endif

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);

    #ifdef ALPHAMASK
        vTexCoord = GetTexCoord(iTexCoord);
    #endif
}

