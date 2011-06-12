#include "../Uniforms.vert"
#include "../Transform.vert"
#include "../ScreenPos.vert"

varying vec2 vTexCoord;
varying vec4 vWorldPos;
varying vec4 vScreenPos;

void main()
{
    vec4 pos;
    #if defined(SKINNED)
        pos = GetPositionSkinned(iPosition, iBlendWeights, iBlendIndices, gl_Position);
    #else
        pos = GetPosition(iPosition, gl_Position);
    #endif

    // Store world-oriented view position in case it is needed
    vWorldPos = vec4(pos.xyz - cCameraPos, GetDepth(gl_Position));
    vScreenPos = GetScreenPos(gl_Position);
    vTexCoord = GetTexCoord(iTexCoord);
}
