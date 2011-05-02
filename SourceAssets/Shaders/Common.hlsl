#pragma warning(disable:3571)

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
uniform float4 cAntiAliasWeights : register(C1);
uniform float3 cCameraPosPS : register(C2);
uniform float2 cElapsedTimePS : register(C3);
uniform float4 cFogParams : register(C4);
uniform float3 cFogColor : register(C5);
uniform float4 cGBufferOffsetsPS : register(C6);
uniform float4 cGBufferViewport : register(C7);
uniform float cLightAtten : register(C8);
uniform float4 cLightColor : register(C9);
uniform float3 cLightDir : register(C10);
uniform float3 cLightPos : register(C11);
uniform float4 cLightSplits : register(C12);
uniform float3x3 cLightVecRot: register(C13);
uniform float4 cMatDiffColor : register(C16);
uniform float3 cMatEmissiveColor : register(C17);
uniform float2 cMatSpecProperties : register(C18);
uniform float4 cSampleOffsets : register(C19);
uniform float2 cShadowIntensity : register(C20);
uniform float4x4 cShadowProjPS : register(C21);
uniform float4x4 cSpotProjPS : register(C25);
uniform float4x4 cViewProjPS : register(C25);

// Material map samplers
sampler2D sDiffMap : register(S0);
samplerCUBE sDiffCubeMap : register(S0);
sampler2D sNormalMap : register(S1);
sampler2D sSpecMap : register(S2);
sampler2D sDetailMap : register(S3);
sampler2D sEnvMap : register(S4);
samplerCUBE sEnvCubeMap : register(S4);
sampler2D sEmissiveMap : register(S5);

// Shadow and light shape samplers
sampler2D sShadowMap : register(S5);
sampler1D sLightRampMap : register(S6);
sampler2D sLightSpotMap : register(S7);
samplerCUBE sLightCubeMap : register(S7);

// Rendertarget samplers
sampler2D sDiffBuffer : register(S0);
sampler2D sNormalBuffer : register(S1);
sampler2D sDepthBuffer : register(S2);
sampler2D sLightBuffer : register(S6);

float4 Sample(sampler2D map, float2 texCoord)
{
    // Use tex2Dlod if available to avoid divergence and allow branching
    #ifdef SM3
        return tex2Dlod(map, float4(texCoord, 0.0, 0.0));
    #else
        return tex2D(map, texCoord);
    #endif
}

float GetDepth(float4 clipPos)
{
    return dot(clipPos.zw, cDepthMode.zw);
}

float4 GetScreenPos(float4 clipPos)
{
    return float4(
        clipPos.x * cGBufferOffsets.z + cGBufferOffsets.x * clipPos.w,
        -clipPos.y * cGBufferOffsets.w + cGBufferOffsets.y * clipPos.w,
        0.0,
        clipPos.w);
}

float2 GetScreenPosPreDiv(float4 clipPos)
{
    return float2(
        clipPos.x / clipPos.w * cGBufferOffsets.z + cGBufferOffsets.x,
        -clipPos.y / clipPos.w * cGBufferOffsets.w + cGBufferOffsets.y);
}

float3 GetFarRay(float4 clipPos)
{
    float3 viewRay = float3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        cFrustumSize.z);

    return mul(viewRay, cCameraRot);
}

float3 GetNearRay(float4 clipPos)
{
    float3 viewRay = float3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        0.0);
    
    return mul(viewRay, cCameraRot) * cDepthMode.z;
}

float GetIntensity(float3 color)
{
    return dot(color, float3(0.333, 0.333, 0.333));
}

float3 UnpackNormal(float4 normalInput)
{
    float3 normal;
    normal.xy = normalInput.ag * 2.0 - 1.0;
    normal.z = sqrt(1.0 - dot(normal.xy, normal.xy));
    return normal;
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
    float4x3 skinMatrix =
        cSkinMatrices[iBlendIndices.x] * iBlendWeights.x +
        cSkinMatrices[iBlendIndices.y] * iBlendWeights.y +
        cSkinMatrices[iBlendIndices.z] * iBlendWeights.z +
        cSkinMatrices[iBlendIndices.w] * iBlendWeights.w;
    
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
    float4x3 skinMatrix =
        cSkinMatrices[iBlendIndices.x] * iBlendWeights.x +
        cSkinMatrices[iBlendIndices.y] * iBlendWeights.y +
        cSkinMatrices[iBlendIndices.z] * iBlendWeights.z +
        cSkinMatrices[iBlendIndices.w] * iBlendWeights.w;

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
    float4x3 skinMatrix =
        cSkinMatrices[iBlendIndices.x] * iBlendWeights.x +
        cSkinMatrices[iBlendIndices.y] * iBlendWeights.y +
        cSkinMatrices[iBlendIndices.z] * iBlendWeights.z +
        cSkinMatrices[iBlendIndices.w] * iBlendWeights.w;

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

float2 GetTexCoord(float2 iTexCoord)
{
    return float2(dot(iTexCoord, cUOffset.xy) + cUOffset.w, dot(iTexCoord, cVOffset.xy) + cVOffset.w);
};

float GetDiffuseDir(float3 normal, out float3 lightDir)
{
    lightDir = cLightDir;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL;
}

float GetDiffusePointOrSpot(float3 normal, float3 worldPos, out float3 lightDir, out float3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten.x;
    float lightDist = length(lightVec);
    lightDir = lightVec / lightDist;
    float NdotL = max(dot(normal, lightDir), 0.0);
    return NdotL * tex1D(sLightRampMap, lightDist).r;
}

float GetDiffuseDirVolumetric()
{
    return 1.0;
}

float GetDiffusePointOrSpotVolumetric(float3 worldPos, out float3 lightVec)
{
    lightVec = (cLightPos - worldPos) * cLightAtten.x;
    float lightDist = length(lightVec);
    return tex1D(sLightRampMap, lightDist).r;
}

float GetSplitFade(float depth)
{
    float nearFadeFactor = saturate((depth - cLightSplits.x) * cLightSplits.y);
    float farFadeFactor = 1.0 - saturate((depth - cLightSplits.z) * cLightSplits.w);
    return nearFadeFactor * farFadeFactor;
}

float GetSpecular(float3 normal, float3 worldPos, float3 lightDir, float specularPower)
{
    float3 eyeDir = normalize(-worldPos);
    float3 halfDir = normalize(eyeDir + lightDir);
    return pow(dot(normal, halfDir), specularPower);
}

float GetShadow(float4 shadowPos)
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

float3 GetFog(float3 color, float depth)
{
    return lerp(color, cFogColor, saturate((depth - cFogParams.x) * cFogParams.z));
}

float3 GetLitFog(float3 color, float depth)
{
    return color * saturate((cFogParams.y - depth) * cFogParams.z);
}

float GetFogFactor(float depth)
{
    return saturate((depth - cFogParams.x) * cFogParams.z);
}

float GetReverseFogFactor(float depth)
{
    return saturate((cFogParams.y - depth) * cFogParams.z);
}
