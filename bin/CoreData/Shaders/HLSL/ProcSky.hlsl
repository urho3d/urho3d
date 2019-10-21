#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
		float3 iNormal : NORMAL,
		out float4 oPos : POSITION,
		out float3 oTexCoord : TEXCOORD0)
{
	oPos = iPos;
	oTexCoord = iNormal;
}

void PS(float3 oTexCoord: TEXCOORD0, out float4 oColor : OUTCOLOR0)
{
    float3 V = normalize( oTexCoord ) + float3(0, 0.2 ,0);
    float2 lt = float2( (1.0 + normalize( V.xz ).y) / 2.0, 1.0 - normalize( V ).y );

    #ifndef D3D11
    oColor = float4(tex2D( sDiffMap, lt ).rgb, 1.0);
    #else
    oColor = float4(tDiffMap.Sample(sDiffMap, lt).rgb, 1.0);
    #endif

}
