#include "Uniforms.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION)
{
    GetPosition(iPos, oPos);
}

void PS(
    out float4 oDiff : COLOR0,
    out float4 oDepth : COLOR1)
{
    oDiff = 0.0;
    oDepth = 1.0;
}
