#include "Uniforms.frag"
#include "Samplers.frag"
#include "Lighting.frag"
#include "Fog.frag"

varying vec2 vTexCoord;
#ifdef PERPIXEL
    varying vec4 vLightVec;
    #ifdef SPECULAR
        varying vec3 vEyeVec;
    #endif
    varying vec3 vNormal;
    #ifdef SHADOW
        varying vec4 vShadowPos[NUMCASCADES];
    #endif
    #ifdef SPOTLIGHT
        varying vec4 vSpotPos;
    #endif
    #ifdef POINTLIGHT
        varying vec3 vCubeMaskVec;
    #endif
#else
    varying vec4 vVertexLight;
    varying vec3 vNormal;
    varying vec4 vScreenPos;
#endif

uniform sampler2D sWeightMap0;
uniform sampler2D sDetailMap1;
uniform sampler2D sDetailMap2;
uniform sampler2D sDetailMap3;

uniform vec2 cDetailTiling;

void main()
{
    // Get material diffuse albedo
    vec3 weights = texture2D(sWeightMap0, vTexCoord).rgb;
    float sumWeights = weights.r + weights.g + weights.b;
    weights /= sumWeights;
    vec2 detailTexCoord = cDetailTiling * vTexCoord;
    vec4 diffColor = cMatDiffColor * (weights.r * texture2D(sDetailMap1, detailTexCoord) +
        weights.g * texture2D(sDetailMap2, detailTexCoord) + weights.b * texture2D(sDetailMap3, detailTexCoord));

    // Get material specular albedo
    vec3 specColor = cMatSpecColor.rgb;

    #if defined(PERPIXEL)
        // Per-pixel forward lighting
        vec3 lightColor;
        vec3 lightDir;
        vec3 finalColor;
        float diff;

        vec3 normal = normalize(vNormal);

        #ifdef DIRLIGHT
            lightDir = vLightVec.xyz;
            diff = GetDiffuseDir(normal, lightDir);
        #else
            diff = GetDiffusePointOrSpot(normal, vLightVec.xyz, lightDir);
        #endif

        #ifdef SHADOW
            diff *= GetShadow(vShadowPos, vLightVec.w);
        #endif

        #if defined(SPOTLIGHT)
            lightColor = vSpotPos.w > 0.0 ? texture2DProj(sLightSpotMap, vSpotPos).rgb * cLightColor.rgb : vec3(0.0, 0.0, 0.0);
        #elif defined(CUBEMASK)
            lightColor = textureCube(sLightCubeMap, vCubeMaskVec).rgb * cLightColor.rgb;
        #else
            lightColor = cLightColor.rgb;
        #endif

        #ifdef SPECULAR
            float spec = GetSpecular(normal, vEyeVec, lightDir, cMatSpecColor.a);
            finalColor = diff * lightColor * (diffColor.rgb + spec * specColor * cLightColor.a);
        #else
            finalColor = diff * lightColor * diffColor.rgb;
        #endif

        #ifdef AMBIENT
            finalColor += cAmbientColor * diffColor.rgb;
            gl_FragColor = vec4(GetFog(finalColor, vLightVec.w), diffColor.a);
        #else
            gl_FragColor = vec4(GetLitFog(finalColor, vLightVec.w), diffColor.a);
        #endif
    #elif defined(PREPASS)
        // Fill light pre-pass G-Buffer
        vec3 normal = vNormal;

        float specPower = cMatSpecColor.a / 255.0;

        #ifdef HWDEPTH
            gl_FragColor = vec4(normal * 0.5 + 0.5, specPower);
        #else
            gl_FragData[0] = vec4(normal * 0.5 + 0.5, specPower);
            gl_FragData[1] = vec4(EncodeDepth(vVertexLight.a), 0.0);
        #endif
    #elif defined(DEFERRED)
        // Fill deferred G-buffer
        vec3 normal = vNormal;

        float specIntensity = specColor.g;
        float specPower = cMatSpecColor.a / 255.0;

        gl_FragData[0] = vec4(GetFog(vVertexLight.rgb * diffColor.rgb, vVertexLight.a), 1.0);
        gl_FragData[1] = GetFogFactor(vVertexLight.a) * vec4(diffColor.rgb, specIntensity);
        gl_FragData[2] = vec4(normal * 0.5 + 0.5, specPower);
        #ifndef HWDEPTH
            gl_FragData[3] = vec4(EncodeDepth(vVertexLight.a), 0.0);
        #endif
    #else
        // Ambient & per-vertex lighting
        vec3 finalColor = vVertexLight.rgb * diffColor.rgb;

        #ifdef MATERIAL
            // Add light pre-pass accumulation result
            // Lights are accumulated at half intensity. Bring back to full intensity now
            vec4 lightInput = 2.0 * texture2DProj(sLightBuffer, vScreenPos);
            vec3 lightSpecColor = lightInput.a * lightInput.rgb / max(GetIntensity(lightInput.rgb), 0.001);

            finalColor += lightInput.rgb * diffColor.rgb + lightSpecColor * specColor;
        #endif

        gl_FragColor = vec4(GetFog(finalColor, vVertexLight.a), diffColor.a);
    #endif
}
