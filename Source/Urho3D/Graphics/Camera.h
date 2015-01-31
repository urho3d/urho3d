//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Math/Frustum.h"
#include "../Scene/Component.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Math/Ray.h"

namespace Urho3D
{

static const float DEFAULT_NEARCLIP = 0.1f;
static const float DEFAULT_FARCLIP = 1000.0f;
static const float DEFAULT_CAMERA_FOV = 45.0f;
static const float DEFAULT_ORTHOSIZE = 20.0f;

static const unsigned VO_NONE = 0x0;
static const unsigned VO_LOW_MATERIAL_QUALITY = 0x1;
static const unsigned VO_DISABLE_SHADOWS = 0x2;
static const unsigned VO_DISABLE_OCCLUSION = 0x4;

/// %Camera component.
class URHO3D_API Camera : public Component
{
    OBJECT(Camera);

public:
    /// Construct.
    Camera(Context* context);
    /// Destruct.
    virtual ~Camera();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set near clip distance.
    void SetNearClip(float nearClip);
    /// Set far clip distance.
    void SetFarClip(float farClip);
    /// Set vertical field of view in degrees.
    void SetFov(float fov);
    /// Set orthographic mode view uniform size.
    void SetOrthoSize(float orthoSize);
    /// Set orthographic mode view non-uniform size. Disables the auto aspect ratio -mode.
    void SetOrthoSize(const Vector2& orthoSize);
    /// Set aspect ratio manually. Disables the auto aspect ratio -mode.
    void SetAspectRatio(float aspectRatio);
    /// Set polygon fill mode to use when rendering a scene.
    void SetFillMode(FillMode mode);
    /// Set zoom.
    void SetZoom(float zoom);
    /// Set LOD bias.
    void SetLodBias(float bias);
    /// Set view mask. Will be and'ed with object's view mask to see if the object should be rendered.
    void SetViewMask(unsigned mask);
    /// Set view override flags.
    void SetViewOverrideFlags(unsigned flags);
    /// Set orthographic mode enabled/disabled.
    void SetOrthographic(bool enable);
    /// Set automatic aspect ratio based on viewport dimensions. Enabled by default.
    void SetAutoAspectRatio(bool enable);
    /// Set projection offset. It needs to be calculated as (offset in pixels) / (viewport dimensions.)
    void SetProjectionOffset(const Vector2& offset);
    /// Set reflection mode.
    void SetUseReflection(bool enable);
    /// Set reflection plane in world space for reflection mode.
    void SetReflectionPlane(const Plane& plane);
    /// Set whether to use a custom clip plane.
    void SetUseClipping(bool enable);
    /// Set custom clipping plane in world space.
    void SetClipPlane(const Plane& plane);
    /// Set vertical flipping mode. Called internally by View to resolve OpenGL / Direct3D9 rendertarget sampling differences.
    void SetFlipVertical(bool enable);

    /// Return far clip distance.
    float GetFarClip() const { return farClip_; }
    /// Return near clip distance.
    float GetNearClip() const;
    /// Return vertical field of view in degrees.
    float GetFov() const { return fov_; }
    /// Return orthographic mode size.
    float GetOrthoSize() const { return orthoSize_; }
    /// Return aspect ratio.
    float GetAspectRatio() const { return aspectRatio_; }
    /// Return zoom.
    float GetZoom() const { return zoom_; }
    /// Return LOD bias.
    float GetLodBias() const { return lodBias_; }
    /// Return view mask.
    unsigned GetViewMask() const { return viewMask_; }
    /// Return view override flags.
    unsigned GetViewOverrideFlags() const { return viewOverrideFlags_; }
    /// Return fill mode.
    FillMode GetFillMode() const { return fillMode_; }
    /// Return orthographic flag.
    bool IsOrthographic() const { return orthographic_; }
    /// Return auto aspect ratio flag.
    bool GetAutoAspectRatio() const { return autoAspectRatio_; }
    /// Return frustum in world space.
    const Frustum& GetFrustum() const;
    /// Return API-specific projection matrix.
    const Matrix4& GetProjection() const;
    /// Return either API-specific or API-independent (D3D convention) projection matrix.
    Matrix4 GetProjection(bool apiSpecific) const;
    /// Return view matrix.
    const Matrix3x4& GetView() const;
    /// Return frustum near and far sizes.
    void GetFrustumSize(Vector3& near, Vector3& far) const;
    /// Return half view size.
    float GetHalfViewSize() const;
    /// Return frustum split by custom near and far clip distances.
    Frustum GetSplitFrustum(float nearClip, float farClip) const;
    /// Return frustum in view space.
    Frustum GetViewSpaceFrustum() const;
    /// Return split frustum in view space.
    Frustum GetViewSpaceSplitFrustum(float nearClip, float farClip) const;
    /// Return ray corresponding to normalized screen coordinates (0.0 - 1.0).
    Ray GetScreenRay(float x, float y) const;
    // Convert a world space point to normalized screen coordinates (0.0 - 1.0).
    Vector2 WorldToScreenPoint(const Vector3& worldPos) const;
    // Convert normalized screen coordinates (0.0 - 1.0) and depth to a world space point.
    Vector3 ScreenToWorldPoint(const Vector3& screenPos) const;
    /// Return projection offset.
    const Vector2& GetProjectionOffset() const { return projectionOffset_; }
    /// Return whether is using reflection.
    bool GetUseReflection() const { return useReflection_; }
    /// Return the reflection plane.
    const Plane& GetReflectionPlane() const { return reflectionPlane_; }
    /// Return whether is using a custom clipping plane.
    bool GetUseClipping() const { return useClipping_; }
    /// Return the custom clipping plane.
    const Plane& GetClipPlane() const { return clipPlane_; }
    /// Return vertical flipping mode.
    bool GetFlipVertical() const { return flipVertical_; }
    /// Return whether to reverse culling; affected by vertical flipping and reflection.
    bool GetReverseCulling() const { return flipVertical_ ^ useReflection_; }
    /// Return distance to position. In orthographic mode uses only Z coordinate.
    float GetDistance(const Vector3& worldPos) const;
    /// Return squared distance to position. In orthographic mode uses only Z coordinate.
    float GetDistanceSquared(const Vector3& worldPos) const;
    /// Return a scene node's LOD scaled distance.
    float GetLodDistance(float distance, float scale, float bias) const;
    /// Return a world rotation for facing a camera on certain axes based on the existing world rotation.
    Quaternion GetFaceCameraRotation(const Vector3& position, const Quaternion& rotation, FaceCameraMode mode);
    /// Get effective world transform for matrix and frustum calculations including reflection but excluding node scaling.
    Matrix3x4 GetEffectiveWorldTransform() const;
    /// Return if projection parameters are valid for rendering and raycasting.
    bool IsProjectionValid() const;

    /// Set aspect ratio without disabling the "auto aspect ratio" mode. Called internally by View.
    void SetAspectRatioInternal(float aspectRatio);
    /// Set orthographic size attribute without forcing the aspect ratio.
    void SetOrthoSizeAttr(float orthoSize);
    /// Set reflection plane attribute.
    void SetReflectionPlaneAttr(const Vector4& value);
    /// Return reflection plane attribute.
    Vector4 GetReflectionPlaneAttr() const;
    /// Set clipping plane attribute.
    void SetClipPlaneAttr(const Vector4& value);
    /// Return clipping plane attribute.
    Vector4 GetClipPlaneAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);

private:
    /// Cached view matrix.
    mutable Matrix3x4 view_;
    /// Cached projection matrix.
    mutable Matrix4 projection_;
    /// Cached frustum.
    mutable Frustum frustum_;
    /// View matrix dirty flag.
    mutable bool viewDirty_;
    /// Projection matrix dirty flag.
    mutable bool projectionDirty_;
    /// Frustum dirty flag.
    mutable bool frustumDirty_;
    /// Orthographic mode flag.
    bool orthographic_;
    /// Near clip distance.
    float nearClip_;
    /// Far clip distance.
    float farClip_;
    /// Field of view.
    float fov_;
    /// Orthographic view size.
    float orthoSize_;
    /// Aspect ratio.
    float aspectRatio_;
    /// Zoom.
    float zoom_;
    /// LOD bias.
    float lodBias_;
    /// View mask.
    unsigned viewMask_;
    /// View override flags.
    unsigned viewOverrideFlags_;
    /// Fill mode.
    FillMode fillMode_;
    /// Projection offset.
    Vector2 projectionOffset_;
    /// Reflection plane.
    Plane reflectionPlane_;
    /// Clipping plane.
    Plane clipPlane_;
    /// Reflection matrix calculated from the plane.
    Matrix3x4 reflectionMatrix_;
    /// Auto aspect ratio flag.
    bool autoAspectRatio_;
    /// Flip vertical flag.
    bool flipVertical_;
    /// Reflection mode enabled flag.
    bool useReflection_;
    /// Use custom clip plane flag.
    bool useClipping_;
};

}
