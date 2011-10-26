#include "Uniforms.vert"
#include "Transform.vert"

varying vec2 vTexCoord;
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif
varying vec4 vLightVec;
#ifndef UNLIT
    #ifdef SPECULAR
        varying vec3 vEyeVec;
    #endif
    #ifndef NORMALMAP
        varying vec3 vNormal;
    #endif
    #ifdef SHADOW
        #if defined(DIRLIGHT)
            varying vec4 vShadowPos[4];
        #elif defined(SPOTLIGHT)
            varying vec4 vShadowPos;
        #else
            varying vec3 vShadowPos;
        #endif
    #endif
    #ifdef SPOTLIGHT
        varying vec4 vSpotPos;
    #endif
    #ifdef POINTLIGHT
        varying vec3 vCubeMaskVec;
    #endif
#endif

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vTexCoord = GetTexCoord(iTexCoord);

    #ifndef UNLIT

        #ifdef NORMALMAP
            vec3 vNormal;
            vec3 vTangent;
            vec3 vBitangent;
        #endif
    
        vNormal = GetWorldNormal(modelMatrix);
        vec3 centeredWorldPos = worldPos - cCameraPos;

        #if defined(DIRLIGHT)
            vLightVec = vec4(cLightDir, GetDepth(gl_Position));
        #elif defined(LIGHT)
            vLightVec = vec4((cLightPos - centeredWorldPos) * cLightAtten, GetDepth(gl_Position));
        #else
            vLightVec = vec4(0.0, 0.0, 0.0, GetDepth(gl_Position));
        #endif

        #ifdef SHADOW
            // Shadow projection: transform from world space to shadow space
            GetShadowPos(worldPos, vShadowPos);
        #endif

        #ifdef SPOTLIGHT
            // Spotlight projection: transform from world space to projector texture coordinates
            vec4 projWorldPos = vec4(worldPos, 1.0);
            vSpotPos = cSpotProj * projWorldPos;
        #endif

        #ifdef POINTLIGHT
            vCubeMaskVec = cLightVecRot * vLightVec.xyz;
        #endif

        #ifdef NORMALMAP
            vTangent = GetWorldTangent(modelMatrix);
            vBitangent = cross(vTangent, vNormal) * iTangent.w;
            mat3 tbn = mat3(vTangent, vBitangent, vNormal);
            #ifdef LIGHT
                vLightVec.xyz = vLightVec.xyz * tbn;
            #endif
            #ifdef SPECULAR
                vEyeVec = -centeredWorldPos * tbn;
            #endif
        #elif defined(SPECULAR)
            vEyeVec = -centeredWorldPos;
        #endif
        
    #else
    
        vLightVec = vec4(0.0, 0.0, 0.0, GetDepth(gl_Position));

    #endif

    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}
