#include "Uniforms.glsl"
#include "Transform.glsl"

uniform float cWindHeightFactor;
uniform float cWindHeightPivot;
uniform float cWindPeriod;
uniform vec2 cWindWorldSpacing;

varying vec3 vTexCoord;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    
    float windStrength = max(iPos.y - cWindHeightPivot, 0.0) * cWindHeightFactor;
    float windPeriod = cElapsedTime * cWindPeriod + dot(worldPos.xz, cWindWorldSpacing);
    worldPos.x += windStrength * sin(windPeriod);
    worldPos.z -= windStrength * cos(windPeriod);

    gl_Position = GetClipPos(worldPos);
    vTexCoord = vec3(GetTexCoord(iTexCoord), GetDepth(gl_Position));
}

