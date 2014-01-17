#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"

varying vec4 vScreenPos;
varying vec4 vRefractUV;
varying vec2 vReflectUV;

uniform float cDistortStrength;
uniform float cDistortSpeed;
uniform float cReflectionMix;
uniform float cRefractionMix;
uniform vec3 cWaterTint;

void main()
{
    vec2 refractUV = vScreenPos.xy / vScreenPos.w;
    vec2 reflectUV = vReflectUV.xy / vScreenPos.w;
    float t = vRefractUV.x + vRefractUV.z + cElapsedTimePS * cDistortSpeed;
    vec2 distort = vec2(-sin(t), cos(t)) * cDistortStrength;
    refractUV += distort;
    reflectUV += distort;

    vec3 refract = texture2D(sEnvMap, refractUV).rgb;
    vec3 reflect = texture2D(sDiffMap, reflectUV).rgb;

    vec3 final = (cRefractionMix * refract + cReflectionMix * reflect) * cWaterTint;

    gl_FragColor = float4(GetFog(final, vRefractUV.w), 1.0);
}