// Vertex shader parameters
uniform float3 cCameraPos : register(C0);
uniform float3x3 cCameraRot : register(C1);
uniform float4 cDepthMode : register(C4);
uniform float3 cFrustumSize : register(C5);
uniform float4 cGBufferOffsets : register(C6);
uniform float3 cLightDir : register(C7);
uniform float4 cLightPos : register(C8);
uniform float3x3 cLightVecRot: register(C9);
uniform float4x3 cModel : register(C12);
uniform float4x4 cSpotProj : register(C15);
uniform float4x4 cViewProj : register(C19);
uniform float4 cUOffset : register(C23);
uniform float4 cVOffset : register(C24);
uniform float3 cViewRightVector : register(C25);
uniform float3 cViewUpVector : register(C26);
uniform float4x3 cZone : register(C27);
uniform float4x4 cShadowProj[4] : register(C30);
uniform float4x3 cSkinMatrices[64] : register(C46);
uniform float4 cVertexLights[6*3] : register(C238);

// Pixel shader parameters
uniform float3 cAmbientStartColor : register(C0);
uniform float3 cAmbientEndColor : register(C1);
uniform float2 cDepthReconstruct : register(C2);
uniform float4 cFogParams : register(C3);
uniform float3 cFogColor : register(C4);
uniform float4 cLightColor : register(C5);
uniform float4 cLightPosPS : register(C6);
uniform float3 cLightDirPS : register(C7);
uniform float4 cMatDiffColor : register(C8);
uniform float3 cMatEmissiveColor : register(C9);
uniform float2 cMatSpecProperties : register(C10);
uniform float2 cSampleOffsets : register(C11);
uniform float4 cShadowCubeAdjust : register(C12);
uniform float4 cShadowDepthFade : register(C13);
uniform float4 cShadowIntensity : register(C14);
uniform float4 cShadowSplits : register(C15);
uniform float4x4 cShadowProjPS[4] :  register(C16);
