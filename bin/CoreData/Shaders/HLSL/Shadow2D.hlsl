
#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"

#ifdef COMPILEPS
uniform float4 cShadowAmbient;
#endif

void VS(float4 iPos : POSITION,
       out float2 oScreenPos : TEXCOORD0,
       out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iScreenPos : TEXCOORD0, out float4 oColor : OUTCOLOR0)
{

    float4 diffInput = Sample2D(DiffMap, iScreenPos);
    float4 lightInput = Sample2D(EmissiveMap, iScreenPos);

	  oColor.rgb = (diffInput.rgb * (lightInput.rgb + cShadowAmbient.rgb) * (lightInput.a + cShadowAmbient.a));
    oColor.a = 1.0;
}
