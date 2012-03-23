#include "Uniforms.vert"
#include "Transform.vert"
#include "Lighting.vert"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec4 vVertexLighting;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetTexCoord(iTexCoord);

    vVertexLighting = vec4(GetAmbient(GetZonePos(worldPos)), GetDepth(gl_Position));
    #ifdef NUMVERTEXLIGHTS
        vec3 normal = GetWorldNormal(modelMatrix);
        for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
            vVertexLighting.rgb += GetVertexLight(i, worldPos, normal) * cVertexLights[i * 3].rgb;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}
