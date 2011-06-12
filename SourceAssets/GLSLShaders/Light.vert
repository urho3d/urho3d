#include "../Uniforms.vert"
#include "../Transform.vert"
#include "../ScreenPos.vert"

#ifdef DIRLIGHT
varying vec2 vScreenPos;
#else
varying vec4 vScreenPos;
#endif
varying vec3 vFarRay;
#ifdef ORTHO
varying vec3 vNearFar;
#endif

void main()
{
    GetPosition(iPosition, gl_Position);
    #ifdef DIRLIGHT
        vScreenPos = GetScreenPosPreDiv(gl_Position);
        vFarRay = GetFarRay(gl_Position);
        #ifdef ORTHO
            vNearRay = GetNearRay(gl_Position);
        #endif
    #else
        vScreenPos = GetScreenPos(gl_Position);
        vFarRay = GetFarRay(gl_Position) * gl_Position.w;
        #ifdef ORTHO
            vNearRay = GetNearRay(gl_Position) * gl_Position.w;
        #endif
    #endif
}
