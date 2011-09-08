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
    
    /// %Set bounding box. Will be used as an oriented bounding box to test whether the camera is inside.
    void SetBoundingBox(const BoundingBox& box);
    /// %Set ambient color.
    void SetAmbientColor(const Color& color);
    /// %Set fog color.
    void SetFogColor(const Color& color);
    /// %Set fog start distance.
    void SetFogStart(float start);
    /// %Set fog end distance.
    void SetFogEnd(float end);
    /// %Set zone priority. If camera is inside several zones, the one with highest priority is used.
    void SetPriority(int priority);
    
    /// Return bounding box.
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }
    /// Return ambient color.
    const Color& GetAmbientColor() const { return ambientColor_; }
    /// Return fog color.
    const Color& GetFogColor() const { return fogColor_; }
    /// Return fog start distance.
    float GetFogStart() const { return fogStart_; }
    /// Return fog end distance.
    float GetFogEnd() const { return fogEnd_; }
    /// Return zone priority.
    int GetPriority() const { return priority_; }
    
    /// Check whether a point is inside.
    virtual bool IsInside(const Vector3& point);
    
protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
    /// Bounding box.
    BoundingBox boundingBox_;
    /// Ambient color.
    Color ambientColor_;
    /// Fog color.
    Color fogColor_;
    /// Fog start distance.
    float fogStart_;
    /// Fog end distance.
    float fogEnd_;
    /// Zone priority.
    int priority_;
};
