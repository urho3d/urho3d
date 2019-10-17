#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#ifdef COMPILEVS
void VS(float4 iPos : POSITION,
    out float2 oScreenPos : TEXCOORD0,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}
#endif
#ifdef COMPILEPS
void PS(float2 iScreenPos : TEXCOORD0,
    out float4 oColor : OUTCOLOR0)
{
    oColor = Sample2D(DiffMap, iScreenPos);
}
#endif
