#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"
#include "Fog.hlsl"

uniform float cDistortStrength;
uniform float cDistortSpeed;
uniform float cReflectionMix;
uniform float cRefractionMix;
uniform float3 cWaterTint;

void VS(float4 iPos : POSITION,
    out float4 oScreenPos : TEXCOORD0,
    out float4 oRefractUV : TEXCOORD1,
    out float2 oReflectUV : TEXCOORD2,
    out float4 oPos : POSITION)
{
    float4x3 modelMatrix = iModelMatrix;
    float3 worldPos = GetWorldPos(modelMatrix);
    oPos = GetClipPos(worldPos);
    oScreenPos = GetScreenPos(oPos);
    oRefractUV = float4(worldPos, GetDepth(oPos));
    // GetQuadTexCoord() returns a float2 that is OK for quad rendering; multiply it with output W
    // coordinate to make it work with arbitrary meshes such as the water plane (perform divide in pixel shader)
    oReflectUV = GetQuadTexCoord(oPos) * oPos.w;
}

void PS(
    float4 iScreenPos : TEXCOORD0,
    float4 iRefractUV : TEXCOORD1,
    float2 iReflectUV : TEXCOORD2,
    out float4 oColor : COLOR0)
{
    float2 refractUV = iScreenPos.xy / iScreenPos.w;
    float2 reflectUV = iReflectUV.xy / iScreenPos.w;
    float t = iRefractUV.x + iRefractUV.z + cElapsedTimePS * cDistortSpeed;
    float2 distort = float2(-sin(t), cos(t)) * cDistortStrength;
    refractUV += distort;
    reflectUV += distort;

    float3 refract = tex2D(sEnvMap, refractUV).rgb;
    float3 reflect = tex2D(sDiffMap, reflectUV).rgb;

    float3 final = (cRefractionMix * refract + cReflectionMix * reflect) * cWaterTint;

    oColor = float4(GetFog(final, iRefractUV.w), 1.0);
}