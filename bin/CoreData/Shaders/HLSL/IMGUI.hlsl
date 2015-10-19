#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"

void VS(float4 iPos : POSITION,
#ifdef DIFFMAP
	float2 iTexCoord : TEXCOORD0,
#endif
#ifdef VERTEXCOLOR
	float4 iColor : COLOR0,
	out float4 oColor : COLOR0,
#endif
#ifdef DIFFMAP
	out float2 oTexCoord : TEXCOORD0,
#endif
    out float4 oPos : OUTPOSITION)
{

    oPos = GetClipPos(float3(iPos.xy, 0.0));


#ifdef VERTEXCOLOR
	oColor = iColor;
#endif
#ifdef DIFFMAP
	oTexCoord = iTexCoord;
#endif
}

void PS(
#ifdef VERTEXCOLOR
	float4 iColor : COLOR0,
#endif
#if defined(DIFFMAP) || defined(ALPHAMAP)
	float2 iTexCoord : TEXCOORD0,
#endif
        out float4 oColor : OUTCOLOR0)
{

	float4 diffColor = cMatDiffColor;
#ifdef VERTEXCOLOR
	diffColor *= iColor;
#endif

#if (!defined(DIFFMAP)) && (!defined(ALPHAMAP))
	oColor = diffColor;
#endif

#ifdef DIFFMAP
	float4 diffInput = Sample2D(DiffMap, iTexCoord);
	#ifdef ALPHAMASK
		if (diffInput.a < 0.5)
			discard;
	#endif
	oColor = diffColor * diffInput;
#endif

#ifdef ALPHAMAP
	float alphaInput = Sample2D(DiffMap, iTexCoord).a;
	oColor = float4(diffColor.rgb, diffColor.a * alphaInput);
#endif


	
}
