#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"

varying vec2 vTexCoord;
varying vec2 vScreenPos;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetQuadTexCoord(gl_Position);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}
