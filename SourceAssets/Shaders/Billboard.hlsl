#include "Common.hlsl"

void vs(float4 iPos : POSITION,
    float4 iColor : COLOR,
    float2 iTexCoord : TEXCOORD0,
    float2 iSize : TEXCOORD1,
    out float4 oWorldPos : TEXCOORD1,
    #ifdef SPOTLIGHT
        out float4 oSpotPos : TEXCOORD2,
    #endif
    out float4 oPos : POSITION,
    out float4 oColor : COLOR,
    out float2 oTexCoord : TEXCOORD0)
{
    float4 pos = evaluatePositionBillboard(iPos, iSize, oPos);
    oColor = iColor;
    oTexCoord = evaluateTexCoord(iTexCoord);
    oWorldPos = float4(adjustWorldPos(pos), calculateDepth(oPos));

    #ifdef SPOTLIGHT
        oSpotPos = mul(pos, cSpotProj);
    #endif
}

void ps(float4 iColor : COLOR,
    float2 iTexCoord : TEXCOORD0,
    float4 iWorldPos : TEXCOORD1,
    #ifdef SPOTLIGHT
        float4 iSpotPos : TEXCOORD2,
    #endif
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffColor = cMatDiffColor * iColor * tex2D(sDiffMap, iTexCoord);
    #else
        float4 diffColor = cMatDiffColor * iColor;
    #endif

    #ifdef UNLIT
        oColor = float4(evaluateFog(diffColor.rgb, iWorldPos.w), diffColor.a);
    #endif

    #ifdef ADDITIVE
        oColor = float4(evaluateLitFog(diffColor.rgb, iWorldPos.w), diffColor.a);
    #endif
    
    #ifdef AMBIENT
        float3 finalColor = cAmbientColorPS * diffColor.rgb;
        oColor = float4(evaluateFog(finalColor, iWorldPos.w), diffColor.a);
    #endif
    
    #if (!defined(UNLIT)) && (!defined(ADDITIVE)) && (!defined(AMBIENT))
        float3 lightVec;
        float diff;

        #ifdef DIRLIGHT
            diff = evaluateDiffuseDirVolumetric() * evaluateSplitFade(iWorldPos.w);
        #else
            diff = evaluateDiffusePointOrSpotVolumetric(iWorldPos.xyz, lightVec);
        #endif

        #ifdef SPOTLIGHT
            float3 lightColor = iSpotPos.w > 0.0 ? tex2Dproj(sLightSpotMap, iSpotPos).rgb * cLightColor.rgb : 0.0;
        #else
            float3 lightColor = cLightColor.rgb;
        #endif

        #ifndef NEGATIVE
            float3 finalColor = diff * lightColor * diffColor.rgb;
            oColor = float4(evaluateLitFog(finalColor, iWorldPos.w), diffColor.a);
        #else
            float3 finalColor = 1.0 + diff * diffColor.a * evaluateReverseFogFactor(iWorldPos.w) * lightColor;
            oColor = float4(finalColor, 1.0);
        #endif
    #endif
}
