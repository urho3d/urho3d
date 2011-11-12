//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

/// %Component that describes global rendering properties
class Zone : public Drawable
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
    /// Add debug geometry to the debug renderer.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
    /// %Set bounding box. Will be used as an oriented bounding box to test whether the camera is inside.
    void SetBoundingBox(const BoundingBox& box);
    /// %Set ambient color, both start and end.
    void SetAmbientColor(const Color& color);
    /// %Set ambient start color at bounding box Z minimum.
    void SetAmbientStartColor(const Color& color);
    /// %Set ambient end color at bounding box Z maximum.
    void SetAmbientEndColor(const Color& color);
    /// %Set fog color.
    void SetFogColor(const Color& color);
    /// %Set fog start distance.
    void SetFogStart(float start);
    /// %Set fog end distance.
    void SetFogEnd(float end);
    /// %Set zone priority. If camera is inside several zones, the one with highest priority is used.
    void SetPriority(int priority);
    /// %Set override mode. If camera is inside an override zone, it will also be used for all drawables.
    void SetOverride(bool enable);
    
    /// Return bounding box.
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }
    /// Return ambient start color.
    const Color& GetAmbientStartColor() const { return ambientStartColor_; }
    /// Return ambient end color.
    const Color& GetAmbientEndColor() const { return ambientEndColor_; }
    /// Return fog color.
    const Color& GetFogColor() const { return fogColor_; }
    /// Return fog start distance.
    float GetFogStart() const { return fogStart_; }
    /// Return fog end distance.
    float GetFogEnd() const { return fogEnd_; }
    /// Return zone priority.
    int GetPriority() const { return priority_; }
    /// Return override mode.
    bool GetOverride() const { return override_; }
    
    /// Check whether a point is inside.
    virtual bool IsInside(const Vector3& point);
    
protected:
    /// Transform has changed. Clear cached zone of any contained drawables.
    virtual void OnMarkedDirty(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
    /// Bounding box.
    BoundingBox boundingBox_;
    /// Last bounding box.
    BoundingBox lastBoundingBox_;
    /// Ambient start color.
    Color ambientStartColor_;
    /// Ambient end start color.
    Color ambientEndColor_;
    /// Fog color.
    Color fogColor_;
    /// Fog start distance.
    float fogStart_;
    /// Fog end distance.
    float fogEnd_;
    /// Zone priority.
    int priority_;
    /// Override mode.
    bool override_;
};
