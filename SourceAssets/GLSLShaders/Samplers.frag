uniform sampler2D sDiffMap;
uniform samplerCube sDiffCubeMap;
uniform sampler2D sNormalMap;
uniform sampler2D sSpecMap;
uniform sampler2D sDetailMap;
uniform sampler2D sEnvMap;
uniform samplerCube sEnvCubeMap;
uniform sampler2D sEmissiveMap;
uniform sampler2DShadow sShadowMap;
uniform sampler2D sLightRampMap;
uniform sampler2D sLightSpotMap;
uniform samplerCube sLightCubeMap;
uniform sampler2D sDiffBuffer;
uniform sampler2D sNormalBuffer;
uniform sampler2D sDepthBuffer;
uniform sampler2D sLightBuffer;

vec3 UnpackNormal(vec4 normalInput)
{
    vec3 normal;
    normal.xy = normalInput.ag * 2.0 - 1.0;
    normal.z = sqrt(max(1.0 - dot(normal.xy, normal.xy), 0.0));
    return normal;
}

float ReconstructDepth(float hwDepth)
{
    return cDepthReconstruct.y / (hwDepth - cDepthReconstruct.x);
}

float GetIntensity(vec3 color)
{
    const float dotValue = 1.0 / 3.0;

    return dot(color, vec3(dotValue, dotValue, dotValue));
}