#include "Uniforms.vert"
#include "Transform.vert"

varying vec3 vTexCoord;

void main()
{
    GetPosition(iPosition, gl_Position);
    gl_Position.z = gl_Position.w;
    vTexCoord = iPosition.xyz;
}
