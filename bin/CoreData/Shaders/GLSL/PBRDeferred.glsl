#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"
#include "Constants.glsl"
#include "BRDF.glsl"
#line 40007

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
        vec4 depthInput = texture2D(sDepthBuffer, vScreenPos);
        #ifdef HWDEPTH
            float depth = ReconstructDepth(depthInput.r);
        #else
            float depth = DecodeDepth(depthInput.rgb);
        #endif
        #ifdef ORTHO
            vec3 worldPos = mix(vNearRay, vFarRay, depth);
        #else
            vec3 worldPos = vFarRay * depth;
        #endif
        vec4 albedoInput = texture2D(sAlbedoBuffer, vScreenPos);
        vec4 normalInput = texture2D(sNormalBuffer, vScreenPos);
        vec4 specularInput = texture2D(sSpecMap, vScreenPos);
    #else
        vec4 depthInput = texture2DProj(sDepthBuffer, vScreenPos);
        #ifdef HWDEPTH
            float depth = ReconstructDepth(depthInput.r);
        #else
            float depth = DecodeDepth(depthInput.rgb);
        #endif
        #ifdef ORTHO
            vec3 worldPos = mix(vNearRay, vFarRay, depth) / vScreenPos.w;
        #else
            vec3 worldPos = vFarRay * depth / vScreenPos.w;
        #endif
        vec4 albedoInput = texture2DProj(sAlbedoBuffer, vScreenPos);
        vec4 normalInput = texture2DProj(sNormalBuffer, vScreenPos);
        vec4 specularInput = texture2DProj(sSpecMap, vScreenPos);
    #endif

    // Position acquired via near/far ray is relative to camera. Bring position to world space
    worldPos += cCameraPosPS;
    
    vec3 normal = normalInput.rgb;
    float roughness = length(normal);
    normal = normalize(normal);

    vec3 specColor = specularInput.rgb;

    vec4 projWorldPos = vec4(worldPos, 1.0);

    vec3 lightDir;
    float diff = GetDiffuse(normal, worldPos, lightDir);

    #ifdef SHADOW
        diff *= GetShadowDeferred(projWorldPos, depth);
    #endif

    #if defined(SPOTLIGHT)
        vec4 spotPos = projWorldPos * cLightMatricesPS[0];
        vec3 lightColor = spotPos.w > 0.0 ? texture2DProj(sLightSpotMap, spotPos).rgb * cLightColor.rgb : vec3(0.0);
    #elif defined(CUBEMASK)
        mat3 lightVecRot = mat3(cLightMatricesPS[0][0].xyz, cLightMatricesPS[0][1].xyz, cLightMatricesPS[0][2].xyz);
        vec3 lightColor = textureCube(sLightCubeMap, (worldPos - cLightPosPS.xyz) * lightVecRot).rgb * cLightColor.rgb;
    #else
        vec3 lightColor = cLightColor.rgb;
    #endif

    vec3 toCamera = normalize(-worldPos);
    vec3 lightVec = normalize(lightDir);

    vec3 Hn = normalize(toCamera + lightVec);
    float vdh = clamp(abs(dot(toCamera, Hn)), M_EPSILON, 1.0);
    float ndh = clamp(abs(dot(normal, Hn)), M_EPSILON, 1.0);
    float ndl = clamp(abs(dot(normal, lightVec)), M_EPSILON, 1.0);
    float ndv = clamp(abs(dot(normal, toCamera)), M_EPSILON, 1.0);

    vec3 diffuseFactor = BurleyDiffuse(albedoInput.rgb, roughness, ndv, ndl, vdh);
    vec3 specularFactor = vec3(0,0,0);

     #ifdef SPECULAR
        vec3 fresnelTerm = Fresnel(specColor, vdh) ;
        float distTerm = Distribution(ndh, roughness);
        float visTerm = Visibility(ndl, ndv, roughness);

        specularFactor = SpecularBRDF(distTerm, fresnelTerm, visTerm, ndl, ndv);
    #endif

    gl_FragColor.a = 1.0;
    gl_FragColor.rgb = (diffuseFactor + specularFactor) * lightColor * diff;

}
