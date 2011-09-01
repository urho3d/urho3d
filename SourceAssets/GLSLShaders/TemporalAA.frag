#include "Uniforms.frag"
#include "Samplers.frag"

varying vec2 vScreenPos;
varying vec3 vFarRay;
#ifdef ORTHO
varying vec3 vNearRay;
#endif

void main()
{
    vec2 hOffset = vec2(cSampleOffsets.x, 0);
    vec2 vOffset = vec2(0, cSampleOffsets.y);
    vec3 current = texture2D(sDiffBuffer, vScreenPos).rgb;

    // Reconstruct position for this frame's pixel
    #ifdef ORTHO
        float depth = texture2D(sDepthBuffer, vScreenPos).r;
        vec3 worldPos = mix(vNearRay, vFarRay, depth) + cCameraPosPS;
    #else
        #ifdef LINEAR
            float depth = texture2D(sDepthBuffer, vScreenPos).r;
        #else
            float depth = ReconstructDepth(texture2D(sDepthBuffer, vScreenPos).r);
        #endif
        vec3 worldPos = vFarRay * depth + cCameraPosPS;
    #endif

    // Calculate G-buffer position for pixel on last frame
    vec4 clipPosLast = cViewProjPS * vec4(worldPos, 1.0);

    #ifdef ORTHO
        vec2 screenPosLast = vec2(
            clipPosLast.x * cGBufferOffsetsPS.z + cGBufferOffsetsPS.x,
            clipPosLast.y * cGBufferOffsetsPS.w + cGBufferOffsetsPS.y);
    #else
       vec2 screenPosLast = vec2(
            clipPosLast.x / clipPosLast.w * cGBufferOffsetsPS.z + cGBufferOffsetsPS.x,
            clipPosLast.y / clipPosLast.w * cGBufferOffsetsPS.w + cGBufferOffsetsPS.y);
    #endif

    vec3 last = texture2D(sNormalBuffer, screenPosLast).rgb;
    vec3 color = cSampleOffsets.z * current + cSampleOffsets.w * last;

    // To eliminate ghosting, clamp RGB values to the pixel's neighbours
    // This is rather expensive, so only do it if there is a large color difference
    if (dot(abs(current - last), 1.0) > 0.25)
    /{
        vec3 left = texture2D(sDiffBuffer, vScreenPos - hOffset).rgb;
        vec3 right = texture2D(sDiffBuffer, vScreenPos + hOffset).rgb;
        vec3 up = texture2D(sDiffBuffer, vScreenPos - vOffset).rgb;
        vec3 down = texture2D(sDiffBuffer, vScreenPos + vOffset).rgb;
        vec3 minColor = min(min(left, right), min(up, down));
        vec3 maxColor = max(max(left, right), max(up, down));
        gl_FragColor = vec4(clamp(color, minColor, maxColor), 1.0);
    }
    else
        gl_FragColor = vec4(color, 1.0);
}
