#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"

#ifdef DIRLIGHT
    varying vec2 vScreenPos;
#else
    varying vec4 vScreenPos;
#endif
varying vec3 vFarRay;
#ifdef ORTHO
    varying vec3 vNearRay;
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    #ifdef DIRLIGHT
        vScreenPos = GetScreenPosPreDiv(gl_Position);
        vFarRay = GetFarRay(gl_Position);
        #ifdef ORTHO
            vNearRay = GetNearRay(gl_Position);
        #endif
    #else
        vScreenPos = GetScreenPos(gl_Position);
        vFarRay = GetFarRay(gl_Position) * gl_Position.w;
        #ifdef ORTHO
            vNearRay = GetNearRay(gl_Position) * gl_Position.w;
        #endif
    #endif
}

void PS()
{
    // If rendering a directional light quad, optimize out the w divide
    #ifdef DIRLIGHT
        #ifdef HWDEPTH
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
        #ifdef HWDEPTH
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

    // Position acquired via near/far ray is relative to camera. Bring position to world space
    worldPos += cCameraPosPS;
    
    vec3 normal = normalize(normalInput.rgb * 2.0 - 1.0);
    vec4 projWorldPos = vec4(worldPos, 1.0);
    vec3 lightColor;
    vec3 lightDir;

    // Accumulate light at half intensity to allow 2x "overburn"
    float diff = 0.5 * GetDiffuse(normal, worldPos, lightDir);

    #ifdef SHADOW
        diff *= GetShadowDeferred(projWorldPos, depth);
    #endif
    
    #if defined(SPOTLIGHT)
        vec4 spotPos = projWorldPos * cLightMatricesPS[0];
        lightColor = spotPos.w > 0.0 ? texture2DProj(sLightSpotMap, spotPos).rgb * cLightColor.rgb : vec3(0.0);
    #elif defined(CUBEMASK)
        mat3 lightVecRot = mat3(cLightMatricesPS[0][0].xyz, cLightMatricesPS[0][1].xyz, cLightMatricesPS[0][2].xyz);
        lightColor = textureCube(sLightCubeMap, (worldPos - cLightPosPS.xyz) * lightVecRot).rgb * cLightColor.rgb;
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
