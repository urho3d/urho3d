#include "Uniforms.vert"
#include "Transform.vert"
#include "Lighting.vert"

varying vec4 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec3 vVertexLighting;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = vec4(GetTexCoord(iTexCoord), GetZonePos(worldPos), GetDepth(gl_Position));

    vVertexLighting = vec3(0.0, 0.0, 0.0);
    #ifdef NUMVERTEXLIGHTS
    vec3 normal = GetWorldNormal(modelMatrix);
    for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
        vVertexLighting += GetVertexLight(i, worldPos, normal) * cVertexLights[i * 3].rgb;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}
