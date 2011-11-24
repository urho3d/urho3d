#include "Uniforms.vert"
#include "Transform.vert"

varying vec4 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec3 vLightVec;
#ifdef SPECULAR
    varying vec3 vEyeVec;
#endif
#ifndef NORMALMAP
    varying vec3 vNormal;
#endif
#ifdef SHADOW
    #if defined(DIRLIGHT)
        varying vec4 vShadowPos[4];
    #elif defined(SPOTLIGHT)
        varying vec4 vShadowPos;
    #else
        varying vec3 vShadowPos;
    #endif
#endif
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
    vTexCoord = vec4(GetTexCoord(iTexCoord), GetZonePos(worldPos), GetDepth(gl_Position));

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif

    #ifdef NORMALMAP
        vec3 vNormal;
        vec3 vTangent;
        vec3 vBitangent;
    #endif

    vNormal = GetWorldNormal(modelMatrix);
    vec4 projWorldPos = vec4(worldPos, 1.0);

    #ifdef DIRLIGHT
        vLightVec = cLightDir;
    #else
        vLightVec = (cLightPos.xyz - worldPos) * cLightPos.w;
    #endif

    #ifdef SHADOW
        // Shadow projection: transform from world space to shadow space
        #if defined(DIRLIGHT)
            vShadowPos[0] = cShadowProj[0] * projWorldPos;
            vShadowPos[1] = cShadowProj[1] * projWorldPos;
            vShadowPos[2] = cShadowProj[2] * projWorldPos;
            vShadowPos[3] = cShadowProj[3] * projWorldPos;
        #elif defined(SPOTLIGHT)
            vShadowPos = cShadowProj[0] * projWorldPos;
        #else
            vShadowPos = worldPos - cLightPos.xyz;
        #endif
    #endif

    #ifdef SPOTLIGHT
        // Spotlight projection: transform from world space to projector texture coordinates
        vSpotPos = cSpotProj * projWorldPos;
    #endif

    #ifdef POINTLIGHT
        vCubeMaskVec = cLightVecRot * vLightVec;
    #endif

    #ifdef NORMALMAP
        vTangent = GetWorldTangent(modelMatrix);
        vBitangent = cross(vTangent, vNormal) * iTangent.w;
        mat3 tbn = mat3(vTangent, vBitangent, vNormal);
        vLightVec = vLightVec * tbn;
        #ifdef SPECULAR
            vEyeVec = (cameraPos - worldPos) * tbn;
        #endif
    #elif defined(SPECULAR)
        vEyeVec = cameraPos - worldPos;
    #endif
}
