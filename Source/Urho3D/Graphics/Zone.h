//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "../Graphics/Drawable.h"
#include "../GraphicsAPI/Texture.h"
#include "../Math/Color.h"

namespace Urho3D
{

/// %Component that describes global rendering properties.
class URHO3D_API Zone : public Drawable
{
    URHO3D_OBJECT(Zone, Drawable);

public:
    /// Construct.
    explicit Zone(Context* context);
    /// Destruct.
    ~Zone() override;
    /// Register object factory. Drawable must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set local-space bounding box. Will be used as an oriented bounding box to test whether objects or the camera are inside.
    /// @property
    void SetBoundingBox(const BoundingBox& box);
    /// Set ambient color.
    /// @property
    void SetAmbientColor(const Color& color);
    /// Set fog color.
    /// @property
    void SetFogColor(const Color& color);
    /// Set fog start distance.
    /// @property
    void SetFogStart(float start);
    /// Set fog end distance.
    /// @property
    void SetFogEnd(float end);
    /// Set fog height distance relative to the scene node's world position. Effective only in height fog mode.
    /// @property
    void SetFogHeight(float height);
    /// Set fog height scale. Effective only in height fog mode.
    /// @property
    void SetFogHeightScale(float scale);
    /// Set zone priority. If an object or camera is inside several zones, the one with highest priority is used.
    /// @property
    void SetPriority(int priority);
    /// Set height fog mode.
    /// @property
    void SetHeightFog(bool enable);
    /// Set override mode. If camera is inside an override zone, that zone will be used for all rendered objects instead of their own zone.
    /// @property
    void SetOverride(bool enable);
    /// Set ambient gradient mode. In gradient mode ambient color is interpolated from neighbor zones.
    /// @property
    void SetAmbientGradient(bool enable);
    /// Set zone texture. This will be bound to the zone texture unit when rendering objects inside the zone. Note that the default shaders do not use it.
    /// @property
    void SetZoneTexture(Texture* texture);

    /// Return inverse world transform.
    /// @property
    const Matrix3x4& GetInverseWorldTransform() const;

    /// Return zone's own ambient color, disregarding gradient mode.
    /// @property
    const Color& GetAmbientColor() const { return ambientColor_; }

    /// Return ambient start color. Not safe to call from worker threads due to possible octree query.
    /// @property
    const Color& GetAmbientStartColor();
    /// Return ambient end color. Not safe to call from worker threads due to possible octree query.
    /// @property
    const Color& GetAmbientEndColor();

    /// Return fog color.
    /// @property
    const Color& GetFogColor() const { return fogColor_; }

    /// Return fog start distance.
    /// @property
    float GetFogStart() const { return fogStart_; }

    /// Return fog end distance.
    /// @property
    float GetFogEnd() const { return fogEnd_; }

    /// Return fog height distance relative to the scene node's world position.
    /// @property
    float GetFogHeight() const { return fogHeight_; }

    /// Return fog height scale.
    /// @property
    float GetFogHeightScale() const { return fogHeightScale_; }

    /// Return zone priority.
    /// @property
    int GetPriority() const { return priority_; }

    /// Return whether height fog mode is enabled.
    /// @property
    bool GetHeightFog() const { return heightFog_; }

    /// Return whether override mode is enabled.
    /// @property
    bool GetOverride() const { return override_; }

    /// Return whether ambient gradient mode is enabled.
    /// @property
    bool GetAmbientGradient() const { return ambientGradient_; }

    /// Return zone texture.
    /// @property
    Texture* GetZoneTexture() const { return zoneTexture_; }

    /// Check whether a point is inside.
    bool IsInside(const Vector3& point) const;
    /// Set zone texture attribute.
    void SetZoneTextureAttr(const ResourceRef& value);
    /// Return zone texture attribute.
    ResourceRef GetZoneTextureAttr() const;

protected:
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Handle removal from octree.
    void OnRemoveFromOctree() override;
    /// Recalculate the ambient gradient colors from neighbor zones. Not safe to call from worker threads due to octree query.
    void UpdateAmbientGradient();
    /// Clear zone reference from drawables inside the bounding box.
    void ClearDrawablesZone();
    /// Mark node transform dirty.
    void MarkNodeDirty() { OnMarkedDirty(node_); }

    /// Cached inverse world transform matrix.
    mutable Matrix3x4 inverseWorld_;
    /// Inverse transform dirty flag.
    mutable bool inverseWorldDirty_;
    /// Height fog mode flag.
    bool heightFog_;
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
    /// Zone texture.
    SharedPtr<Texture> zoneTexture_;
    /// Last zone used for ambient gradient start color.
    WeakPtr<Zone> lastAmbientStartZone_;
    /// Last zone used for ambient gradient end color.
    WeakPtr<Zone> lastAmbientEndZone_;
};

}
