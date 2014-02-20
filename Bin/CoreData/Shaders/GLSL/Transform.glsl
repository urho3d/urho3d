#ifdef COMPILEVS
attribute vec4 iPos;
attribute vec3 iNormal;
attribute vec4 iColor;
attribute vec2 iTexCoord;
attribute vec2 iTexCoord2;
attribute vec4 iTangent;
attribute vec4 iBlendWeights;
attribute vec4 iBlendIndices;
attribute vec3 iCubeTexCoord;
attribute vec4 iCubeTexCoord2;
#ifndef GL_ES
    attribute vec4 iInstanceMatrix1;
    attribute vec4 iInstanceMatrix2;
    attribute vec4 iInstanceMatrix3;
#endif

#ifdef SKINNED
mat4 GetSkinMatrix(vec4 blendWeights, vec4 blendIndices)
{
    ivec4 idx = ivec4(blendIndices) * 3;
    const vec4 lastColumn = vec4(0.0, 0.0, 0.0, 1.0);
    return mat4(cSkinMatrices[idx.x], cSkinMatrices[idx.x + 1], cSkinMatrices[idx.x + 2], lastColumn) * blendWeights.x +
        mat4(cSkinMatrices[idx.y], cSkinMatrices[idx.y + 1], cSkinMatrices[idx.y + 2], lastColumn) * blendWeights.y +
        mat4(cSkinMatrices[idx.z], cSkinMatrices[idx.z + 1], cSkinMatrices[idx.z + 2], lastColumn) * blendWeights.z +
        mat4(cSkinMatrices[idx.w], cSkinMatrices[idx.w + 1], cSkinMatrices[idx.w + 2], lastColumn) * blendWeights.w;
}
#endif

#ifdef INSTANCED
mat4 GetInstanceMatrix()
{
    const vec4 lastColumn = vec4(0.0, 0.0, 0.0, 1.0);
    return mat4(iInstanceMatrix1, iInstanceMatrix2, iInstanceMatrix3, lastColumn);
}
#endif

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
    vec4 ret = cViewProj * vec4(worldPos, 1.0);
    // While getting the clip coordinate, also automatically set gl_ClipVertex for user clip planes
    #ifndef GL_ES
    gl_ClipVertex = ret;
    #endif
    return ret;
}

float GetZonePos(vec3 worldPos)
{
    return clamp((cZone * vec4(worldPos, 1.0)).z, 0.0, 1.0);
}

float GetDepth(vec4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

vec3 GetBillboardPos(vec4 iPos, vec2 iSize, mat4 modelMatrix)
{
    return (modelMatrix * iPos).xyz + cBillboardRot * vec3(iSize.x, iSize.y, 0.0);
}

vec3 GetBillboardNormal()
{
    return vec3(-cBillboardRot[2][0], -cBillboardRot[2][1], -cBillboardRot[2][2]);
}

// Note: the skinning/instancing model matrix is a transpose, so the matrix multiply order must be swapped
// (see GetWorldPos(), GetWorldNormal() and GetWorldTangent() below)
#if defined(SKINNED)
    #define iModelMatrix GetSkinMatrix(iBlendWeights, iBlendIndices)
#elif defined(INSTANCED)
    #define iModelMatrix GetInstanceMatrix();
#else
    #define iModelMatrix cModel
#endif

vec3 GetWorldPos(mat4 modelMatrix)
{
    #if defined(SKINNED) || defined(INSTANCED)
        return (iPos * modelMatrix).xyz;
    #elif defined(BILLBOARD)
        return GetBillboardPos(iPos, iTexCoord2, modelMatrix);
    #else
        return (modelMatrix * iPos).xyz;
    #endif
}

vec3 GetWorldNormal(mat4 modelMatrix)
{
    #if defined(SKINNED) || defined(INSTANCED)
        return normalize(iNormal * GetNormalMatrix(modelMatrix));
    #elif defined(BILLBOARD)
        return GetBillboardNormal();
    #else
        return normalize(GetNormalMatrix(modelMatrix) * iNormal);
    #endif
}

vec3 GetWorldTangent(mat4 modelMatrix)
{   
    mat3 normalMatrix = GetNormalMatrix(modelMatrix);
    #if defined(SKINNED) || defined(INSTANCED)
        return normalize(iTangent.xyz * normalMatrix);
    #else
        return normalize(normalMatrix * iTangent.xyz);
    #endif
}
#endif
