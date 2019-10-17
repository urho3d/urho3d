#include "Uniforms.hlsl"
#include "Transform.hlsl"
#include "Samplers.hlsl"
#include "ScreenPos.hlsl"
#include "PostProcess.hlsl"

uniform float2 cBlurDir;
uniform float cBlurRadius;
uniform float cBlurSigma;
uniform float2 cBlurHOffsets;
uniform float2 cBlurHInvSize;

void VS(float4 iPos : POSITION,
    out float2 oTexCoord : TEXCOORD0,
    out float2 oScreenPos : TEXCOORD1,
    out float4 oPos : OUTPOSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oTexCoord = GetQuadTexCoord(oPos) + cBlurHOffsets;
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iTexCoord : TEXCOORD0,
    float2 iScreenPos : TEXCOORD1,
    out float4 oColor : OUTCOLOR0)
{
    #ifdef BLUR3
        #ifndef D3D11 
            oColor = GaussianBlur(3, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, iTexCoord);
        #else
            oColor = GaussianBlur(3, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, tDiffMap, sDiffMap, iTexCoord);
        #endif
    #endif

    #ifdef BLUR5
        #ifndef D3D11
            oColor = GaussianBlur(5, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, iTexCoord);
        #else
            oColor = GaussianBlur(5, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, tDiffMap, sDiffMap, iTexCoord);
        #endif
    #endif

    #ifdef BLUR7
        #ifndef D3D11
            oColor = GaussianBlur(7, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, iTexCoord);
        #else
            oColor = GaussianBlur(7, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, tDiffMap, sDiffMap, iTexCoord);
        #endif
    #endif

    #ifdef BLUR9
        #ifndef D3D11
            oColor = GaussianBlur(9, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, sDiffMap, iTexCoord);
        #else
            oColor = GaussianBlur(9, cBlurDir, cBlurHInvSize * cBlurRadius, cBlurSigma, tDiffMap, sDiffMap, iTexCoord);
        #endif
    #endif
}
