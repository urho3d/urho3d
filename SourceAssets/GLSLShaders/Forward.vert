#include "Uniforms.vert"
#include "Transform.vert"

varying vec2 vTexCoord;
varying vec4 vLightVec;
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
varying vec3 vWorldLightVec;
#endif
#endif
#ifdef SPOTLIGHT
varying vec4 vSpotPos;
#endif
#ifdef POINTLIGHT
varying vec3 vCubeMaskVec;
#endif
#ifdef VERTEXCOLOR
varying vec4 vColor;
#endif

void main()
{
    vec4 pos;

    #ifdef NORMALMAP
        vec3 vNormal;
        vec3 vTangent;
        vec3 vBitangent;
    #endif

    #if defined(SKINNED)
        #ifndef NORMALMAP
            pos = GetPositionNormalSkinned(iPosition, iNormal, iBlendWeights, iBlendIndices, gl_Position, vNormal);
        #else
            pos = GetPositionNormalTangentSkinned(iPosition, iNormal, iTangent, iBlendWeights, iBlendIndices, gl_Position, vNormal, vTangent);
        #endif
    #elif defined(BILLBOARD)
        pos = GetPositionBillboard(iPosition, iTexCoord2, gl_Position);
        vNormal = vec3(-cCameraRot[2][0], -cCameraRot[2][1], -cCameraRot[2][2]);
    #else
        #ifndef NORMALMAP
            pos = GetPositionNormal(iPosition, iNormal, gl_Position, vNormal);
        #else
            pos = GetPositionNormalTangent(iPosition, iNormal, iTangent, gl_Position, vNormal, vTangent);
        #endif
    #endif

    vec3 worldPos = pos.xyz - cCameraPos;

    #if defined(DIRLIGHT)
        vLightVec = vec4(cLightDir, GetDepth(gl_Position));
    #elif defined(LIGHT)
        vLightVec = vec4((cLightPos - worldPos) * cLightAtten, GetDepth(gl_Position));
    #else
        vLightVec = vec4(0.0, 0.0, 0.0, GetDepth(gl_Position));
    #endif

    #ifdef SHADOW
        // Shadow projection: transform from world space to shadow space
        #if defined(DIRLIGHT)
            vShadowPos[0] = cShadowProj[0] * pos;
            vShadowPos[1] = cShadowProj[1] * pos;
            vShadowPos[2] = cShadowProj[2] * pos;
            vShadowPos[3] = cShadowProj[3] * pos;
        #elif defined(SPOTLIGHT)
            vShadowPos = cShadowProj[0] * pos;
        #else
            vWorldLightVec = worldPos - cLightPos;
        #endif
    #endif

    #ifdef SPOTLIGHT
        // Spotlight projection: transform from world space to projector texture coordinates
        vSpotPos = cSpotProj * pos;
    #endif

    #ifdef POINTLIGHT
        vCubeMaskVec = cLightVecRot * vLightVec.xyz;
    #endif

    #ifdef NORMALMAP
        vBitangent = cross(vTangent, vNormal) * iTangent.w;
        mat3 tbn = mat3(vTangent, vBitangent, vNormal);
        #ifdef LIGHT
            vLightVec.xyz = vLightVec.xyz * tbn;
        #endif
        #ifdef SPECULAR
            vEyeVec = -worldPos * tbn;
        #endif
    #elif defined(SPECULAR)
        vEyeVec = -worldPos;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif

    vTexCoord = GetTexCoord(iTexCoord);
}
