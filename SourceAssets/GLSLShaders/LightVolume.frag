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
        vec4 normalInput = texture2DProj(sNormalBuffer, vScreenPos);
    #endif

    // With specular, normalization greatly improves stability of reflections,
    // considering input is only 8 bits per axis
    #ifdef SPECULAR
        vec3 normal = normalize(normalInput.rgb * 2.0 - 1.0);
    #else
        vec3 normal = normalInput.rgb * 2.0 - 1.0;
    #endif

    vec4 projWorldPos = vec4(worldPos, 1.0);
    vec3 lightColor;
    vec3 lightDir;
    float diff;

    // Accumulate light at half intensity to allow 2x "overburn"
    #ifdef DIRLIGHT
        lightDir = cLightDirPS;
        diff = 0.5 * GetDiffuseDir(normal, lightDir);
    #else
        vec3 lightVec = (cLightPosPS.xyz - worldPos) * cLightPosPS.w;
        diff = 0.5 * GetDiffusePointOrSpot(normal, lightVec, lightDir);
    #endif

    #ifdef SHADOW
        #if defined(DIRLIGHT)
            mat4 shadowMatrix = GetDirShadowMatrix(depth, cLightMatricesPS);
            vec4 shadowPos = shadowMatrix * projWorldPos;
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
        lightColor = spotPos.w > 0.0 ? texture2DProj(sLightSpotMap, spotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
    #elif defined(CUBEMASK)
        lightColor = textureCube(sLightCubeMap, lightVec).rgb * cLightColor.rgb;
    #else
        lightColor = cLightColor.rgb;
    #endif

    #ifdef SPECULAR
        float spec = lightColor.g * GetSpecular(normal, -worldPos, lightDir, normalInput.a * 255.0);
        gl_FragColor = diff * vec4(lightColor, spec * cLightColor.a);
    #else
        gl_FragColor = diff * vec4(lightColor, 0.0);
    #endif
}
