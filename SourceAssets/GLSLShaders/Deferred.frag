#include "Uniforms.frag"
#include "Samplers.frag"
#include "Fog.frag"

varying vec2 vTexCoord;
varying vec4 vVertexLighting;
varying vec3 vNormal;
#ifdef NORMALMAP
    varying vec3 vTangent;
    varying vec3 vBitangent;
#endif

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

    #ifdef VERTEXCOLOR
        diffColor *= vColor.rgb;
    #endif

    #ifdef NORMALMAP
        mat3 tbn = mat3(vTangent, vBitangent, vNormal);
        vec3 normal = tbn * DecodeNormal(texture2D(sNormalMap, vTexCoord));
    #else
        vec3 normal = vNormal;
    #endif

    #ifdef SPECMAP
        float specIntensity = cMatSpecColor.g * texture2D(sSpecMap, vTexCoord).g;
    #else
        float specIntensity = cMatSpecColor.g;
    #endif

    float specPower = cMatSpecColor.a / 255.0;

    gl_FragData[0] = vec4(GetFog(vVertexLighting.rgb * diffColor, vVertexLighting.a), 1.0);
    gl_FragData[1] = GetFogFactor(vVertexLighting.a) * vec4(diffColor, specIntensity);
    gl_FragData[2] = vec4(normal * 0.5 + 0.5, specPower);
    #ifndef HWDEPTH
        gl_FragData[3] = vec4(EncodeDepth(vVertexLighting.a), 0.0);
    #endif
}
