#include "../Common.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef SKINNED
        float4 iBlendWeights : BLENDWEIGHT,
        int4 iBlendIndices : BLENDINDICES,
    #endif
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD2,
    #endif
    float2 iTexCoord : TEXCOORD0,
    out float2 oTexCoord : TEXCOORD0,
    out float4 oWorldPos : TEXCOORD1,
    out float4 oScreenPos : TEXCOORD2,
    out float4 oPos : POSITION)
{
    float4 pos;
    #if (!defined(SKINNED)) && (!defined(INSTANCED))
        pos = GetPosition(iPos, oPos);
    #endif
    #ifdef SKINNED
        pos = GetPositionSkinned(iPos, iBlendWeights, iBlendIndices, oPos);
    #endif
    #ifdef INSTANCED
        pos = GetPositionInstanced(iPos, iModelInstance, oPos);
    #endif

    // Store world-oriented view position in case it is needed
    oWorldPos = float4(pos.xyz - cCameraPos, GetDepth(oPos));
    oScreenPos = GetScreenPos(oPos);
    oTexCoord = GetTexCoord(iTexCoord);
}

void PS(float2 iTexCoord : TEXCOORD0,
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

    #ifdef SPECMAP
        float specStrength = cMatSpecProperties.x * tex2D(sSpecMap, iTexCoord).g;
    #else
        float specStrength = cMatSpecProperties.x;
    #endif

    // Lights are accumulated at half intensity. Bring back to full intensity now
    float4 lightInput = 2.0 * tex2Dproj(sLightBuffer, iScreenPos);
    float3 lightDiffColor = cAmbientColor + lightInput.rgb;
    // Divide light color by intensity to reconstruct the specular color
    float3 lightSpecColor = lightInput.a * (lightInput.rgb / GetIntensity(lightInput.rgb));

    float3 finalColor = lightDiffColor * diffColor + lightSpecColor * specStrength;

    // Store coarse depth to alpha channel for deferred antialiasing
    oColor = float4(GetFog(finalColor, iWorldPos.w), iWorldPos.w);
}
