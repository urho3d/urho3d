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
    #if defined(LINEAR)
        float depth = tex2D(sDepthBuffer, iScreenPos).r;
    #elif defined(FALLBACK)
        float4 normalInput = tex2D(sNormalBuffer, iScreenPos);
        float depth = DecodeDepth(float2(diffInput.w, normalInput.w));
    #else
        float depth = ReconstructDepth(tex2D(sDepthBuffer, iScreenPos).r);
    #endif
    float3 ambientColor = cAmbientColor * diffInput.rgb;

    oColor = float4(ambientColor + GetFogFactor(depth) * cFogColor, 1.0);
}
