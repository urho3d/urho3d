#include "Uniforms.vert"
#include "Transform.vert"

varying vec3 vTexCoord;

void main()
{
    GetPosition(iPosition, gl_Position);
    vTexCoord = iPosition.xyz;
}
