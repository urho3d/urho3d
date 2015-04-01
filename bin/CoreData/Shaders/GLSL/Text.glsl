#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

varying vec2 vTexCoord;
varying vec4 vColor;

#ifdef TEXT_EFFECT_SHADOW
uniform vec2 cShadowOffset;
uniform vec4 cShadowColor;
#endif

#ifdef TEXT_EFFECT_STROKE
uniform vec4 cStrokeColor;
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    
    vTexCoord = iTexCoord;
    vColor = iColor;
}

void PS()
{
    gl_FragColor.rgb = vColor.rgb;

#ifdef SIGNED_DISTANCE_FIELD
    float distance = texture2D(sDiffMap, vTexCoord).a;
    if (distance < 0.5)
    {
    #ifdef TEXT_EFFECT_SHADOW
        if (texture2D(sDiffMap, vTexCoord - cShadowOffset).a > 0.5)
            gl_FragColor = cShadowColor;
        else
    #endif
        gl_FragColor.a = 0.0;
    }
    else
    {
    #ifdef TEXT_EFFECT_STROKE
        if (distance < 0.525)
            gl_FragColor.rgb = cStrokeColor.rgb;
    #endif

    #ifdef TEXT_EFFECT_SHADOW
        if (texture2D(sDiffMap, vTexCoord + cShadowOffset).a < 0.5)
            gl_FragColor.a = vColor.a;
        else
    #endif
        gl_FragColor.a = vColor.a * smoothstep(0.5, 0.505, distance);
    }
#else
    // Non-SDF font will likely be monochrome, in which case the alpha channel will be on the R channel on OpenGL 3
    #ifdef GL3
        gl_FragColor.a = vColor.a * texture2D(sDiffMap, vTexCoord).r;
    #else
        gl_FragColor.a = vColor.a * texture2D(sDiffMap, vTexCoord).a;
    #endif
#endif
}
