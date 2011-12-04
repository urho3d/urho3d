#include "Uniforms.frag"
#include "Samplers.frag"

varying vec3 vTexCoord;
varying vec3 vNormal;
#ifdef NORMALMAP
    varying vec3 vTangent;
    varying vec3 vBitangent;
#endif

void main()
{
    #ifdef ALPHAMASK
        vec4 diffInput = texture2D(sDiffMap, vTexCoord.xy);
        if (diffInput.a < 0.5)
            discard;
    #endif

    #ifdef NORMALMAP
        mat3 tbn = mat3(vTangent, vBitangent, vNormal);
        vec3 normal = normalize(tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord.xy)));
    #else
        vec3 normal = normalize(vNormal);
    #endif

    #ifdef SPECMAP
        float specStrength = texture2D(sSpecMap, vTexCoord.xy).g * cMatSpecProperties.x;
    #else
        float specStrength = cMatSpecProperties.x;
    #endif
    float specPower = cMatSpecProperties.y / 255.0;

    gl_FragData[0] = vec4(normal * 0.5 + 0.5, specPower);
    gl_FragData[1] = vec4(vTexCoord.z);
}
