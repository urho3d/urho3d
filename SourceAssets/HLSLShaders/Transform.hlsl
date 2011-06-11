float4x3 GetSkinMatrix(float4 blendWeights, int4 blendIndices)
{
    return cSkinMatrices[blendIndices.x] * blendWeights.x +
        cSkinMatrices[blendIndices.y] * blendWeights.y +
        cSkinMatrices[blendIndices.z] * blendWeights.z +
        cSkinMatrices[blendIndices.w] * blendWeights.w;
}

float2 GetTexCoord(float2 iTexCoord)
{
    return float2(dot(iTexCoord, cUOffset.xy) + cUOffset.w, dot(iTexCoord, cVOffset.xy) + cVOffset.w);
};

float GetDepth(float4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

float4 GetPosition(float4 iPos, out float4 oPos)
{
    float4 worldPos = float4(mul(iPos, cModel), 1.0);
    oPos = mul(worldPos, cViewProj);
    return worldPos;
}

float4 GetPositionBillboard(float4 iPos, float2 iSize, out float4 oPos)
{
    float4 worldPos = float4(iPos.xyz + iSize.x * cViewRightVector + iSize.y * cViewUpVector, 1.0);
    oPos = mul(worldPos, cViewProj);
    return worldPos;
}

float4 GetPositionSkinned(float4 iPos, float4 iBlendWeights, int4 iBlendIndices, out float4 oPos)
{
    float4x3 skinMatrix = GetSkinMatrix(iBlendWeights, iBlendIndices);
    float4 worldPos = float4(mul(iPos, skinMatrix), 1.0);
    oPos = mul(worldPos, cViewProj);
    return worldPos;
}

float4 GetPositionInstanced(float4 iPos, float4x3 iModel, out float4 oPos)
{
    float4 worldPos = float4(mul(iPos, iModel), 1.0);
    oPos = mul(worldPos, cViewProj);
    return worldPos;
}

float4 GetPositionNormal(float4 iPos, float3 iNormal, out float4 oPos, out float3 oNormal)
{
    float4 worldPos = float4(mul(iPos, cModel), 1.0);
    oPos = mul(worldPos, cViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)cModel));
    return worldPos;
}

float4 GetPositionNormalSkinned(float4 iPos, float3 iNormal, float4 iBlendWeights, int4 iBlendIndices, out float4 oPos, out float3 oNormal)
{
    float4x3 skinMatrix = GetSkinMatrix(iBlendWeights, iBlendIndices);
    float4 worldPos = float4(mul(iPos, skinMatrix), 1.0);
    oPos = mul(worldPos, cViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)skinMatrix));
    return worldPos;
}

float4 GetPositionNormalInstanced(float4 iPos, float3 iNormal, float4x3 iModel, out float4 oPos, out float3 oNormal)
{
    float4 worldPos = float4(mul(iPos, iModel), 1.0);
    oPos = mul(worldPos, cViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)iModel));
    return worldPos;
}

float4 GetPositionNormalTangent(float4 iPos, float3 iNormal, float4 iTangent, out float4 oPos, out float3 oNormal, out float3 oTangent)
{
    float4 worldPos = float4(mul(iPos, cModel), 1.0);
    oPos = mul(worldPos, cViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)cModel));
    oTangent = normalize(mul(iTangent.xyz, (float3x3)cModel));
    return worldPos;
}

float4 GetPositionNormalTangentSkinned(float4 iPos, float3 iNormal, float4 iTangent, float4 iBlendWeights, int4 iBlendIndices, out float4 oPos, out float3 oNormal, out float3 oTangent)
{
    float4x3 skinMatrix = GetSkinMatrix(iBlendWeights, iBlendIndices);
    float4 worldPos = float4(mul(iPos, skinMatrix), 1.0);
    oPos = mul(worldPos, cViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)skinMatrix));
    oTangent = normalize(mul(iTangent.xyz, (float3x3)skinMatrix));
    return worldPos;
}

float4 GetPositionNormalTangentInstanced(float4 iPos, float3 iNormal, float4 iTangent, float4x3 iModel, out float4 oPos, out float3 oNormal, out float3 oTangent)
{
    float4 worldPos = float4(mul(iPos, iModel), 1.0);
    oPos = mul(worldPos, cViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)iModel));
    oTangent = normalize(mul(iTangent.xyz, (float3x3)iModel));
    return worldPos;
}
