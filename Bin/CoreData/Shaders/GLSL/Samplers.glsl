#ifdef COMPILEPS
uniform sampler2D sDiffMap;
uniform samplerCube sDiffCubeMap;
uniform sampler2D sNormalMap;
uniform sampler2D sSpecMap;
uniform sampler2D sEmissiveMap;
uniform sampler2D sEnvMap;
uniform samplerCube sEnvCubeMap;
uniform sampler2D sLightRampMap;
uniform sampler2D sLightSpotMap;
uniform samplerCube sLightCubeMap;
#ifndef GL_ES
    uniform sampler3D sVolumeMap;
    uniform sampler2D sAlbedoBuffer;
    uniform sampler2D sNormalBuffer;
    uniform sampler2D sDepthBuffer;
    uniform sampler2D sLightBuffer;
    uniform sampler2DShadow sShadowMap;
    uniform samplerCube sFaceSelectCubeMap;
    uniform samplerCube sIndirectionCubeMap;
    uniform samplerCube sZoneCubeMap;
    uniform sampler3D sZoneVolumeMap;
#else
    uniform sampler2D sShadowMap;
#endif

vec3 DecodeNormal(vec4 normalInput)
{
    #ifdef PACKEDNORMAL
        vec3 normal;
        normal.xy = normalInput.ag * 2.0 - 1.0;
        normal.z = sqrt(max(1.0 - dot(normal.xy, normal.xy), 0.0));
        return normal;
    #else
        return normalize(normalInput.rgb * 2.0 - 1.0);
    #endif
}

vec3 EncodeDepth(float depth)
{
    vec3 ret;
    depth *= 255.0;
    ret.x = floor(depth);
    depth = (depth - ret.x) * 255.0;
    ret.y = floor(depth);
    ret.z = (depth - ret.y);
    ret.xy *= 1.0 / 255.0;
    return ret;
}

float DecodeDepth(vec3 depth)
{
    const vec3 dotValues = vec3(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0));
    return dot(depth, dotValues);
}

float ReconstructDepth(float hwDepth)
{
    return dot(vec2(hwDepth, cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x)), cDepthReconstruct.zw);
}
#endif
