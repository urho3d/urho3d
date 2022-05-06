// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Math/Frustum.h"
#include "../Math/Ray.h"
#include "../Scene/Component.h"

namespace Urho3D
{

static const float DEFAULT_NEARCLIP = 0.1f;
static const float DEFAULT_FARCLIP = 1000.0f;
static const float DEFAULT_CAMERA_FOV = 45.0f;
static const float DEFAULT_ORTHOSIZE = 20.0f;

enum ViewOverride : unsigned
{
    VO_NONE = 0x0,
    VO_LOW_MATERIAL_QUALITY = 0x1,
    VO_DISABLE_SHADOWS = 0x2,
    VO_DISABLE_OCCLUSION = 0x4,
};
URHO3D_FLAGSET(ViewOverride, ViewOverrideFlags);

/// %Camera component.
class URHO3D_API Camera : public Component
{
    URHO3D_OBJECT(Camera, Component);

public:
    /// Construct.
    explicit Camera(Context* context);
    /// Destruct.
    ~Camera() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set near clip distance.
    /// @property
    void SetNearClip(float nearClip);
    /// Set far clip distance.
    /// @property
    void SetFarClip(float farClip);
    /// Set vertical field of view in degrees.
    /// @property
    void SetFov(float fov);
    /// Set orthographic mode view uniform size.
    /// @property
    void SetOrthoSize(float orthoSize);
    /// Set orthographic mode view non-uniform size. Disables the auto aspect ratio -mode.
    void SetOrthoSize(const Vector2& orthoSize);
    /// Set aspect ratio manually. Disables the auto aspect ratio -mode.
    /// @property
    void SetAspectRatio(float aspectRatio);
    /// Set polygon fill mode to use when rendering a scene.
    /// @property
    void SetFillMode(FillMode mode);
    /// Set zoom.
    /// @property
    void SetZoom(float zoom);
    /// Set LOD bias.
    /// @property
    void SetLodBias(float bias);
    /// Set view mask. Will be and'ed with object's view mask to see if the object should be rendered.
    /// @property
    void SetViewMask(unsigned mask);
    /// Set view override flags.
    /// @property
    void SetViewOverrideFlags(ViewOverrideFlags flags);
    /// Set orthographic mode enabled/disabled.
    /// @property
    void SetOrthographic(bool enable);
    /// Set automatic aspect ratio based on viewport dimensions. Enabled by default.
    /// @property
    void SetAutoAspectRatio(bool enable);
    /// Set projection offset. It needs to be calculated as (offset in pixels) / (viewport dimensions).
    /// @property
    void SetProjectionOffset(const Vector2& offset);
    /// Set reflection mode.
    /// @property
    void SetUseReflection(bool enable);
    /// Set reflection plane in world space for reflection mode.
    /// @property
    void SetReflectionPlane(const Plane& plane);
    /// Set whether to use a custom clip plane.
    /// @property
    void SetUseClipping(bool enable);
    /// Set custom clipping plane in world space.
    /// @property
    void SetClipPlane(const Plane& plane);
    /// Set vertical flipping mode. Called internally by View to resolve OpenGL / Direct3D9 rendertarget sampling differences.
    void SetFlipVertical(bool enable);
    /// Set custom projection matrix, which should be specified in D3D convention with depth range 0 - 1. Disables auto aspect ratio.
    /// @property
    /** Change any of the standard view parameters (FOV, far clip, zoom, etc.) to revert to the standard projection.
        Note that the custom projection is not serialized or replicated through the network.
     */
    void SetProjection(const Matrix4& projection);

    /// Return far clip distance. If a custom projection matrix is in use, is calculated from it instead of the value assigned with SetFarClip().
    /// @property
    float GetFarClip() const;

    /// Return near clip distance. If a custom projection matrix is in use, is calculated from it instead of the value assigned with SetNearClip().
    /// @property
    float GetNearClip() const;

    /// Return vertical field of view in degrees.
    /// @property
    float GetFov() const { return fov_; }

    /// Return orthographic mode size.
    /// @property
    float GetOrthoSize() const { return orthoSize_; }

    /// Return aspect ratio.
    /// @property
    float GetAspectRatio() const { return aspectRatio_; }

    /// Return zoom.
    /// @property
    float GetZoom() const { return zoom_; }

    /// Return LOD bias.
    /// @property
    float GetLodBias() const { return lodBias_; }

    /// Return view mask.
    /// @property
    unsigned GetViewMask() const { return viewMask_; }

    /// Return view override flags.
    /// @property
    ViewOverrideFlags GetViewOverrideFlags() const { return viewOverrideFlags_; }

    /// Return fill mode.
    /// @property
    FillMode GetFillMode() const { return fillMode_; }

    /// Return orthographic flag.
    /// @property
    bool IsOrthographic() const { return orthographic_; }

    /// Return auto aspect ratio flag.
    /// @property
    bool GetAutoAspectRatio() const { return autoAspectRatio_; }

    /// Return frustum in world space.
    /// @property
    const Frustum& GetFrustum() const;
    /// Return projection matrix. It's in D3D convention with depth range 0 - 1.
    /// @property
    Matrix4 GetProjection() const;
    /// Return projection matrix converted to API-specific format for use as a shader parameter.
    /// @property
    Matrix4 GetGPUProjection() const;
    /// Return view matrix.
    /// @property
    const Matrix3x4& GetView() const;
    /// Return frustum near and far sizes.
    void GetFrustumSize(Vector3& near, Vector3& far) const;
    /// Return half view size.
    /// @property
    float GetHalfViewSize() const;
    /// Return frustum split by custom near and far clip distances.
    Frustum GetSplitFrustum(float nearClip, float farClip) const;
    /// Return frustum in view space.
    /// @property
    Frustum GetViewSpaceFrustum() const;
    /// Return split frustum in view space.
    Frustum GetViewSpaceSplitFrustum(float nearClip, float farClip) const;
    /// Return ray corresponding to normalized screen coordinates (0 - 1), with origin on the near clip plane.
    Ray GetScreenRay(float x, float y) const;
    /// Convert a world space point to normalized screen coordinates (0 - 1).
    Vector2 WorldToScreenPoint(const Vector3& worldPos) const;
    /// Convert normalized screen coordinates (0 - 1) and distance along view Z axis (in Z coordinate) to a world space point. The distance can not be closer than the near clip plane.
    /** Note that a HitDistance() from the camera screen ray is not the same as distance along the view Z axis, as under a perspective projection the ray is likely to not be Z-aligned.
     */
    Vector3 ScreenToWorldPoint(const Vector3& screenPos) const;

    /// Return projection offset.
    /// @property
    const Vector2& GetProjectionOffset() const { return projectionOffset_; }

    /// Return whether is using reflection.
    /// @property
    bool GetUseReflection() const { return useReflection_; }

    /// Return the reflection plane.
    /// @property
    const Plane& GetReflectionPlane() const { return reflectionPlane_; }

    /// Return whether is using a custom clipping plane.
    /// @property
    bool GetUseClipping() const { return useClipping_; }

    /// Return the custom clipping plane.
    /// @property
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
    Quaternion GetFaceCameraRotation(const Vector3& position, const Quaternion& rotation, FaceCameraMode mode, float minAngle = 0.0f);
    /// Get effective world transform for matrix and frustum calculations including reflection but excluding node scaling.
    /// @property
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
    void OnNodeSet(Node* node) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;

private:
    /// Recalculate projection matrix.
    void UpdateProjection() const;

    /// Cached view matrix.
    mutable Matrix3x4 view_;
    /// Cached projection matrix.
    mutable Matrix4 projection_;
    /// Cached world space frustum.
    mutable Frustum frustum_;
    /// View matrix dirty flag.
    mutable bool viewDirty_;
    /// Projection matrix dirty flag.
    mutable bool projectionDirty_;
    /// Frustum dirty flag.
    mutable bool frustumDirty_;
    /// Orthographic mode flag.
    bool orthographic_;
    /// Cached actual near clip distance.
    mutable float projNearClip_{};
    /// Cached actual far clip distance.
    mutable float projFarClip_{};
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
    ViewOverrideFlags viewOverrideFlags_;
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
    /// Use custom projection matrix flag. Used internally.
    mutable bool customProjection_;
};

}
