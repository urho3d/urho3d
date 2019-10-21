#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
		float2 iTexCoord : TEXCOORD0,
		float4 iColor : COLOR0,
		out float4 oColor : COLOR0,
		out float4 oPos : OUTPOSITION
		)
{

	float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oColor = iColor * iTexCoord.x;
}

void PS(float4 iColor : COLOR0, out float4 oColor : OUTCOLOR0)
{
	oColor = iColor;
}
