#include "Uniforms.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION)
{
    GetPosition(iPos, oPos);
}

void PS(
    #ifdef DEPTH
        out float4 oDepth : COLOR1,
    #endif
    out float4 oDiff : COLOR0)
{
    oDiff = 0.0;
    #ifdef DEPTH
    oDepth = 1.0;
    #endif
}
