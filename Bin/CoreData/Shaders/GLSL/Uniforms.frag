#ifdef GL_ES
    precision mediump float;
#endif

uniform vec3 cAmbientColor;
uniform float cDeltaTimePS;
uniform float cElapsedTimePS;
uniform vec4 cFogParams;
uniform vec3 cFogColor;
uniform vec2 cGBufferInvSize;
uniform vec4 cLightColor;
uniform vec3 cLightDirPS;
uniform vec4 cLightPosPS;
uniform vec4 cMatDiffColor;
uniform vec3 cMatEmissiveColor;
uniform vec3 cMatEnvMapColor;
uniform vec4 cMatSpecColor;
uniform float cNearClipPS;
uniform float cFarClipPS;
uniform vec4 cShadowCubeAdjust;
uniform vec4 cShadowDepthFade;
uniform vec2 cShadowIntensity;
uniform vec2 cShadowMapInvSize;
uniform vec4 cShadowSplits;
uniform mat4 cLightMatricesPS[4];
