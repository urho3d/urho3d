#include "Common.hlsl"

void vs(float4 iPos : POSITION,
    out float4 oPos : POSITION)
{
    evaluatePosition(iPos, oPos);
}

void ps(out float4 oColor : COLOR0)
{
    oColor = 1.0;
}
