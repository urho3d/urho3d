#include "../Uniforms.frag"
#include "../Samplers.frag"
#include "../Fog.frag"

varying vec2 vTexCoord;
varying vec4 vWorldPos;
varying vec4 vScreenPos;

void main()
{
    #ifdef DIFFMAP
        vec4 diffInput = texture2D(sDiffMap, vTexCoord);
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
        vec3 diffColor = cMatDiffColor.rgb * diffInput.rgb;
    #else
        vec3 diffColor = cMatDiffColor.rgb;
    #endif

    #ifdef SPECMAP
        float specStrength = cMatSpecProperties.x * tex2D(sSpecMap, vTexCoord).g;
    #else
        float specStrength = cMatSpecProperties.x;
    #endif

    // Lights are accumulated at half intensity. Bring back to full intensity now
    vec4 lightInput = 2.0 * texture2DProj(sLightBuffer, vScreenPos);
    vec3 lightDiffColor = cAmbientColor + lightInput.rgb;
    // Divide light color by intensity to reconstruct the specular color
    float intensity = GetIntensity(lightInput.rgb);
    vec3 lightSpecColor;
    if (intensity > 0.0)
        lightSpecColor = lightInput.a * (lightInput.rgb / GetIntensity(lightInput.rgb));
    else
        lightSpecColor = vec3(0.0, 0.0, 0.0);

    vec3 finalColor = lightDiffColor * diffColor + lightSpecColor * specStrength;

    // Store coarse depth to alpha channel for deferred antialiasing
    gl_FragColor = vec4(GetFog(finalColor, vWorldPos.w), vWorldPos.w);
}
