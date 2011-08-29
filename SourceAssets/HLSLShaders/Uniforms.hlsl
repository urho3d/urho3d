// Vertex shader parameters
uniform float3 cCameraPos : register(C0);
uniform float3x3 cCameraRot : register(C1);
uniform float4 cDepthMode : register(C4);
uniform float2 cElapsedTime : register(C5);
uniform float4 cFrustumSize : register(C6);
uniform float4 cGBufferOffsets : register(C7);
uniform float4x3 cModel : register(C8);
uniform float4x4 cShadowProj : register(C11);
uniform float4x4 cSpotProj : register(C15);
uniform float4x4 cViewProj : register(C19);
uniform float4 cUOffset : register(C23);
uniform float4 cVOffset : register(C24);
uniform float3 cViewRightVector : register(C25);
uniform float3 cViewUpVector : register(C26);
uniform float4x3 cSkinMatrices[64] : register(C27);

// Pixel shader parameters
uniform float3 cAmbientColor : register(C0);
uniform float2 cDepthReconstruct : register(C1);
uniform float4 cEdgeFilterParams : register(C2);
uniform float2 cElapsedTimePS : register(C3);
uniform float4 cFogParams : register(C4);
uniform float3 cFogColor : register(C5);
uniform float cLightAtten : register(C6);
uniform float4 cLightColor : register(C7);
uniform float3 cLightDir : register(C8);
uniform float3 cLightPos : register(C9);
uniform float4 cLightSplits : register(C10);
uniform float3x3 cLightVecRot: register(C11);
uniform float4 cMatDiffColor : register(C14);
uniform float3 cMatEmissiveColor : register(C15);
uniform float2 cMatSpecProperties : register(C16);
uniform float4 cSampleOffsets : register(C17);
uniform float2 cShadowIntensity : register(C18);
uniform float4x4 cShadowProjPS : register(C19);
uniform float4x4 cSpotProjPS : register(C23);
