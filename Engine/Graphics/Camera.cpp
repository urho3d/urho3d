//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "Camera.h"
#include "Context.h"
#include "Drawable.h"

#include "DebugNew.h"

static const float DEFAULT_NEARCLIP = 0.1f;
static const float DEFAULT_FARCLIP = 1000.0f;
static const float DEFAULT_FOV = 45.0f;
static const float DEFAULT_ORTHOSIZE = 20.0f;

OBJECTTYPESTATIC(Camera);

Camera::Camera(Context* context) :
    Component(context),
    projectionOffset_(Vector2::ZERO),
    nearClip_(DEFAULT_NEARCLIP),
    farClip_(DEFAULT_FARCLIP),
    fov_(DEFAULT_FOV),
    orthoSize_(DEFAULT_ORTHOSIZE),
    aspectRatio_(1.0f),
    zoom_(1.0f),
    lodBias_(1.0f),
    viewMask_(DEFAULT_VIEWMASK),
    viewOverrideFlags_(VO_NONE),
    orthographic_(false),
    autoAspectRatio_(true),
    flipVertical_(false)
{
}

Camera::~Camera()
{
}

void Camera::RegisterObject(Context* context)
{
    context->RegisterFactory<Camera>();
    
    ACCESSOR_ATTRIBUTE(Camera, VAR_FLOAT, "Near Clip", GetNearClip, SetNearClip, float, DEFAULT_NEARCLIP, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Camera, VAR_FLOAT, "Far Clip", GetFarClip, SetFarClip, float, DEFAULT_FARCLIP, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Camera, VAR_FLOAT, "FOV", GetFov, SetFov, float, DEFAULT_FOV, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Camera, VAR_FLOAT, "Aspect Ratio", GetAspectRatio, SetAspectRatio, float, 1.0f, AM_DEFAULT);
    ATTRIBUTE(Camera, VAR_BOOL, "Auto Aspect Ratio", autoAspectRatio_, true, AM_DEFAULT);
    ATTRIBUTE(Camera, VAR_BOOL, "Orthographic", orthographic_, false, AM_DEFAULT);
    ATTRIBUTE(Camera, VAR_FLOAT, "Orthographic Size", orthoSize_, DEFAULT_ORTHOSIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Camera, VAR_FLOAT, "Zoom", GetZoom, SetZoom, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Camera, VAR_FLOAT, "LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    ATTRIBUTE(Camera, VAR_INT, "View Mask", viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE(Camera, VAR_INT, "View Override Flags", viewOverrideFlags_, VO_NONE, AM_DEFAULT);
    ATTRIBUTE(Camera, VAR_VECTOR2, "Projection Offset", projectionOffset_, Vector2::ZERO, AM_DEFAULT);
}

void Camera::SetNearClip(float nearClip)
{
    nearClip_ = Max(nearClip, M_MIN_NEARCLIP);
}

void Camera::SetFarClip(float farClip)
{
    farClip_ = Max(farClip, M_MIN_NEARCLIP);
}

void Camera::SetFov(float fov)
{
    fov_ = Clamp(fov, 0.0f, M_MAX_FOV);
}

void Camera::SetOrthoSize(float orthoSize)
{
    orthoSize_ = orthoSize;
    aspectRatio_ = 1.0f;
}

void Camera::SetOrthoSize(const Vector2& orthoSize)
{
    orthoSize_ = orthoSize.y_;
    aspectRatio_ = orthoSize.x_ / orthoSize.y_;
}

void Camera::SetAspectRatio(float aspectRatio)
{
    aspectRatio_ = aspectRatio;
}

void Camera::SetZoom(float zoom)
{
    zoom_ = Max(zoom, M_EPSILON);
}

void Camera::SetLodBias(float bias)
{
    lodBias_ = Max(bias, M_EPSILON);
}

void Camera::SetViewMask(unsigned mask)
{
    viewMask_ = mask;
}

void Camera::SetViewOverrideFlags(unsigned flags)
{
    viewOverrideFlags_ = flags;
}

void Camera::SetOrthographic(bool enable)
{
    orthographic_ = enable;
}

void Camera::SetAutoAspectRatio(bool enable)
{
    autoAspectRatio_ = enable;
}

void Camera::SetProjectionOffset(const Vector2& offset)
{
    projectionOffset_ = offset;
}

void Camera::SetFlipVertical(bool enable)
{
    flipVertical_ = enable;
}

float Camera::GetNearClip() const
{
    // Orthographic camera has always near clip at 0 to avoid trouble with shader depth parameters,
    // and unlike in perspective mode there should be no depth buffer precision issue
    if (!orthographic_)
        return nearClip_;
    else
        return 0.0f;
}

Frustum Camera::GetSplitFrustum(float nearClip, float farClip)
{
    Frustum ret;
    
    nearClip = Max(nearClip, GetNearClip());
    farClip = Min(farClip, farClip_);
    if (farClip < nearClip)
        farClip = nearClip;
    
    if (!orthographic_)
        ret.Define(fov_, aspectRatio_, zoom_, nearClip, farClip, GetWorldTransform());
    else
        ret.DefineOrtho(orthoSize_, aspectRatio_, zoom_, nearClip, farClip, GetWorldTransform());
    
    return ret;
}

Frustum Camera::GetViewSpaceFrustum() const
{
    Frustum ret;
    
    if (!orthographic_)
        ret.Define(fov_, aspectRatio_, zoom_, GetNearClip(), farClip_);
    else
        ret.DefineOrtho(orthoSize_, aspectRatio_, zoom_, GetNearClip(), farClip_);
    
    return ret;
}

Frustum Camera::GetViewSpaceSplitFrustum(float nearClip, float farClip) const
{
    Frustum ret;
    
    nearClip = Max(nearClip, GetNearClip());
    farClip = Min(farClip, farClip_);
    if (farClip < nearClip)
        farClip = nearClip;
    
    if (!orthographic_)
        ret.Define(fov_, aspectRatio_, zoom_, nearClip, farClip);
    else
        ret.DefineOrtho(orthoSize_, aspectRatio_, zoom_, nearClip, farClip);
    
    return ret;
}

Ray Camera::GetScreenRay(float x, float y)
{
    Ray ret;
    
    // If projection is invalid, just return a ray pointing forward
    if (!IsProjectionValid())
    {
        ret.origin_ = GetWorldPosition();
        ret.direction_ = GetForwardVector();
        return ret;
    }
    
    Matrix4 viewProjInverse = (GetProjection() * GetInverseWorldTransform()).Inverse();
    
    // The parameters range from 0.0 to 1.0. Expand to normalized device coordinates (-1.0 to 1.0) & flip Y axis
    x = 2.0f * x - 1.0f;
    y = 1.0f - 2.0f * y;
    
    #ifdef USE_OPENGL
    Vector3 near(x, y, -1.0f);
    Vector3 far(x, y, 1.0f);
    #else
    Vector3 near(x, y, 0.0f);
    Vector3 far(x, y, 1.0f);
    #endif
    
    ret.origin_ = viewProjInverse * near;
    ret.direction_ = ((viewProjInverse * far) - ret.origin_).Normalized();
    return ret;
}

Frustum Camera::GetFrustum() const
{
    Frustum ret;
    
    if (!orthographic_)
        ret.Define(fov_, aspectRatio_, zoom_, GetNearClip(), farClip_, GetWorldTransform());
    else
        ret.DefineOrtho(orthoSize_, aspectRatio_, zoom_, GetNearClip(), farClip_, GetWorldTransform());
    
    return ret;
}

Matrix4 Camera::GetProjection() const
{
    Matrix4 ret(Matrix4::ZERO);
    
    if (!orthographic_)
    {
        float nearClip = GetNearClip();
        float h = (1.0f / tanf(fov_ * M_DEGTORAD * 0.5f)) * zoom_;
        float w = h / aspectRatio_;
        #ifdef USE_OPENGL
        float q = (farClip_ + nearClip) / (farClip_ - nearClip);
        float r = -2.0f * farClip_ * nearClip / (farClip_ - nearClip);
        #else
        float q = farClip_ / (farClip_ - nearClip);
        float r = -q * nearClip;
        #endif
        
        ret.m00_ = w;
        ret.m02_ = projectionOffset_.x_ * 2.0f;
        ret.m11_ = h;
        ret.m12_ = projectionOffset_.y_ * 2.0f;
        ret.m22_ = q;
        ret.m23_ = r;
        ret.m32_ = 1.0f;
    }
    else
    {
        // Disregard near clip, because it does not affect depth precision as with perspective projection
        float h = (1.0f / (orthoSize_ * 0.5f)) * zoom_;
        float w = h / aspectRatio_;
        #ifdef USE_OPENGL
        float q = 2.0f / farClip_;
        float r = -1.0f;
        #else
        float q = 1.0f / farClip_;
        float r = 0.0f;
        #endif
        
        ret.m00_ = w;
        ret.m03_ = projectionOffset_.x_ * 2.0f;
        ret.m11_ = h;
        ret.m13_ = projectionOffset_.y_ * 2.0f;
        ret.m22_ = q;
        ret.m23_ = r;
        ret.m33_ = 1.0f;
    }
    
    if (flipVertical_)
    {
        Matrix4 flip(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
        
        ret = flip * ret;
    }
    
    return ret;
}

void Camera::GetFrustumSize(Vector3& near, Vector3& far) const
{
    near.z_ = GetNearClip();
    far.z_ = farClip_;
    
    if (!orthographic_)
    {
        float halfViewSize = tanf(fov_ * M_DEGTORAD * 0.5f) / zoom_;
        near.y_ = near.z_ * halfViewSize;
        near.x_ = near.y_ * aspectRatio_;
        far.y_ = far.z_ * halfViewSize;
        far.x_ = far.y_ * aspectRatio_;
    }
    else
    {
        float halfViewSize = orthoSize_ * 0.5f / zoom_;
        near.y_ = far.y_ = halfViewSize;
        near.x_ = far.x_ = near.y_ * aspectRatio_;
    }
    
    if (flipVertical_)
    {
        near.y_ = -near.y_;
        far.y_ = -far.y_;
    }
}

float Camera::GetHalfViewSize() const
{
    if (!orthographic_)
        return tanf(fov_ * M_DEGTORAD * 0.5f) / zoom_;
    else
        return orthoSize_ * 0.5f / zoom_;
}

Vector3 Camera::GetForwardVector()
{
    return GetWorldTransform().RotationMatrix() * Vector3::FORWARD;
}

Vector3 Camera::GetRightVector()
{
    return GetWorldTransform().RotationMatrix() * Vector3::RIGHT;
}

Vector3 Camera::GetUpVector()
{
    return GetWorldTransform().RotationMatrix() * Vector3::UP;
}

float Camera::GetDistance(const Vector3& worldPos)
{
    if (!orthographic_)
        return (worldPos - GetWorldPosition()).Length();
    else
        return fabsf((GetInverseWorldTransform() * worldPos).z_);
}

float Camera::GetDistanceSquared(const Vector3& worldPos)
{
    if (!orthographic_)
        return (worldPos - GetWorldPosition()).LengthSquared();
    else
    {
        float distance = (GetInverseWorldTransform() * worldPos).z_;
        return distance * distance;
    }
}

float Camera::GetLodDistance(float distance, float scale, float bias) const
{
    float d = Max(lodBias_ * bias * scale * zoom_, M_EPSILON);
    if (!orthographic_)
        return distance / d;
    else
        return orthoSize_ / d;
}

bool Camera::IsProjectionValid() const
{
    return farClip_ > GetNearClip();
}
