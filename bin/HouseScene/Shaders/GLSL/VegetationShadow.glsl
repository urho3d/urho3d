#include "Uniforms.glsl"
#include "Transform.glsl"

uniform float cWindHeightFactor;
uniform float cWindHeightPivot;
uniform float cWindPeriod;
uniform vec2 cWindWorldSpacing;
#ifdef WINDSTEMAXIS
    uniform vec3 cWindStemAxis;
#endif

#ifdef VSM_SHADOW
    varying vec4 vTexCoord;
#else
    varying vec2 vTexCoord;
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    
    #ifdef WINDSTEMAXIS
        float stemDistance = dot(iPos.xyz, cWindStemAxis);
    #else
        float stemDistance = iPos.y;
    #endif
    float windStrength = max(stemDistance - cWindHeightPivot, 0.0) * cWindHeightFactor;
    float windPeriod = cElapsedTime * cWindPeriod + dot(worldPos.xz, cWindWorldSpacing);
    worldPos.x += windStrength * sin(windPeriod);
    worldPos.z -= windStrength * cos(windPeriod);

    gl_Position = GetClipPos(worldPos);
    #ifdef VSM_SHADOW
        vTexCoord = vec4(GetTexCoord(iTexCoord), gl_Position.z, gl_Position.w);
    #else
        vTexCoord = GetTexCoord(iTexCoord);
    #endif
}

