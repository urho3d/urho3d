#pragma warning(disable:3571)

// Vertex shader parameters
uniform float3 cAmbientColor : register(C0);
uniform float4 cDepthMode : register(C1);
uniform float2 cElapsedTime : register(C2);
uniform float3 cFrustumSize : register(C3);
uniform float4 cGBufferOffsets : register(C4);
uniform float4x3 cModel : register(C5);
uniform float4x4 cModelViewProj : register(C8);
uniform float4x4 cShadowProj : register(C12);
uniform float4x4 cSpotProj : register(C16);
uniform float4x3 cView : register(C20);
uniform float4x3 cViewInverse : register(C23);
uniform float4x4 cViewProj : register(C26);
uniform float4 cUOffset : register(C30);
uniform float4 cVOffset : register(C31);
uniform float3 cViewRightVector : register(C32);
uniform float3 cViewUpVector : register(C33);
uniform float4x3 cModelSkinMatrices[64] : register(C34);
uniform float4x3 cModelInstances[64] : register(C34);

// Pixel shader parameters
uniform float3 cAmbientColorPS : register(C0);
uniform float2 cDepthReconstruct : register(C1);
uniform float4 cEdgeFilterParams : register(C2);
uniform float2 cElapsedTimePS : register(C3);
uniform float4 cFogParams: register(C4);
uniform float3 cFogColor : register(C5);
uniform float cLightAtten : register(C6);
uniform float4 cLightColor : register(C7);
uniform float3 cLightDir : register(C8);
uniform float3 cLightPos : register(C9);
uniform float4 cLightSplits : register(C10);
uniform float4 cMatDiffColor : register(C11);
uniform float3 cMatEmissiveColor : register(C12);
uniform float2 cMatSpecProperties : register(C13);
uniform float4 cSampleOffsets : register(C14);
uniform float2 cShadowIntensity : register(C15);
uniform float4x4 cShadowProjPS : register(C16);
uniform float4x4 cSpotProjPS : register(C20);

// Material map samplers
sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sDetailMap : register(S3);
sampler2D sEnvMap : register(S4);
samplerCUBE sEnvCubeMap : register(S4);
sampler2D sEmissiveMap : register(S5);

// Rendertarget samplers
sampler2D sDiffBuffer : register(S0);
sampler2D sNormalBuffer : register(S1);
sampler2D sDepthBuffer : register(S2);
sampler2D sLightBuffer : register(S6);

// Shadow and light shape samplers
sampler2D sShadowMap : register(S5);
sampler1D sLightRampMap : register(S6);
sampler2D sLightSpotMap : register(S7);
samplerCUBE sLightCubeMap : register(S7);

float4 sample(sampler2D map, float2 texCoord)
{
    // use tex2Dlod if available to avoid divergence
    #ifdef SM3
        return tex2Dlod(map, float4(texCoord, 0.0, 0.0));
    #else
        return tex2D(map, texCoord);
    #endif
}

float4 calculateScreenPos(float4 clipPos)
{
    return float4(
        clipPos.x * cGBufferOffsets.z + (cGBufferOffsets.x + cGBufferOffsets.z) * clipPos.w,
        -clipPos.y * cGBufferOffsets.w + (cGBufferOffsets.y + cGBufferOffsets.w) * clipPos.w,
        0.0,
        clipPos.w);
}

float2 calculateScreenPosPreDiv(float4 clipPos)
{
    return float2(
        clipPos.x / clipPos.w * cGBufferOffsets.z + (cGBufferOffsets.x + cGBufferOffsets.z),
        -clipPos.y / clipPos.w * cGBufferOffsets.w + (cGBufferOffsets.y + cGBufferOffsets.w));
}

float3 calculateWorldFarRay(float4 clipPos)
{
    float3 viewRay = float3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        cFrustumSize.z);

    return mul(viewRay, (float3x3)cViewInverse);
}

float3 calculateWorldNearRay(float4 clipPos)
{
    float3 viewRay = float3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        0.0);

    return mul(viewRay, (float3x3)cViewInverse) * cDepthMode.z;
}

float calculateDepth(float4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

float reconstructDepth(float hwDepth)
{
    return cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x);
}

float4 reconstructDepth(float4 hwDepth)
{
    return cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x);
}

float3 adjustWorldPos(float3 worldPos)
{
    return worldPos - float3(cViewInverse[3][0], cViewInverse[3][1], cViewInverse[3][2]);
}

float3 adjustWorldPos(float4 worldPos)
{
    return worldPos.xyz - float3(cViewInverse[3][0], cViewInverse[3][1], cViewInverse[3][2]);
}

float3 unpackNormal(float4 normalInput)
{
    float3 normal;
    normal.xy = normalInput.ag * 2.0 - 1.0;
    normal.z = sqrt(1.0 - dot(normal.xy, normal.xy));
    return normal;
}

float4 evaluatePosition(float4 iPos, out float4 oPos)
{
    oPos = mul(iPos, cModelViewProj);
    return float4(mul(iPos, cModel), 1.0);
}

float4 evaluatePositionBillboard(float4 iPos, float2 iSize, out float4 oPos)
{
    float4 tempPos = float4(iPos.xyz + iSize.x * cViewRightVector + iSize.y * cViewUpVector, 1.0);
    oPos = mul(tempPos, cViewProj);
    return tempPos;
}

float4 evaluatePositionSkinned(float4 iPos, float4 iBlendWeights, int4 iBlendIndices, out float4 oPos)
{
    float4x3 skinMatrix =
        cModelSkinMatrices[iBlendIndices.x] * iBlendWeights.x +
        cModelSkinMatrices[iBlendIndices.y] * iBlendWeights.y +
        cModelSkinMatrices[iBlendIndices.z] * iBlendWeights.z +
        cModelSkinMatrices[iBlendIndices.w] * iBlendWeights.w;
    
    float4 tempPos = float4(mul(iPos, skinMatrix), 1.0);
    oPos = mul(tempPos, cViewProj);
    return tempPos;
}

float4 evaluatePositionInstanced(float4 iPos, float4x3 iModel, out float4 oPos)
{
    float4 tempPos = float4(mul(iPos, iModel), 1.0);
    oPos = mul(tempPos, cViewProj);
    return tempPos;
}

float4 evaluatePositionNormal(float4 iPos, float3 iNormal, out float4 oPos, out float3 oNormal)
{
    oPos = mul(iPos, cModelViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)cModel));
    return float4(mul(iPos, cModel), 1.0);
}

float4 evaluatePositionNormalSkinned(float4 iPos, float3 iNormal, float4 iBlendWeights, int4 iBlendIndices, out float4 oPos, out float3 oNormal)
{
    float4x3 skinMatrix =
        cModelSkinMatrices[iBlendIndices.x] * iBlendWeights.x +
        cModelSkinMatrices[iBlendIndices.y] * iBlendWeights.y +
        cModelSkinMatrices[iBlendIndices.z] * iBlendWeights.z +
        cModelSkinMatrices[iBlendIndices.w] * iBlendWeights.w;

    float4 tempPos = float4(mul(iPos, skinMatrix), 1.0);
    float3 tempNormal = mul(iNormal, (float3x3)skinMatrix);
    oPos = mul(tempPos, cViewProj);
    oNormal = normalize(tempNormal);
    return tempPos;
}

float4 evaluatePositionNormalInstanced(float4 iPos, float3 iNormal, float4x3 iModel, out float4 oPos, out float3 oNormal)
{
    float4 tempPos = float4(mul(iPos, iModel), 1.0);
    float3 tempNormal = mul(iNormal, (float3x3)iModel);
    oPos = mul(tempPos, cViewProj);
    oNormal = normalize(tempNormal);
    return tempPos;
}

float4 evaluatePositionNormalTangent(float4 iPos, float3 iNormal, float4 iTangent, out float4 oPos, out float3 oNormal, out float3 oTangent)
{
    oPos = mul(iPos, cModelViewProj);
    oNormal = normalize(mul(iNormal, (float3x3)cModel));
    oTangent = normalize(mul(iTangent.xyz, (float3x3)cModel));
    return float4(mul(iPos, cModel), 1.0);
}

float4 evaluatePositionNormalTangentSkinned(float4 iPos, float3 iNormal, float4 iTangent, float4 iBlendWeights, int4 iBlendIndices, out float4 oPos, out float3 oNormal, out float3 oTangent)
{
    float4x3 skinMatrix =
        cModelSkinMatrices[iBlendIndices.x] * iBlendWeights.x +
        cModelSkinMatrices[iBlendIndices.y] * iBlendWeights.y +
        cModelSkinMatrices[iBlendIndices.z] * iBlendWeights.z +
        cModelSkinMatrices[iBlendIndices.w] * iBlendWeights.w;

    float4 tempPos = float4(mul(iPos, skinMatrix), 1.0);
    float3 tempNormal = mul(iNormal, (float3x3)skinMatrix);
    float3 tempTangent = mul(iTangent.xyz, (float3x3)skinMatrix);
    oPos = mul(tempPos, cViewProj);
    oNormal = normalize(tempNormal);
    oTangent = normalize(tempTangent);
    return tempPos;
}

float4 evaluatePositionNormalTangentInstanced(float4 iPos, float3 iNormal, float4 iTangent, float4x3 iModel, out float4 oPos, out float3 oNormal, out float3 oTangent)
{
    float4 tempPos = float4(mul(iPos, iModel), 1.0);
    float3 tempNormal = mul(iNormal, (float3x3)iModel);
    float3 tempTangent = mul(iTangent.xyz, (float3x3)iModel);
    oPos = mul(tempPos, cViewProj);
    oNormal = normalize(tempNormal);
    oTangent = normalize(tempTangent);
    return tempPos;
}

float2 evaluateTexCoord(float2 iTexCoord)
{
    return float2(dot(iTexCoord, cUOffset.xy) + cUOffset.w, dot(iTexCoord, cVOffset.xy) + cVOffset.w);
};

float evaluateDiffuseDir(float3 normal, out float3 lightDir)
{
    lightDir = cLightDir;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL;
}

float evaluateDiffusePointOrSpot(float3 normal, float3 worldPos, out float3 lightDir, out float3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten.x;
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL * tex1D(sLightRampMap, lightDist).r;
}

float evaluateDiffuseDirVolumetric()
{
    return 1.0;
}

float evaluateDiffusePointOrSpotVolumetric(float3 worldPos, out float3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten.x;
    float lightDist = length(lightVec);
    return tex1D(sLightRampMap, lightDist).r;
}

float evaluateSplitFade(float depth)
{
    float nearFadeFactor = saturate((depth - cLightSplits.x) * cLightSplits.y);
    float farFadeFactor = 1.0 - saturate((depth - cLightSplits.z) * cLightSplits.w);
    return nearFadeFactor * farFadeFactor;
}

float evaluateSpecular(float3 normal, float3 worldPos, float3 lightDir, float specularPower)
{
    float3 eyeDir = normalize(-worldPos);
    float3 halfDir = normalize(eyeDir + lightDir);
    return pow(dot(normal, halfDir), specularPower);
}

float evaluateShadow(float4 shadowPos)
{
    // Take four samples and average them
    float4 pcfValues = cShadowIntensity.x;
    #ifdef SM3
        float2 ofs = cSampleOffsets.xy;
        float4 projShadowPos = float4(shadowPos.xyz / shadowPos.w, 0.0);
        float4 inLight = float4(
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.x, ofs.x), projShadowPos.zw)).r,
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.y, ofs.x), projShadowPos.zw)).r,
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.x, ofs.y), projShadowPos.zw)).r,
            tex2Dlod(sShadowMap, float4(projShadowPos.xy + float2(ofs.y, ofs.y), projShadowPos.zw)).r
        );
        #ifdef HWSHADOW
            return cShadowIntensity.y + dot(inLight, pcfValues);
        #else
            return cShadowIntensity.y + dot(inLight > projShadowPos.z, pcfValues);
        #endif
    #else
        float2 projOfs = cSampleOffsets.xy * shadowPos.w;
        float4 inLight = float4(
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.x, projOfs.x), shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.y, projOfs.x), shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.x, projOfs.y), shadowPos.zw)).r,
            tex2Dproj(sShadowMap, float4(shadowPos.xy + float2(projOfs.y, projOfs.y), shadowPos.zw)).r
        );
        #ifdef HWSHADOW
            return cShadowIntensity.y + dot(inLight, pcfValues);
        #else
            return cShadowIntensity.y + dot((inLight * shadowPos.w) > shadowPos.z, pcfValues);
        #endif
    #endif
}

float3 evaluateFog(float3 color, float depth)
{
    return lerp(color, cFogColor, saturate((depth - cFogParams.x) * cFogParams.z));
}

float3 evaluateLitFog(float3 color, float depth)
{
    return color * saturate((cFogParams.y - depth) * cFogParams.z);
}

float evaluateFogFactor(float depth)
{
    return saturate((depth - cFogParams.x) * cFogParams.z);
}

float evaluateReverseFogFactor(float depth)
{
    return saturate((cFogParams.y - depth) * cFogParams.z);
}

