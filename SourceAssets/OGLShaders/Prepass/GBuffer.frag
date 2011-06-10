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
    #ifdef ALPHAMASK
        if (texture2D(sDiffMap, iTexCoord).a < 0.5)
            discard;
    #endif

    #ifdef NORMALMAP
        mat3 tbn = mat3(vTangent, vBitangent, vNormal);
        vec3 normal = normalize(tbn * UnpackNormal(texture2D(sNormalMap, vTexCoord)));
    #else
        vec3 normal = normalize(vNormal);
    #endif

    float specPower = cMatSpecProperties.y / 255.0;

    gl_FragColor = vec4(normal * 0.5 + 0.5, specPower);
}
