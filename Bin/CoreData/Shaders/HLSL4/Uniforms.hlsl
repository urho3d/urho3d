#ifdef COMPILEVS
// Vertex shader uniforms
cbuffer FrameVS : register(b0)
{
    float cDeltaTime;
    float cElapsedTime;
}

cbuffer CameraVS : register(b1)
{
    float3 cCameraPos;
    float3x3 cCameraRot;
    float cNearClip;
    float cFarClip;
    float4 cDepthMode;
    float3 cFrustumSize;
    float4 cGBufferOffsets;
    float4x4 cViewProj;
}

cbuffer ZoneVS : register(b2)
{
    float3 cAmbientStartColor;
    float3 cAmbientEndColor;
    float4x3 cZone;
}

cbuffer LightVS : register(b3)
{
    float3 cLightDir;
    float4 cLightPos;
    #ifdef NUMVERTEXLIGHTS
        float4 cVertexLights[4*3];
    #else
        float4x4 cLightMatrices[4];
    #endif
}

cbuffer MaterialVS : register(b4)
{
    float4 cUOffset;
    float4 cVOffset;
}

cbuffer ObjectVS : register(b5)
{
    float4x3 cModel;
    #ifdef BILLBOARD
        float3x3 cBillboardRot;
    #endif
    #ifdef SKINNED
        uniform float4x3 cSkinMatrices[64];
    #endif
}
#endif

#ifdef COMPILEPS
// Pixel shader uniforms
cbuffer FramePS : register(b0)
{
    float cDeltaTimePS;
    float cElapsedTimePS;
}

cbuffer CameraPS : register(b1)
{
    float3 cCameraPosPS;
    float4 cDepthReconstruct;
    float2 cGBufferInvSize;
    float cNearClipPS;
    float cFarClipPS;
}

cbuffer ZonePS : register(b2)
{
    float3 cAmbientColor;
    float4 cFogParams;
    float3 cFogColor;
}

cbuffer LightPS : register(b3)
{
    float4 cLightColor;
    float4 cLightPosPS;
    float3 cLightDirPS;
    float4 cShadowCubeAdjust;
    float4 cShadowDepthFade;
    float2 cShadowIntensity;
    float2 cShadowMapInvSize;
    float4 cShadowSplits;
    float4x4 cLightMatricesPS[4];
}

cbuffer MaterialPS : register(b4)
{
    float4 cMatDiffColor;
    float3 cMatEmissiveColor;
    float3 cMatEnvMapColor;
    float4 cMatSpecColor;
}
#endif
