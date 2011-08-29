#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Fog.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oScreenPos : TEXCOORD0)
{
    GetPosition(iPos, oPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iScreenPos : TEXCOORD0,
    out float4 oColor : COLOR0)
{
    float4 diffInput = tex2D(sDiffBuffer, iScreenPos);
    #ifdef LINEAR
        float depth = tex2D(sDepthBuffer, iScreenPos).r;
    #else
        float depth = ReconstructDepth(tex2D(sDepthBuffer, iScreenPos).r);
    #endif
    float3 ambientColor = cAmbientColor * diffInput.rgb;

    oColor = float4(ambientColor + GetFogFactor(depth) * cFogColor, 1.0);
}
