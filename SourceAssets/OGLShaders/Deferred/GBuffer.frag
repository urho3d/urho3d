#include "../Uniforms.frag"
#include "../Samplers.frag"
#include "../Fog.frag"

varying vec2 vTexCoord;
varying float vDepth;
varying vec3 vNormal;
#ifdef NORMALMAP
varying vec3 vTangent;
varying vec3 vBitangent;
#endif

void main()
{
    #ifdef DIFFMAP
        vec4 diffInput = texture2D(sDiffMap, vTexCoord);
        vec3 diffColor = cMatDiffColor.rgb * diffInput.rgb;
        #ifdef ALPHAMASK
            if (diffInput.a < 0.5)
                discard;
        #endif
    #else
        vec3 diffColor = cMatDiffColor.rgb;
    #endif

    #ifdef NORMALMAP
        mat3 tbn = mat3(vTangent, vBitangent, vNormal);
        vec3 normal = normalize(tbn * UnpackNormal(texture2D(sNormalMap, vTexCoord)));
    #else
        vec3 normal = normalize(vNormal);
    #endif

    #ifdef SPECMAP
        float specStrength = texture2D(sSpecMap, vTexCoord).r * cMatSpecProperties.x;
    #else
        float specStrength = cMatSpecProperties.x;
    #endif
    float specPower = cMatSpecProperties.y / 255.0;

    // Take fogging into account here so that deferred lights do not need to calculate it
    gl_FragData[0] = GetReverseFogFactor(vDepth) * vec4(diffColor, specStrength);
    gl_FragData[1] = vec4(normal * 0.5 + 0.5, specPower);
}
