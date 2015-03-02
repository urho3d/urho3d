#ifdef COMPILEVS

#ifdef D3D11
#define OUTPOSITION SV_POSITION
#else
#define OUTPOSITION POSITION
#endif

#ifdef SKINNED
float4x3 GetSkinMatrix(float4 blendWeights, int4 blendIndices)
{
    return cSkinMatrices[blendIndices.x] * blendWeights.x +
        cSkinMatrices[blendIndices.y] * blendWeights.y +
        cSkinMatrices[blendIndices.z] * blendWeights.z +
        cSkinMatrices[blendIndices.w] * blendWeights.w;
}
#endif

float2 GetTexCoord(float2 iTexCoord)
{
    return float2(dot(iTexCoord, cUOffset.xy) + cUOffset.w, dot(iTexCoord, cVOffset.xy) + cVOffset.w);
};

float4 GetClipPos(float3 worldPos)
{
    return mul(float4(worldPos, 1.0), cViewProj);
}

float GetZonePos(float3 worldPos)
{
    return saturate(mul(float4(worldPos, 1.0), cZone).z);
}

float GetDepth(float4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

#ifdef BILLBOARD
float3 GetBillboardPos(float4 iPos, float2 iSize, float4x3 modelMatrix)
{
    return mul(iPos, modelMatrix) + mul(float3(iSize.x, iSize.y, 0.0), cBillboardRot);
}

float3 GetBillboardNormal()
{
    return float3(-cBillboardRot[2][0], -cBillboardRot[2][1], -cBillboardRot[2][2]);
}
#endif

#if defined(SKINNED)
    #define iModelMatrix GetSkinMatrix(iBlendWeights, iBlendIndices);
#elif defined(INSTANCED)
    #define iModelMatrix iModelInstance
#else
    #define iModelMatrix cModel
#endif

#ifdef BILLBOARD
    #define GetWorldPos(modelMatrix) GetBillboardPos(iPos, iSize, modelMatrix)
#else
    #define GetWorldPos(modelMatrix) mul(iPos, modelMatrix)
#endif

#ifdef BILLBOARD
    #define GetWorldNormal(modelMatrix) GetBillboardNormal()
#else
    #define GetWorldNormal(modelMatrix) normalize(mul(iNormal, (float3x3)modelMatrix))
#endif

#define GetWorldTangent(modelMatrix) normalize(mul(iTangent.xyz, (float3x3)modelMatrix))
#endif

#ifdef COMPILEPS

#ifdef D3D11
#define OUTCOLOR0 SV_TARGET
#define OUTCOLOR1 SV_TARGET1
#define OUTCOLOR2 SV_TARGET2
#define OUTCOLOR3 SV_TARGET3
#else
#define OUTCOLOR0 COLOR0
#define OUTCOLOR1 COLOR1
#define OUTCOLOR2 COLOR2
#define OUTCOLOR3 COLOR3
#endif

#endif

