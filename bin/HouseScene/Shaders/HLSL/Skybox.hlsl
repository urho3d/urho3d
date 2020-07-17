#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
    #ifdef INSTANCED
        float4x3 iModelInstance : TEXCOORD4,
    #endif
    out float3 oTexCoord : TEXCOORD0,
    out float4 oPos : OUTPOSITION)
{
#ifdef IGNORENODETRANSFORM
    float4x3 modelMatrix = { float3(1.0, 0.0, 0.0), float3(0.0, 1.0, 0.0), float3(0.0, 0.0, 1.0), cViewInv[3] };
#else
    float4x3 modelMatrix = iModelMatrix;
#endif
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
        sky = pow(sky + clamp((cAmbientColor.a - 1.0) * 0.1, 0.0, 0.25), max(cAmbientColor.a, 1.0)) * clamp(cAmbientColor.a, 0.0, 1.0);
    #endif
    oColor = sky;
}
