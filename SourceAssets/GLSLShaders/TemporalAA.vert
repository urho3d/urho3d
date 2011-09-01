#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"

varying vec2 vScreenPos;
varying vec3 vFarRay;
#ifdef ORTHO
varying vec3 vNearRay;
#endif

void main()
{
    GetPosition(iPosition, gl_Position);
    vScreenPos = GetScreenPosPreDiv(gl_Position);

    vFarRay = GetFarRay(gl_Position);
    #ifdef ORTHO
        vNearRay = GetNearRay(gl_Position);
    #endif
}
