#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

varying vec3 vTexCoord;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);

    #ifndef GL_ES
    gl_Position.z = gl_Position.w;
    #else
    // On OpenGL ES force Z slightly in front of far plane to avoid clipping artifacts due to inaccuracy
    gl_Position.z = 0.999 * gl_Position.w;
    #endif
    vTexCoord = iPos.xyz;
}

void PS()
{
    gl_FragColor = cMatDiffColor * textureCube(sDiffCubeMap, vTexCoord);
}
