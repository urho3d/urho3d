#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

varying vec3 EyeV;

void VS() 
{
    EyeV = iNormal;
    gl_Position = iPos;
}

void PS()
{
    vec3 V = normalize( EyeV ) + vec3(0,.2,0);
    vec2 lt = vec2( (1.0 + normalize( V.xz ).y) / 2.0, 1.0 - normalize( V ).y );
    gl_FragColor = texture2D( sDiffMap, lt );

}

