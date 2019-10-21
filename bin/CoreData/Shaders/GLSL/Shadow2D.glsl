#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"

varying vec2 vScreenPos;

#ifdef COMPILEPS
uniform vec4 cShadowAmbient;
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}

void PS()
{
	vec4 diffInput = texture2D(sDiffMap, vScreenPos);
	vec4 lightInput = texture2D(sEmissiveMap, vScreenPos);
	gl_FragColor.rgb =  (diffInput.rgb * (lightInput.rgb + cShadowAmbient.rgb) * (lightInput.a + cShadowAmbient.a));    
}

