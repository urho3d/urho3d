#include "Uniforms.frag"
#include "Samplers.frag"

varying vec3 vTexCoord;

void main()
{
    gl_FragColor = cMatDiffColor * textureCube(sDiffCubeMap, vTexCoord);
    gl_FragDepth = 1.0;
}
