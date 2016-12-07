#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#ifdef COMPILEVS
void VS(float4 iPos : POSITION, 
    float2 iTexCoord: TEXCOORD0,
    out float2 oTexCoord : TEXCOORD0, 
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    
    oPos.z = oPos.w;
    oTexCoord = iTexCoord;
}
#endif
#ifdef COMPILEPS
void PS(float2 iTexCoord : TEXCOORD0, 
        out float4 oColor : OUTCOLOR0)
{
    oColor = cMatDiffColor * Sample2D(DiffMap, iTexCoord);
}
#endif
