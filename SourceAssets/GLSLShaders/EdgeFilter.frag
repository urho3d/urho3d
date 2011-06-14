#include "Uniforms.frag"
#include "Samplers.frag"

varying vec2 vScreenPos;

void main()
{
    // Shader based on the blog post http://www.gamestart3d.com/blog/ssaa-antialiasing
    vec2 offsets = cEdgeFilterParams.x * cSampleOffsets.xy;

    vec4 color = texture2D(sDiffBuffer, vScreenPos);
    
    // Get intensity at center, clamp to 10% minimum to not cause oversensitivity in dark areas
    float base = max(GetIntensity(color.rgb), 0.1);
    
    // Get intensities at neighbour pixels
    float up = GetIntensity(texture2D(sDiffBuffer, vScreenPos + vec2(0, -offsets.y)).rgb);
    float down = GetIntensity(texture2D(sDiffBuffer, vScreenPos + vec2(0, offsets.y)).rgb);
    float left = GetIntensity(texture2D(sDiffBuffer, vScreenPos + vec2(-offsets.x, 0)).rgb);
    float right = GetIntensity(texture2D(sDiffBuffer, vScreenPos + vec2(offsets.x, 0)).rgb);
    
    // Calculate normal, scale with base intensity
    vec2 normal = vec2((up - base) + (base - down), (right - base) + (base - left)) / base;
    float len = length(normal);
    
    // Clamp normal to maximum
    if (len > 1)
        normal /= len;

    // Blur if over threshold (compare to center pixel intensity)
    if (len > cEdgeFilterParams.y)
    {
        normal *= cSampleOffsets.xy * cEdgeFilterParams.z;

        gl_FragColor = (color +
            texture2D(sDiffBuffer, vScreenPos + normal) +
            texture2D(sDiffBuffer, vScreenPos - normal)) * (1.0 / 3.0);
    }
    else
        gl_FragColor = color;
}
