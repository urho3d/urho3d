#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

varying vec2 vTexCoord;

uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    gl_Position.z = gl_Position.w;
    vTexCoord = iTexCoord.xy;
}

void PS()
{   
    gl_FragColor = texture2D(sDiffMap, vTexCoord);       
}
