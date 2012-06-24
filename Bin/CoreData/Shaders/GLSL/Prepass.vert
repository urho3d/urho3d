#include "Uniforms.vert"
#include "Transform.vert"

#ifdef HWDEPTH
    varying vec2 vTexCoord;
#else
    varying vec3 vTexCoord;
#endif
varying vec3 vNormal;
#ifdef NORMALMAP
    varying vec3 vTangent;
    varying vec3 vBitangent;
#endif

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    #ifdef HWDEPTH
        vTexCoord = GetTexCoord(iTexCoord);
    #else
        vTexCoord = vec3(GetTexCoord(iTexCoord), GetDepth(gl_Position));
    #endif
    
    vNormal = GetWorldNormal(modelMatrix);
    #ifdef NORMALMAP
        vTangent = GetWorldTangent(modelMatrix);
        vBitangent = cross(vTangent, vNormal) * iTangent.w;
    #endif
}
