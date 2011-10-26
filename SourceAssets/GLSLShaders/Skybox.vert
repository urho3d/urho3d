#include "Uniforms.vert"
#include "Transform.vert"

varying vec3 vTexCoord;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);

    gl_Position.z = gl_Position.w;
    vTexCoord = iPos.xyz;
}
