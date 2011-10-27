attribute vec4 iPos;
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

vec4 GetClipPos(vec3 worldPos)
{
    return cViewProj * vec4(worldPos, 1.0);
}

float GetDepth(vec4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

vec3 GetBillboardPos(vec4 iPos, vec2 iSize)
{
    return vec3(iPos.xyz + iSize.x * cViewRightVector + iSize.y * cViewUpVector);
}

vec3 GetBillboardNormal()
{
    return vec3(-cCameraRot[2][0], -cCameraRot[2][1], -cCameraRot[2][2]);
}

#ifdef SKINNED
    #define iModelMatrix GetSkinMatrix(iBlendWeights, iBlendIndices)
#else
    #define iModelMatrix cModel
#endif

vec3 GetWorldPos(mat4 modelMatrix)
{
    #if defined(BILLBOARD)
        return GetBillboardPos(iPos, iTexCoord2);
    #elif defined(SKINNED)
        return (iPos * modelMatrix).xyz;
    #else
        return (modelMatrix * iPos).xyz;
    #endif
}

vec3 GetWorldNormal(mat4 modelMatrix)
{
    #if defined(BILLBOARD)
        return GetBillboardNormal();
    #elif defined(SKINNED)
        return normalize(iNormal * GetNormalMatrix(modelMatrix));
    #else
        return normalize(GetNormalMatrix(modelMatrix) * iNormal);
    #endif
}

vec3 GetWorldTangent(mat4 modelMatrix)
{   
    mat3 normalMatrix = GetNormalMatrix(modelMatrix);
    #ifdef SKINNED
        return normalize(iTangent.xyz * normalMatrix);
    #else
        return normalize(normalMatrix * iTangent.xyz);
    #endif
}

