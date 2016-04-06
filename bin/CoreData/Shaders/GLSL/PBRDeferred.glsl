#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "Lighting.glsl"
#include "BRDF.glsl"

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
        vec4 albedoInput = texture2D(sAlbedoBuffer, vScreenPos);
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
        vec4 albedoInput = texture2DProj(sAlbedoBuffer, vScreenPos);
        vec4 normalInput = texture2DProj(sNormalBuffer, vScreenPos);
    #endif
    
    float roughness = 0;
   
    roughness = clamp(normalInput.a, 0.1, 1.0);
    float metalness = clamp(albedoInput.a, 0.1, 1.0);

    vec3 specColor = max(albedoInput.rgb * metalness, vec3(0.08, 0.08, 0.08));
    //specColor *= cMatSpecColor.rgb;

    vec3 normal = normalize(normalInput.rgb * 2.0 - 1.0);

    vec4 projWorldPos = vec4(worldPos, 1.0);
    vec3 lightColor;
    vec3 lightDir;
    
    float diff = GetDiffuse(normal, worldPos, lightDir);

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

    vec3 toCamera = normalize(-worldPos);
    vec3 lightVec = lightDir;
 
    vec3 diffHn = normalize(toCamera + lightDir);
    float diffvdh = max(0.0, dot(toCamera, diffHn));
    float diffndl = max(0.0, dot(normal, lightDir));
    float diffndv = max(1e-5, dot(normal, toCamera));
  
    float areaLight = 1;
    // #if defined(POINTLIGHT)               
    //     areaLight = AreaLight(lightVec, toCamera, normal, -worldPos + cLightPosPS.xyz, roughness);
    // #endif
   
    vec3 diffuseTerm = BurleyDiffuse(albedoInput.rgb, roughness, diffndv, diffndl, diffvdh) * diff * lightColor.rgb;

    vec3 Hn = normalize(toCamera + lightVec);
    float vdh = max(0.0, dot(toCamera, Hn));
    float ndh = max(0.0, dot(normal, Hn));
    float ndl = max(0.0, dot(normal, lightVec));
    float ndv = max(1e-5, dot(normal, toCamera));
   

    vec3 fresnelTerm = SchlickGaussianFresnel(specColor, vdh) ;
    float distTerm = GGXDistribution(ndh, roughness) * areaLight;
    float visTerm = SchlickVisibility(ndl, ndv, roughness);

    gl_FragColor.a = 1;
    gl_FragColor.rgb = LinearFromSRGB((diffuseTerm + distTerm * visTerm * fresnelTerm * lightColor) * diff);
        
}
