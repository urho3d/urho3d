#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"

#ifdef COMPILEPS
uniform vec2 cBlurOffsets;
#endif

varying vec2 vScreenPos;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}

void PS()
{
    vec2 color = vec2(0.0);
    
    color += 0.015625 * texture2D(sDiffMap, vScreenPos + vec2(-3.0) * cBlurOffsets).rg;
    color += 0.09375 * texture2D(sDiffMap, vScreenPos + vec2(-2.0) * cBlurOffsets).rg;
    color += 0.234375 * texture2D(sDiffMap, vScreenPos + vec2(-1.0) * cBlurOffsets).rg;
    color += 0.3125 * texture2D(sDiffMap, vScreenPos).rg;
    color += 0.234375 * texture2D(sDiffMap, vScreenPos + vec2(1.0) * cBlurOffsets).rg;
    color += 0.09375 * texture2D(sDiffMap, vScreenPos + vec2(2.0) * cBlurOffsets).rg;
    color += 0.015625 * texture2D(sDiffMap, vScreenPos + vec2(3.0) * cBlurOffsets).rg;
    
    gl_FragColor = vec4(color, 0.0, 0.0);
}

