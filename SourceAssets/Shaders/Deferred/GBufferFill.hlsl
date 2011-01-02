#include "../Common.hlsl"

void vs(float4 iPos : POSITION,
    out float4 oPos : POSITION)
{
    evaluatePosition(iPos, oPos);
}

void ps(    
    #ifndef HWDEPTH
        out float4 oDepth : COLOR1,
    #endif
    out float4 oDiff : COLOR0)
{
    oDiff = 0.0;
    #ifndef HWDEPTH
        oDepth = 1.0;
    #endif
}
