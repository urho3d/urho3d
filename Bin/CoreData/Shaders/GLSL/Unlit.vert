#include "Uniforms.vert"
#include "Transform.vert"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
#ifdef HEIGHTFOG
    varying vec3 vWorldPos;
#endif
varying float vDepth;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetTexCoord(iTexCoord);
    vDepth = GetDepth(gl_Position);

    #ifdef HEIGHTFOG
        vWorldPos = worldPos;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}
