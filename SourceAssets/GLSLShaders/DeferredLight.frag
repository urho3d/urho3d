#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"

#ifdef DIRLIGHT
    varying vec2 vScreenPos;
#else
    varying vec4 vScreenPos;
#endif
varying vec3 vFarRay;
#ifdef ORTHO
    varying vec3 vNearRay;
#endif

void main()
{
    // If rendering a directional light quad, optimize out the w divide
    #ifdef DIRLIGHT
        #if defined(HWDEPTH) && defined(ORTHO)
            float depth = texture2D(sDepthBuffer, vScreenPos).r;
        #elif defined(HWDEPTH) && !defined(ORTHO)
            float depth = ReconstructDepth(texture2D(sDepthBuffer, vScreenPos).r);
        #else
            float depth = DecodeDepth(texture2D(sDepthBuffer, vScreenPos).rgb);
        #endif
        #ifdef ORTHO
            vec3 worldPos = mix(vNearRay, vFarRay, depth);
        #else
            vec3 worldPos = vFarRay * depth;
        #endif
        vec4 albedoInput = texture2D(sAlbedoBuffer, vScreenPos);
        vec4 normalInput = texture2D(sNormalBuffer, vScreenPos);
    #else
        #if defined(HWDEPTH) && defined(ORTHO)
            float depth = texture2DProj(sDepthBuffer, vScreenPos).r;
        #elif defined(HWDEPTH) && !defined(ORTHO)
            float depth = ReconstructDepth(texture2DProj(sDepthBuffer, vScreenPos).r);
        #else
            float depth = DecodeDepth(texture2DProj(sDepthBuffer, vScreenPos).rgb);
        #endif
        #ifdef ORTHO
            vec3 worldPos = mix(vNearRay, vFarRay, depth) / vScreenPos.w;
        #else
            vec3 worldPos = vFarRay * depth / vScreenPos.w;
        #endif
        vec4 albedoInput = texture2DProj(sAlbedoBuffer, vScreenPos);
        vec4 normalInput = texture2DProj(sNormalBuffer, vScreenPos);
    #endif

    vec3 normal = normalize(normalInput.rgb * 2.0 - 1.0);
    vec4 projWorldPos = vec4(worldPos, 1.0);
    vec3 lightColor;
    vec3 lightDir;
    float diff;

    #ifdef DIRLIGHT
        lightDir = cLightDirPS;
        diff = GetDiffuseDir(normal, lightDir);
    #else
        vec3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
        diff = GetDiffusePointOrSpot(normal, lightVec, lightDir);
    #endif

    #ifdef SHADOW
        #if defined(DIRLIGHT)
            vec4 shadowPos = GetDirShadowPosDeferred(cLightMatricesPS, projWorldPos, depth);
            diff *= min(GetShadow(shadowPos) + GetShadowFade(depth), 1.0);
        #elif defined(SPOTLIGHT)
            vec4 shadowPos = cLightMatricesPS[1] * projWorldPos;
            diff *= GetShadow(shadowPos);
        #else
            vec3 shadowPos = worldPos - cLightPosPS.xyz;
            diff *= GetCubeShadow(shadowPos);
        #endif
    #endif

    #if defined(SPOTLIGHT)
        vec4 spotPos = cLightMatricesPS[0] * projWorldPos;
        lightColor = spotPos.w > 0.0 ? texture2DProj(sLightSpotMap, spotPos).rgb * cLightColor.rgb : vec3(0.0);
    #elif defined(CUBEMASK)
        mat3 lightVecRot = mat3(cLightMatricesPS[0][0].xyz, cLightMatricesPS[0][1].xyz, cLightMatricesPS[0][2].xyz);
        lightColor = textureCube(sLightCubeMap, lightVecRot * lightVec).rgb * cLightColor.rgb;
    #else
        lightColor = cLightColor.rgb;
    #endif

    #ifdef SPECULAR
        float spec = GetSpecular(normal, -worldPos, lightDir, normalInput.a * 255.0);
        gl_FragColor = diff * vec4(lightColor * (albedoInput.rgb + spec * cLightColor.a * albedoInput.aaa), 0.0);
    #else
        gl_FragColor = diff * vec4(lightColor * albedoInput.rgb, 0.0);
    #endif
}
