#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION, 
    float2 iTexCoord: TEXCOORD0,
    out float2 oTexCoord : TEXCOORD0, 
    out float4 oPos : OUTPOSITION)
{
    oPos = float4(iPos.x*2.0, iPos.z*2.0, 1.0, 1.0);
    oTexCoord = iTexCoord;
}

void PS(float2 iTexCoord : TEXCOORD0, 
        out float4 oColor : OUTCOLOR0)
{
    oColor = cMatDiffColor * Sample2D(DiffMap, iTexCoord);
}
