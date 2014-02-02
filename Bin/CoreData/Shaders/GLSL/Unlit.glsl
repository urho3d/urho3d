#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Fog.glsl"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
#ifdef HEIGHTFOG
    varying vec3 vWorldPos;
#endif
varying float vDepth;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetTexCoord(iTexCoord);
    vDepth = GetDepth(gl_Position);

    #ifdef HEIGHTFOG
        vWorldPos = worldPos;
    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}

void PS()
{
    #ifdef DIFFMAP
        vec4 diffColor = cMatDiffColor * texture2D(sDiffMap, vTexCoord);
        #ifdef ALPHAMASK
            if (diffColor.a < 0.5)
                discard;
        #endif
    #else
        vec4 diffColor = cMatDiffColor;
    #endif

    #ifdef VERTEXCOLOR
        diffColor *= vColor;
    #endif

    #ifdef HEIGHTFOG
        float fogFactor = GetHeightFogFactor(vDepth, vWorldPos.y);
    #else
        float fogFactor = GetFogFactor(vDepth);
    #endif

    gl_FragColor = vec4(GetFog(diffColor.rgb, fogFactor), diffColor.a);
}
