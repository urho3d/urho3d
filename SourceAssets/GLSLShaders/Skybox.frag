#include "Uniforms.frag"
#include "Samplers.frag"

varying vec3 vTexCoord;

void main()
{
    gl_FragColor = cMatDiffColor * textureCube(sDiffCubeMap, vTexCoord);
}
