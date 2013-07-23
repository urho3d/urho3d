uniform vec3 cAmbientStartColor;
uniform vec3 cAmbientEndColor;
uniform vec3 cCameraPos;
uniform mat3 cCameraRot;
uniform vec4 cDepthMode;
uniform vec3 cFrustumSize;
uniform float cElapsedTime;
uniform vec4 cGBufferOffsets;
uniform vec3 cLightDir;
uniform vec4 cLightPos;
uniform mat4 cModel;
uniform mat4 cViewProj;
uniform vec4 cUOffset;
uniform vec4 cVOffset;
uniform vec3 cViewRightVector;
uniform vec3 cViewUpVector;
uniform mat4 cZone;
#ifndef GL_ES
    uniform mat4 cLightMatrices[4];
#else
    uniform mat4 cLightMatrices[2];
#endif
#ifdef SKINNED
    uniform vec4 cSkinMatrices[64*3];
#endif
#ifdef NUMVERTEXLIGHTS
    uniform vec4 cVertexLights[4*3];
#endif