#include "../Uniforms.vert"
#include "../Transform.vert"

varying vec2 vTexCoord;
varying float vDepth;
varying vec3 vNormal;
#ifdef NORMALMAP
varying vec3 vTangent;
varying vec3 vBitangent;
#endif

void main()
{
    #if defined(SKINNED)
        #ifndef NORMALMAP
            GetPositionNormalSkinned(iPosition, iNormal, iBlendWeights, iBlendIndices, gl_Position, vNormal);
        #else
            GetPositionNormalTangentSkinned(iPosition, iNormal, iTangent, iBlendWeights, iBlendIndices, gl_Position, vNormal, vTangent);
        #endif
    #else
        #ifndef NORMALMAP
            GetPositionNormal(iPosition, iNormal, gl_Position, vNormal);
        #else
            GetPositionNormalTangent(iPosition, iNormal, iTangent, gl_Position, vNormal, vTangent);
        #endif
    #endif

    #ifdef NORMALMAP
        vBitangent = cross(vTangent, vNormal) * iTangent.w;
    #endif

    vTexCoord = GetTexCoord(iTexCoord);
    vDepth = GetDepth(gl_Position);
}
