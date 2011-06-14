#include "Uniforms.hlsl"
#include "Samplers.hlsl"
#include "Transform.hlsl"
#include "ScreenPos.hlsl"

void VS(float4 iPos : POSITION,
    out float4 oPos : POSITION,
    out float2 oScreenPos : TEXCOORD0)
{
    GetPosition(iPos, oPos);
    oScreenPos = GetScreenPosPreDiv(oPos);
}

void PS(float2 iScreenPos : TEXCOORD0,
    out float4 oColor : COLOR0)
{
    // Shader based on the blog post http://www.gamestart3d.com/blog/ssaa-antialiasing
    float2 offsets = cEdgeFilterParams.x * cSampleOffsets.xy;

    float4 color = tex2D(sDiffBuffer, iScreenPos);
    
    // Get intensity at center, clamp to 10% minimum to not cause oversensitivity in dark areas
    float base = max(GetIntensity(color.rgb), 0.1);
    
    // Get intensities at neighbour pixels
    float up = GetIntensity(tex2D(sDiffBuffer, iScreenPos + float2(0, -offsets.y)).rgb);
    float down = GetIntensity(tex2D(sDiffBuffer, iScreenPos + float2(0, offsets.y)).rgb);
    float left = GetIntensity(tex2D(sDiffBuffer, iScreenPos + float2(-offsets.x, 0)).rgb);
    float right = GetIntensity(tex2D(sDiffBuffer, iScreenPos + float2(offsets.x, 0)).rgb);
    
    // Calculate normal, scale with base intensity
    float2 normal = float2((up - base) + (base - down), (right - base) + (base - left)) / base;
    float len = length(normal);
    
    // Clamp normal to maximum
    if (len > 1)
        normal /= len;
    
    // Blur if over threshold (compare to center pixel intensity)
    if (len > cEdgeFilterParams.y)
    {
        normal *= cSampleOffsets.xy * cEdgeFilterParams.z;
        oColor = (color +
            Sample(sDiffBuffer, iScreenPos + normal) +
            Sample(sDiffBuffer, iScreenPos - normal)) * (1.0 / 3.0);
    }
    else
        oColor = color;
}
