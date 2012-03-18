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

#pragma once

#include "Frustum.h"
#include "Component.h"
#include "Node.h"
#include "Ray.h"

static const unsigned VO_NONE = 0x0;
static const unsigned VO_LOW_MATERIAL_QUALITY = 0x1;
static const unsigned VO_DISABLE_SHADOWS = 0x2;
static const unsigned VO_DISABLE_OCCLUSION = 0x4;

/// %Camera component.
class Camera : public Component
{
    OBJECT(Camera);
    
public:
    /// Construct.
    Camera(Context* context);
    /// Destruct.
    virtual ~Camera();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set near clip distance.
    void SetNearClip(float nearClip);
    /// %Set far clip distance.
    void SetFarClip(float farClip);
    /// %Set field of view.
    void SetFov(float fov);
    /// %Set orthographic mode view uniform size.
    void SetOrthoSize(float orthoSize);
    /// %Set orthographic mode view size.
    void SetOrthoSize(const Vector2& orthoSize);
    /// %Set aspect ratio.
    void SetAspectRatio(float aspectRatio);
    /// %Set zoom.
    void SetZoom(float zoom);
    /// %Set LOD bias.
    void SetLodBias(float bias);
    /// %Set view mask. Will be and'ed with object's view mask to see if the object should be rendered.
    void SetViewMask(unsigned mask);
    /// %Set view override flags.
    void SetViewOverrideFlags(unsigned flags);
    /// %Set orthographic mode enabled/disabled.
    void SetOrthographic(bool enable);
    /// %Set automatic aspect ratio based on viewport dimensions.
    void SetAutoAspectRatio(bool enable);
    /// %Set projection offset. It needs to be calculated as (offset in pixels) / (viewport dimensions.)
    void SetProjectionOffset(const Vector2& offset);
    /// %Set vertical flipping mode.
    void SetFlipVertical(bool enable);
    
    /// Return far clip distance.
    float GetFarClip() const { return farClip_; }
    /// Return near clip distance.
    float GetNearClip() const;
    /// Return field of view.
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
    /// Return orthographic flag.
    bool IsOrthographic() const { return orthographic_; }
    /// Return auto aspect ratio flag.
    bool GetAutoAspectRatio() const { return autoAspectRatio_; }
    /// Return frustum in world space.
    const Frustum& GetFrustum();
    /// Return projection matrix.
    const Matrix4& GetProjection();
    /// Return frustum near and far sizes.
    void GetFrustumSize(Vector3& near, Vector3& far) const;
    /// Return half view size.
    float GetHalfViewSize() const;
    /// Return frustum split by custom near and far clip distances.
    Frustum GetSplitFrustum(float nearClip, float farClip);
    /// Return frustum in view space.
    Frustum GetViewSpaceFrustum() const;
    /// Return split frustum in view space.
    Frustum GetViewSpaceSplitFrustum(float nearClip, float farClip) const;
    /// Return ray corresponding to screen coordinates (0.0 to 1.0.)
    Ray GetScreenRay(float x, float y);
    /// Return forward vector.
    Vector3 GetForwardVector();
    /// Return right vector.
    Vector3 GetRightVector();
    /// Return up vector.
    Vector3 GetUpVector();
    /// Return projection offset.
    const Vector2& GetProjectionOffset() const { return projectionOffset_; }
    /// Return vertical flipping mode.
    bool GetFlipVertical() const { return flipVertical_; }
    /// Return distance to position. In orthographic mode uses only Z coordinate.
    float GetDistance(const Vector3& worldPos);
    /// Return squared distance to position. In orthographic mode uses only Z coordinate.
    float GetDistanceSquared(const Vector3& worldPos);
    /// Return a scene node's LOD scaled distance.
    float GetLodDistance(float distance, float scale, float bias) const;
    /// Return if projection parameters are valid for rendering and raycasting.
    bool IsProjectionValid() const;
    
    /// Return inverse world transform, also known as the view matrix.
    Matrix3x4 GetInverseWorldTransform() const { return GetWorldTransform().Inverse(); }
    
protected:
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    
private:
    /// Cached frustum.
    Frustum frustum_;
    /// Cached projection matrix.
    Matrix4 projection_;
    /// Projection offset.
    Vector2 projectionOffset_;
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
    /// Orthographic mode flag.
    bool orthographic_;
    /// Auto aspect ratio flag.
    bool autoAspectRatio_;
    /// Flip vertical flag.
    bool flipVertical_;
    /// Frustum dirty flag.
    bool frustumDirty_;
    /// Projection matrix dirty flag.
    bool projectionDirty_;
};
