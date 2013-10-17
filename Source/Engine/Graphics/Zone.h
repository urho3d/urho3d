//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Color.h"
#include "Drawable.h"

namespace Urho3D
{

/// %Component that describes global rendering properties
class URHO3D_API Zone : public Drawable
{
    OBJECT(Zone);
    
public:
    /// Construct.
    Zone(Context* context);
    /// Destruct.
    virtual ~Zone();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
    /// Set local-space bounding box. Will be used as an oriented bounding box to test whether objects or the camera are inside.
    void SetBoundingBox(const BoundingBox& box);
    /// Set ambient color
    void SetAmbientColor(const Color& color);
    /// Set fog color.
    void SetFogColor(const Color& color);
    /// Set fog start distance.
    void SetFogStart(float start);
    /// Set fog end distance.
    void SetFogEnd(float end);
    /// Set fog height distance.
    void SetFogHeight(float height);
    /// Set fog height scale.
    void SetFogHeightScale(float scale);
    /// Set zone priority. If an object or camera is inside several zones, the one with highest priority is used.
    void SetPriority(int priority);
    /// Set override mode. If camera is inside an override zone, it will also be used for all drawables.
    void SetOverride(bool enable);
    /// Set ambient gradient mode. In gradient mode ambient color is interpolated from neighbor zones.
    void SetAmbientGradient(bool enable);
    
    /// Return inverse world transform.
    const Matrix3x4& GetInverseWorldTransform() const;
    /// Return zone's own ambient color, disregarding gradient mode.
    const Color& GetAmbientColor() const { return ambientColor_; }
    /// Return ambient start color. Not safe to call from worker threads due to possible octree query.
    const Color& GetAmbientStartColor();
    /// Return ambient end color. Not safe to call from worker threads due to possible octree query.
    const Color& GetAmbientEndColor();
    /// Return fog color.
    const Color& GetFogColor() const { return fogColor_; }
    /// Return fog start distance.
    float GetFogStart() const { return fogStart_; }
    /// Return fog end distance.
    float GetFogEnd() const { return fogEnd_; }
    /// Return fog height distance.
    float GetFogHeight() const { return fogHeight_; }
    /// Return fog height scale.
    float GetFogHeightScale() const { return fogHeightScale_; }
    /// Return zone priority.
    int GetPriority() const { return priority_; }
    /// Return override mode.
    bool GetOverride() const { return override_; }
    /// Return whether ambient gradient mode is enabled.
    bool GetAmbientGradient() const { return ambientGradient_; }
    
    /// Check whether a point is inside.
    bool IsInside(const Vector3& point) const;
    
protected:
    /// Transform has changed. Clear cached zone of any contained drawables.
    virtual void OnMarkedDirty(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Recalculate the ambient gradient colors from neighbor zones. Not safe to call from worker threads due to octree query.
    void UpdateAmbientGradient();
    
    /// Cached inverse world transform matrix.
    mutable Matrix3x4 inverseWorld_;
    /// Inverse transform dirty flag.
    mutable bool inverseWorldDirty_;
    /// Override mode flag.
    bool override_;
    /// Ambient gradient mode flag.
    bool ambientGradient_;
    /// Last world-space bounding box.
    BoundingBox lastWorldBoundingBox_;
    /// Ambient color.
    Color ambientColor_;
    /// Cached ambient start color.
    Color ambientStartColor_;
    /// Cached ambient end color.
    Color ambientEndColor_;
    /// Fog color.
    Color fogColor_;
    /// Fog start distance.
    float fogStart_;
    /// Fog end distance.
    float fogEnd_;
    /// Fog height distance.
    float fogHeight_;
    /// Fog height cale.
    float fogHeightScale_;
    /// Zone priority.
    int priority_;
    /// Last zone used for ambient gradient start color.
    WeakPtr<Zone> lastAmbientStartZone_;
    /// Last zone used for ambient gradient end color.
    WeakPtr<Zone> lastAmbientEndZone_;
};

}
