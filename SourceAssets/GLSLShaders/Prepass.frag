#include "Uniforms.frag"
#include "Samplers.frag"

#ifdef HWDEPTH
    varying vec2 vTexCoord;
#else
    varying vec3 vTexCoord;
#endif
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
        vec3 normal = tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord.xy));
    #else
        vec3 normal = vNormal;
    #endif

    float specPower = cMatSpecColor.a / 255.0;

    #ifdef HWDEPTH
        gl_FragColor = vec4(normal * 0.5 + 0.5, specPower);
    #else
        gl_FragData[0] = vec4(normal * 0.5 + 0.5, specPower);
        gl_FragData[1] = vec4(EncodeDepth(vTexCoord.z), 0.0);
    #endif
}
