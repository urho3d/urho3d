#include "Uniforms.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION)
{
    GetPosition(iPos, oPos);
}

void PS(out float4 oColor : COLOR0)
{
    oColor = 1.0;
}
