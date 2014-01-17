#include "Uniforms.vert"
#include "Transform.vert"
#include "ScreenPos.vert"

varying vec4 vScreenPos;
varying vec4 vRefractUV;
varying vec2 vReflectUV;

void main()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vScreenPos = GetScreenPos(gl_Position);
    vRefractUV = vec4(worldPos, GetDepth(gl_Position));
    // GetQuadTexCoord() returns a float2 that is OK for quad rendering; multiply it with output W
    // coordinate to make it work with arbitrary meshes such as the water plane (perform divide in pixel shader)
    // Also because the quadTexCoord is based on the clip position, and Y is flipped when rendering to a texture
    // on OpenGL, must flip again to cancel it out
    vReflectUV = GetQuadTexCoord(gl_Position);
    vReflectUV.y = 1.0 - vReflectUV.y;
    vReflectUV *= gl_Position.w;

}
