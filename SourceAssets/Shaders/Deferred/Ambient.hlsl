#include "../Common.hlsl"

void vs(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oScreenPos : TEXCOORD0)
{
    evaluatePosition(iPos, oPos);
    oScreenPos = calculateScreenPosPreDiv(oPos);
}

void ps(float2 iScreenPos : TEXCOORD0,
    out float4 oColor : COLOR0)
{
    float4 diffInput = tex2D(sDiffBuffer, iScreenPos);
    #ifdef LINEAR
        float depth = tex2D(sDepthBuffer, iScreenPos).r;
    #else
        float depth = reconstructDepth(tex2D(sDepthBuffer, iScreenPos).r);
    #endif

    float3 ambientColor = cAmbientColorPS * diffInput.rgb;
    oColor = float4(ambientColor + evaluateFogFactor(depth) * cFogColor, 1.0);
}
