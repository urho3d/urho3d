#ifdef COMPILEVS
// Vertex shader uniforms
uniform float3 cAmbientStartColor;
uniform float3 cAmbientEndColor;
uniform float3x3 cBillboardRot;
uniform float3 cCameraPos;
uniform float3x3 cCameraRot;
uniform float cNearClip;
uniform float cFarClip;
uniform float4 cDepthMode;
uniform float cDeltaTime;
uniform float cElapsedTime;
uniform float3 cFrustumSize;
uniform float4 cGBufferOffsets;
uniform float3 cLightDir;
uniform float4 cLightPos;
uniform float4x3 cModel;
uniform float4x4 cViewProj;
uniform float4 cUOffset;
uniform float4 cVOffset;
uniform float4x3 cZone;
uniform float4x4 cLightMatrices[4];
#ifdef SKINNED
    uniform float4x3 cSkinMatrices[64];
#endif
#ifdef NUMVERTEXLIGHTS
    uniform float4 cVertexLights[4*3];
#endif
#endif

#ifdef COMPILEPS
// Pixel shader uniforms
uniform float3 cAmbientColor;
uniform float3 cCameraPosPS;
uniform float cDeltaTimePS;
uniform float4 cDepthReconstruct;
uniform float cElapsedTimePS;
uniform float4 cFogParams;
uniform float3 cFogColor;
uniform float2 cGBufferInvSize;
uniform float4 cLightColor;
uniform float4 cLightPosPS;
uniform float3 cLightDirPS;
uniform float4 cMatDiffColor;
uniform float3 cMatEmissiveColor;
uniform float3 cMatEnvMapColor;
uniform float4 cMatSpecColor;
uniform float cNearClipPS;
uniform float cFarClipPS;
uniform float4 cShadowCubeAdjust;
uniform float4 cShadowDepthFade;
uniform float2 cShadowIntensity;
uniform float2 cShadowMapInvSize;
uniform float4 cShadowSplits;
#ifdef SM3
    uniform float4x4 cLightMatricesPS[4];
#else
    uniform float4x4 cLightMatricesPS[3];
#endif
#endif
