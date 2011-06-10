#include "Uniforms.vert"
#include "Transform.vert"

varying vec4 vWorldPos;
varying vec2 vTexCoord;
varying vec3 vNormal;
#ifdef NORMALMAP
varying vec3 vTangent;
varying vec3 vBitangent;
#endif
#ifdef SHADOW
varying vec4 vShadowPos;
#endif
#ifdef SPOTLIGHT
varying vec4 vSpotPos;
#endif
#ifdef VERTEXCOLOR
varying vec4 vColor;
#endif

void main()
{
    vec4 pos;

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

    // Store adjusted world position and linear depth for light calculations
    vWorldPos = vec4(pos.xyz - cCameraPos, GetDepth(gl_Position));

    #ifdef SHADOW
        // Shadow projection: transform from world space to shadow space
        vShadowPos = cShadowProj * pos;
    #endif
    #ifdef SPOTLIGHT
        // Spotlight projection: transform from world space to projector texture coordinates
        vSpotPos = cSpotProj * pos;
    #endif

    #ifdef NORMALMAP
        vBitangent = cross(vTangent, vNormal) * iTangent.w;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif

    vTexCoord = GetTexCoord(iTexCoord);
}
