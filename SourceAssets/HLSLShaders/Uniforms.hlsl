// Vertex shader parameters
uniform float3 cCameraPos : register(C0);
uniform float3x3 cCameraRot : register(C1);
uniform float4 cDepthMode : register(C4);
uniform float2 cElapsedTime : register(C5);
uniform float cLightAtten : register(C6);
uniform float3 cLightDir : register(C7);
uniform float3 cLightPos : register(C8);
uniform float3x3 cLightVecRot: register(C9);
uniform float4x3 cModel : register(C12);
uniform float4x4 cSpotProj : register(C15);
uniform float4x4 cViewProj : register(C19);
uniform float4 cUOffset : register(C23);
uniform float4 cVOffset : register(C24);
uniform float3 cViewRightVector : register(C25);
uniform float3 cViewUpVector : register(C26);
uniform float4x4 cShadowProj[4] : register(C27);
uniform float4x3 cSkinMatrices[64] : register(C43);

// Pixel shader parameters
uniform float3 cAmbientColor : register(C0);
uniform float2 cElapsedTimePS : register(C1);
uniform float4 cFogParams : register(C2);
uniform float3 cFogColor : register(C3);
uniform float4 cLightColor : register(C4);
uniform float4 cMatDiffColor : register(C5);
uniform float3 cMatEmissiveColor : register(C6);
uniform float2 cMatSpecProperties : register(C7);
uniform float4 cSampleOffsets : register(C8);
uniform float4 cShadowCubeAdjust : register(C9);
uniform float2 cShadowCubeProj : register(C10);
uniform float2 cShadowFade : register(C11);
uniform float4 cShadowIntensity : register(C12);
uniform float4 cShadowSplits : register(C13);
