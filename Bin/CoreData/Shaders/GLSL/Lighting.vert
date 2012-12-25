vec3 GetAmbient(float zonePos)
{
    return cAmbientStartColor + zonePos * cAmbientEndColor;
}

#ifdef NUMVERTEXLIGHTS
float GetVertexLight(int index, vec3 worldPos, vec3 normal)
{
    vec3 lightDir = cVertexLights[index * 3 + 1].xyz;
    vec3 lightPos = cVertexLights[index * 3 + 2].xyz;
    float invRange = cVertexLights[index * 3].w;
    float cutoff = cVertexLights[index * 3 + 1].w;
    float invCutoff = cVertexLights[index * 3 + 2].w;

    // Directional light
    if (invRange == 0.0)
    {
        float NdotL = max(dot(normal, lightDir), 0.0);
        return NdotL;
    }
    // Point/spot light
    else
    {
        vec3 lightVec = (lightPos - worldPos) * invRange;
        float lightDist = length(lightVec);
        vec3 localDir = lightVec / lightDist;
        float NdotL = max(dot(normal, localDir), 0.0);
        float atten = clamp(1.0 - lightDist * lightDist, 0.0, 1.0);
        float spotEffect = dot(localDir, lightDir);
        float spotAtten = clamp((spotEffect - cutoff) * invCutoff, 0.0, 1.0);
        return NdotL * atten * spotAtten;
    }
}

float GetVertexLightVolumetric(int index, vec3 worldPos)
{
    vec3 lightDir = cVertexLights[index * 3 + 1].xyz;
    vec3 lightPos = cVertexLights[index * 3 + 2].xyz;
    float invRange = cVertexLights[index * 3].w;
    float cutoff = cVertexLights[index * 3 + 1].w;
    float invCutoff = cVertexLights[index * 3 + 2].w;

    // Directional light
    if (invRange == 0.0)
        return 1.0;
    // Point/spot light
    else
    {
        vec3 lightVec = (lightPos - worldPos) * invRange;
        float lightDist = length(lightVec);
        vec3 localDir = lightVec / lightDist;
        float atten = clamp(1.0 - lightDist * lightDist, 0.0, 1.0);
        float spotEffect = dot(localDir, lightDir);
        float spotAtten = clamp((spotEffect - cutoff) * invCutoff, 0.0, 1.0);
        return atten * spotAtten;
    }
}
#endif

#ifdef SHADOW

#ifdef DIRLIGHT
    #ifndef GL_ES
        #define NUMCASCADES 4
    #else
        #define NUMCASCADES 2
    #endif
#else
    #define NUMCASCADES 1
#endif

vec4 GetShadowPos(int index, vec4 projWorldPos)
{
    #if defined(DIRLIGHT)
        return cLightMatrices[index] * projWorldPos;
    #elif defined(SPOTLIGHT)
        return cLightMatrices[1] * projWorldPos;
    #else
        return vec4(projWorldPos.xyz - cLightPos.xyz, 1.0);
    #endif
}

#endif
