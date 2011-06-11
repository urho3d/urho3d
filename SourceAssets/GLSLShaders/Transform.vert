attribute vec4 iPosition;
attribute vec3 iNormal;
attribute vec4 iColor;
attribute vec2 iTexCoord;
attribute vec2 iTexCoord2;
attribute vec3 iCubeTexCoord;
attribute vec4 iCubeTexCoord2;
attribute vec4 iTangent;
attribute vec4 iBlendWeights;
attribute vec4 iBlendIndices;

mat4 GetSkinMatrix(vec4 blendWeights, vec4 blendIndices)
{
    ivec4 idx = ivec4(blendIndices) * 3;
    const vec4 lastColumn = vec4(0.0, 0.0, 0.0, 1.0);
    return mat4(cSkinMatrices[idx.x], cSkinMatrices[idx.x + 1], cSkinMatrices[idx.x + 2], lastColumn) * blendWeights.x +
        mat4(cSkinMatrices[idx.y], cSkinMatrices[idx.y + 1], cSkinMatrices[idx.y + 2], lastColumn) * blendWeights.y +
        mat4(cSkinMatrices[idx.z], cSkinMatrices[idx.z + 1], cSkinMatrices[idx.z + 2], lastColumn) * blendWeights.z +
        mat4(cSkinMatrices[idx.w], cSkinMatrices[idx.w + 1], cSkinMatrices[idx.w + 2], lastColumn) * blendWeights.w;
}

mat3 GetNormalMatrix(mat4 modelMatrix)
{
    return mat3(modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz);
}

vec2 GetTexCoord(vec2 texCoord)
{
    return vec2(dot(texCoord, cUOffset.xy) + cUOffset.w, dot(texCoord, cVOffset.xy) + cVOffset.w);
}

float GetDepth(vec4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

vec4 GetPosition(vec4 pos, out vec4 oPos)
{
    vec4 worldPos = cModel * pos;
    oPos = cViewProj * worldPos;
    return worldPos;
}

vec4 GetPositionBillboard(vec4 pos, vec2 size, out vec4 oPos)
{
    vec4 worldPos = vec4(pos.xyz + size.x * cViewRightVector + size.y * cViewUpVector, 1.0);
    oPos = cViewProj * worldPos;
    return worldPos;
}

vec4 GetPositionSkinned(vec4 pos, vec4 blendWeights, vec4 blendIndices, out vec4 oPos)
{
    mat4 skinMatrix = GetSkinMatrix(blendWeights, blendIndices);
    vec4 worldPos = pos * skinMatrix;
    oPos = cViewProj * worldPos;
    return worldPos;
}

vec4 GetPositionNormal(vec4 pos, vec3 normal, out vec4 oPos, out vec3 oNormal)
{
    mat3 normalMatrix = GetNormalMatrix(cModel);
    vec4 worldPos = cModel * pos;
    oPos = cViewProj * worldPos;
    oNormal = normalize(normalMatrix * normal);
    return worldPos;
}

vec4 GetPositionNormalSkinned(vec4 pos, vec3 normal, vec4 blendWeights, vec4 blendIndices, out vec4 oPos, out vec3 oNormal)
{
    mat4 skinMatrix = GetSkinMatrix(blendWeights, blendIndices);
    mat3 normalMatrix = GetNormalMatrix(skinMatrix);
    vec4 worldPos = pos * skinMatrix;
    oPos = cViewProj * worldPos;
    oNormal = normalize(normal * normalMatrix);
    return worldPos;
}

vec4 GetPositionNormalTangent(vec4 pos, vec3 normal, vec4 tangent, out vec4 oPos, out vec3 oNormal, out vec3 oTangent)
{
    mat3 normalMatrix = GetNormalMatrix(cModel);
    vec4 worldPos = cModel * pos;
    oPos = cViewProj * worldPos;
    oNormal = normalize(normalMatrix * normal);
    oTangent = normalize(normalMatrix * tangent.xyz);
    return worldPos;
}

vec4 GetPositionNormalTangentSkinned(vec4 pos, vec3 normal, vec4 tangent, vec4 blendWeights, vec4 blendIndices, out vec4 oPos, out vec3 oNormal, out vec3 oTangent)
{
    mat4 skinMatrix = GetSkinMatrix(blendWeights, blendIndices);
    mat3 normalMatrix = GetNormalMatrix(skinMatrix);
    vec4 worldPos = pos * skinMatrix;
    oPos = cViewProj * worldPos;
    oNormal = normalize(normal * normalMatrix);
    oTangent = normalize(tangent.xyz * normalMatrix);
    return worldPos;
}
