// Vertex shader uniforms
uniform float3 cAmbientStartColor;
uniform float3 cAmbientEndColor;
uniform float3 cCameraPos;
uniform float3x3 cCameraRot;
uniform float4 cDepthMode;
uniform float3 cFrustumSize;
uniform float4 cGBufferOffsets;
uniform float3 cLightDir;
uniform float4 cLightPos;
uniform float4x3 cModel;
uniform float4x4 cViewProj;
uniform float4 cUOffset;
uniform float4 cVOffset;
uniform float3 cViewRightVector;
uniform float3 cViewUpVector;
uniform float4x3 cZone;
uniform float4x4 cLightMatrices[4];
uniform float4x3 cSkinMatrices[64];
uniform float4 cVertexLights[6*3];

// Pixel shader uniforms
uniform float3 cAmbientColor;
uniform float2 cDepthReconstruct;
uniform float2 cFogParams;
uniform float3 cFogColor;
uniform float2 cGBufferInvSize;
uniform float4 cLightColor;
uniform float4 cLightPosPS;
uniform float3 cLightDirPS;
uniform float4 cMatDiffColor;
uniform float3 cMatEmissiveColor;
uniform float3 cMatEnvMapColor;
uniform float4 cMatSpecColor;
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
