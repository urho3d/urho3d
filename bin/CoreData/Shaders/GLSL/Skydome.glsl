#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

varying vec2 vTexCoord;
#ifdef COMPILEVS
void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    gl_Position.z = gl_Position.w;
    vTexCoord = iTexCoord.xy;
}
#endif
#ifdef COMPILEPS
void main()
{
    gl_FragColor = texture2D(sDiffMap, vTexCoord);
}
#endif
