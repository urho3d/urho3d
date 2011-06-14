#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"

varying vec2 vScreenPos;

void main()
{
    GetPosition(iPosition, gl_Position);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}
