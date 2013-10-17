#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"

varying vec2 vScreenPos;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}
