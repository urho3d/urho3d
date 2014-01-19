#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"

varying vec4 vScreenPos;
varying vec2 vReflectUV;
varying vec2 vWaterUV;
varying vec3 vNormal;
varying vec4 vEyeVec;

uniform float cNoiseStrength;
uniform float cFresnelPower;
uniform vec3 cWaterTint;

void main()
{
    vec2 refractUV = vScreenPos.xy / vScreenPos.w;
    vec2 reflectUV = vReflectUV.xy / vScreenPos.w;

    vec2 noise = (texture2D(sNormalMap, vWaterUV).rg - 0.5) * cNoiseStrength;
    refractUV += noise;
    // Do not shift reflect UV coordinate upward, because it will reveal the clipping of geometry below water
    if (noise.y < 0.0)
        noise.y = 0.0;
    reflectUV += noise;

    float fresnel = pow(1.0 - clamp(dot(normalize(vEyeVec.xyz), vNormal), 0.0, 1.0), cFresnelPower);
    vec3 refractColor = texture2D(sEnvMap, refractUV).rgb * cWaterTint;
    vec3 reflectColor = texture2D(sDiffMap, reflectUV).rgb;
    vec3 finalColor = mix(refractColor, reflectColor, fresnel);

    gl_FragColor = vec4(GetFog(finalColor, vEyeVec.w), 1.0);
}