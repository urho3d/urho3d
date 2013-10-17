#include "Uniforms.frag"
#include "Samplers.frag"
#include "PostProcess.frag"

uniform float cAutoExposureAdaptRate;
uniform float cAutoExposureMiddleGrey;
uniform float cAutoExposureSensitivity;
uniform vec2 cHDR128InvSize;
uniform vec2 cLum64InvSize;
uniform vec2 cLum16InvSize;
uniform vec2 cLum4InvSize;

varying vec2 vTexCoord;
varying vec2 vScreenPos;

float GatherAvgLum(sampler2D texSampler, vec2 texCoord, vec2 texelSize)
{
    float lumAvg = 0.0;
    lumAvg += texture2D(texSampler, texCoord + vec2(1.0, -1.0) * texelSize).r;
    lumAvg += texture2D(texSampler, texCoord + vec2(-1.0, 1.0) * texelSize).r;
    lumAvg += texture2D(texSampler, texCoord + vec2(1.0, 1.0) * texelSize).r;
    lumAvg += texture2D(texSampler, texCoord + vec2(1.0, -1.0) * texelSize).r;
    return lumAvg / 4.0;
}

void main()
{
    #ifdef LUMINANCE64
    float logLumSum = 1e-5;
    logLumSum += log(dot(texture2D(sDiffMap, vTexCoord + vec2(-1.0, -1.0) * cHDR128InvSize).rgb, LumWeights));
    logLumSum += log(dot(texture2D(sDiffMap, vTexCoord + vec2(-1.0, 1.0) * cHDR128InvSize).rgb, LumWeights));
    logLumSum += log(dot(texture2D(sDiffMap, vTexCoord + vec2(1.0, 1.0) * cHDR128InvSize).rgb, LumWeights));
    logLumSum += log(dot(texture2D(sDiffMap, vTexCoord + vec2(1.0, -1.0) * cHDR128InvSize).rgb, LumWeights));
    gl_FragColor.r = logLumSum;
    #endif

    #ifdef LUMINANCE16
    gl_FragColor.r = exp(GatherAvgLum(sDiffMap, vTexCoord, cLum64InvSize) / 16.0);
    #endif

    #ifdef LUMINANCE4
    gl_FragColor.r = GatherAvgLum(sDiffMap, vTexCoord, cLum16InvSize);
    #endif

    #ifdef LUMINANCE1
    gl_FragColor.r = GatherAvgLum(sDiffMap, vTexCoord, cLum4InvSize);
    #endif

    #ifdef ADAPTLUMINANCE
    float adaptedLum = texture2D(sDiffMap, vTexCoord).r;
    float lum = texture2D(sNormalMap, vTexCoord).r;
    gl_FragColor.r = adaptedLum + (lum - adaptedLum) * (1.0 - exp(-cDeltaTimePS * cAutoExposureAdaptRate));
    #endif

    #ifdef EXPOSE
    vec3 color = texture2D(sDiffMap, vScreenPos).rgb;
    float adaptedLum = max(mix(cAutoExposureMiddleGrey, texture2D(sNormalMap, vTexCoord).r, cAutoExposureSensitivity), 1e-5);
    gl_FragColor = vec4(color * (cAutoExposureMiddleGrey / adaptedLum), 1.0);
    #endif
}
