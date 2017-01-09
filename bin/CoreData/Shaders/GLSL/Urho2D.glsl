#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

varying vec2 vTexCoord;
varying vec4 vColor;
#ifdef COMPILEVS
void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    
    vTexCoord = iTexCoord;
    vColor = iColor;
}
#endif
#ifdef COMPILEPS
void main()
{
    vec4 diffColor = cMatDiffColor * vColor;
    vec4 diffInput = texture2D(sDiffMap, vTexCoord);
    gl_FragColor = diffColor * diffInput;
}
#endif
