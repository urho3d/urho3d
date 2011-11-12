#include "Uniforms.vert"
#include "Transform.vert"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec3 vLightVec;
varying vec2 vZonePosDepth;
#ifdef SPOTLIGHT
    varying vec4 vSpotPos;
#endif
#ifdef POINTLIGHT
    varying vec3 vCubeMaskVec;
#endif

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetTexCoord(iTexCoord);

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif

    vec3 centeredWorldPos = worldPos - cCameraPos;
    vec4 projWorldPos = vec4(worldPos, 1.0);

    #ifdef DIRLIGHT
        vLightVec = cLightDir;
    #else
        vLightVec = (cLightPos - centeredWorldPos) * cLightAtten;
    #endif
    
    vZonePosDepth = vec2(GetZonePos(worldPos), GetDepth(gl_Position));

    #ifdef SPOTLIGHT
        // Spotlight projection: transform from world space to projector texture coordinates
        vSpotPos = cSpotProj * projWorldPos;
    #endif

    #ifdef POINTLIGHT
        vCubeMaskVec = cLightVecRot * vLightVec.xyz;
    #endif
}
