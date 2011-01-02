#include "../Common.hlsl"

void vs(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        #ifndef SM3
            int iInstanceNumber : TEXCOORD2,
        #else
            float4x3 iModelInstance : TEXCOORD2,
        #endif
    #endif
    float2 iTexCoord : TEXCOORD0,
    out float2 oTexCoord : TEXCOORD0,
    out float4 oWorldPos : TEXCOORD1,
    out float4 oScreenPos : TEXCOORD2,
    out float4 oPos : POSITION)
{
    float4 pos;
    #ifndef SKINNED
        #ifndef INSTANCED
            pos = evaluatePosition(iPos, oPos);
        #else
            #ifndef SM3
                pos = evaluatePositionInstanced(iPos, cModelInstances[iInstanceNumber], oPos);
            #else
                pos = evaluatePositionInstanced(iPos, iModelInstance, oPos);
            #endif
        #endif
    #else
        pos = evaluatePositionSkinned(iPos, iBlendWeights, iBlendIndices, oPos);
    #endif

    // Store world-oriented view position in case it is needed
    oWorldPos = float4(adjustWorldPos(pos), calculateDepth(oPos));
    oScreenPos = calculateScreenPos(oPos);
    oTexCoord = evaluateTexCoord(iTexCoord);
}

void ps(float2 iTexCoord : TEXCOORD0,
    float4 iWorldPos : TEXCOORD1,
    float4 iScreenPos : TEXCOORD2,
    out float4 oColor : COLOR0)
{
    #ifdef DIFFMAP
        float4 diffInput = tex2D(sDiffMap, iTexCoord);
        float3 diffColor = cMatDiffColor.rgb * diffInput.rgb;
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
    #else
        float3 diffColor = cMatDiffColor.rgb;
    #endif

    // Use monochromatic specular intensity to match deferred rendering. However, a material specular color could be used instead
    #ifdef SPECMAP
        float specIntensity = cMatSpecProperties.x * tex2D(sSpecMap, iTexCoord).r;
    #else
        float specIntensity = cMatSpecProperties.x;
    #endif
    
    // Lights are accumulated at half intensity. Bring back to full intensity now
    float4 lightInput = 2.0 * tex2Dproj(sLightBuffer, iScreenPos);
    // Subtract ambient level from the specular multiplier
    float3 lightSpecColor = lightInput.a * saturate(lightInput.rgb - cAmbientColorPS);
    
    float3 finalColor = lightInput.rgb * diffColor + lightSpecColor * specIntensity;
    oColor = float4(evaluateFog(finalColor, iWorldPos.w), 1.0);
}
