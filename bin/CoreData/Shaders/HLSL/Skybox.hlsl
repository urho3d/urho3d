#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    out float3 oTexCoord : TEXCOORD0,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);

    oPos.z = oPos.w;
    oTexCoord = iPos.xyz;
}

void PS(float3 iTexCoord : TEXCOORD0,
    out float4 oColor : OUTCOLOR0)
{
    float4 sky = cMatDiffColor * SampleCube(DiffCubeMap, iTexCoord);
    #ifdef HDRSCALE
        sky = lerp(sky, pow(sky + 0.25, 6.0), max(cAmbientColor.a, 0.0));
    #endif
    oColor = sky;
}
