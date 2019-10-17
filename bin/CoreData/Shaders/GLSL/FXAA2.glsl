/*============================================================================

                  FXAA v2 CONSOLE by TIMOTHY LOTTES @ NVIDIA

============================================================================*/

// Adapted for Urho3D from http://timothylottes.blogspot.com/2011/04/nvidia-fxaa-ii-for-console.html

#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"

varying vec2 vScreenPos;

#ifdef COMPILEPS
uniform vec3 cFXAAParams;
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}

void PS()
{
    float FXAA_SUBPIX_SHIFT = 1.0/4.0; // Not used
    float FXAA_SPAN_MAX = 8.0;
    float FXAA_REDUCE_MUL = 1.0/8.0;
    float FXAA_REDUCE_MIN = 1.0/128.0;

    vec2 posOffset = cGBufferInvSize.xy * cFXAAParams.x;

    vec3 rgbNW = texture2D(sDiffMap, vScreenPos + vec2(-posOffset.x, -posOffset.y)).rgb;
    vec3 rgbNE = texture2D(sDiffMap, vScreenPos + vec2(posOffset.x, -posOffset.y)).rgb;
    vec3 rgbSW = texture2D(sDiffMap, vScreenPos + vec2(-posOffset.x, posOffset.y)).rgb;
    vec3 rgbSE = texture2D(sDiffMap, vScreenPos + vec2(posOffset.x, posOffset.y)).rgb;
    vec3 rgbM  = texture2D(sDiffMap, vScreenPos).rgb;

    vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    if (((lumaMax - lumaMin) / lumaMin) >= cFXAAParams.y)
    {
        vec2 dir;
        dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
        dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));

        float dirReduce = max(
            (lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL),
            FXAA_REDUCE_MIN);
        float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
        dir = min(vec2( FXAA_SPAN_MAX,  FXAA_SPAN_MAX),
              max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
              dir * rcpDirMin)) * cGBufferInvSize.xy;

        dir *= cFXAAParams.z;

        vec3 rgbA = (1.0/2.0) * (
            texture2D(sDiffMap, vScreenPos + dir * (1.0/3.0 - 0.5)).xyz +
            texture2D(sDiffMap, vScreenPos + dir * (2.0/3.0 - 0.5)).xyz);
        vec3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (
            texture2D(sDiffMap, vScreenPos + dir * (0.0/3.0 - 0.5)).xyz +
            texture2D(sDiffMap, vScreenPos + dir * (3.0/3.0 - 0.5)).xyz);
        float lumaB = dot(rgbB, luma);

        vec3 rgbOut;
        if((lumaB < lumaMin) || (lumaB > lumaMax))
            rgbOut = rgbA;
        else
            rgbOut = rgbB;
    
        gl_FragColor = vec4(rgbOut, 1.0);
    }
    else
        gl_FragColor = vec4(rgbM, 1.0);
}

