#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"
#include "Lighting.vert"

varying vec2 vTexCoord;
#ifdef HEIGHTFOG
    varying vec3 vWorldPos;
#endif
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

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetTexCoord(iTexCoord);
    vNormal = GetWorldNormal(modelMatrix);

    #ifdef HEIGHTFOG
        vWorldPos = worldPos;
    #endif

    #ifdef PERPIXEL
        // Per-pixel forward lighting
        vec4 projWorldPos = vec4(worldPos, 1.0);

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            for (int i = 0; i < NUMCASCADES; i++)
                vShadowPos[i] = GetShadowPos(i, projWorldPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            vSpotPos = cLightMatrices[0] * projWorldPos;
        #endif

        #ifdef POINTLIGHT
            vCubeMaskVec = mat3(cLightMatrices[0][0].xyz, cLightMatrices[0][1].xyz, cLightMatrices[0][2].xyz) * (cLightPos.xyz - worldPos);
        #endif

        #ifdef DIRLIGHT
            vLightVec = vec4(cLightDir, GetDepth(gl_Position));
        #else
            vLightVec = vec4((cLightPos.xyz - worldPos) * cLightPos.w, GetDepth(gl_Position));
        #endif
        #ifdef SPECULAR
            vEyeVec = cCameraPos - worldPos;
        #endif
    #else
        // Ambient & per-vertex lighting
        vVertexLight = vec4(GetAmbient(GetZonePos(worldPos)), GetDepth(gl_Position));

        #ifdef NUMVERTEXLIGHTS
            for (int i = 0; i < NUMVERTEXLIGHTS; ++i)
                vVertexLight.rgb += GetVertexLight(i, worldPos, vNormal) * cVertexLights[i * 3].rgb;
        #endif
        
        vScreenPos = GetScreenPos(gl_Position);
    #endif
}
