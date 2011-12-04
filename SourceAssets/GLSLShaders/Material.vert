#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"
#include "Lighting.vert"

varying vec3 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec3 vVertexLighting;
varying vec4 vScreenPos;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = vec3(GetTexCoord(iTexCoord), GetDepth(gl_Position));
    vScreenPos = GetScreenPos(gl_Position);

    vVertexLighting = GetAmbient(GetZonePos(worldPos));
    #ifdef NUMVERTEXLIGHTS
    vec3 normal = GetWorldNormal(modelMatrix);
    for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
        vVertexLighting += GetVertexLight(i, worldPos, normal) * cVertexLights[i * 3].rgb;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}
