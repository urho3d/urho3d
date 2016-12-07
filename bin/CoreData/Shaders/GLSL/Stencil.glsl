#include "Uniforms.glsl"
#include "Transform.glsl"
#ifdef COMPILEVS
void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
}
#endif
#ifdef COMPILEPS
void main()
{
    gl_FragColor = vec4(1.0);
}
#endif
