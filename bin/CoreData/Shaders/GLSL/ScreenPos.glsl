#ifdef COMPILEVS
mat3 GetCameraRot()
{
    return mat3(cViewInv[0][0], cViewInv[0][1], cViewInv[0][2],
        cViewInv[1][0], cViewInv[1][1], cViewInv[1][2],
        cViewInv[2][0], cViewInv[2][1], cViewInv[2][2]);
}

vec4 GetScreenPos(vec4 clipPos)
{
    return vec4(
        clipPos.x * cGBufferOffsets.z + cGBufferOffsets.x * clipPos.w,
        clipPos.y * cGBufferOffsets.w + cGBufferOffsets.y * clipPos.w,
        0.0,
        clipPos.w);
}

vec2 GetScreenPosPreDiv(vec4 clipPos)
{
    return vec2(
        clipPos.x / clipPos.w * cGBufferOffsets.z + cGBufferOffsets.x,
        clipPos.y / clipPos.w * cGBufferOffsets.w + cGBufferOffsets.y);
}

vec2 GetQuadTexCoord(vec4 clipPos)
{
    return vec2(
        clipPos.x / clipPos.w * 0.5 + 0.5,
        clipPos.y / clipPos.w * 0.5 + 0.5);
}

vec2 GetQuadTexCoordNoFlip(vec3 worldPos)
{
    return vec2(
        worldPos.x * 0.5 + 0.5,
        -worldPos.y * 0.5 + 0.5);
}

vec3 GetFarRay(vec4 clipPos)
{
    vec3 viewRay = vec3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        cFrustumSize.z);

    return viewRay * GetCameraRot();
}

vec3 GetNearRay(vec4 clipPos)
{
    vec3 viewRay = vec3(
        clipPos.x / clipPos.w * cFrustumSize.x,
        clipPos.y / clipPos.w * cFrustumSize.y,
        0.0);

    return (viewRay * GetCameraRot()) * cDepthMode.x;
}
#endif
