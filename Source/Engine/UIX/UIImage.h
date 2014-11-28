//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Drawable2D.h"

namespace Urho3D
{

class Sprite2D;
class UIRect;

/// UI image draw mode.
enum UIImageDrawMode
{
    UIIDM_SIMPLE = 0,
    UIIDM_TILED,
    UIIDM_SLICED,
};

/// UI drawable component.
class URHO3D_API UIImage : public Drawable2D
{
    OBJECT(UIImage);

public:
    /// Construct.
    UIImage(Context* scontext);
    /// Destruct.
    virtual ~UIImage();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set sprite.
    void SetSprite(Sprite2D* sprite);
    /// Set color.
    void SetColor(const Color& color);
    /// Set draw mode.
    void SetDrawMode(UIImageDrawMode mode);
    /// Set X slice size.
    void SetXSliceSize(int size);
    /// Set Y slice size.
    void SetYSliceSize(int size);

    /// Return sprite.
    Sprite2D* GetSprite() const;
    /// Return color.
    const Color& GetColor() const { return color_; }
    /// Return draw mode.
    UIImageDrawMode GetDrawMode() const { return drawMode_; }
    /// Return X slice size.
    int GetXSliceSize() const { return xSliceSize_;}
    /// Return Y slice size.
    int GetYSliceSize() const { return ySliceSize_;}

    /// Set sprite attribute.
    void SetSpriteAttr(const ResourceRef& value);
    /// Return sprite attribute.
    ResourceRef GetSpriteAttr() const;

private:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Update vertices.
    virtual void UpdateVertices();
    /// Update vertices simple mode.
    void UpdateVerticesSimpleMode();
    /// Update vertices tiled mode.
    void UpdateVerticesTiledMode();
    /// Update vertices sliced mode.
    void UpdateVerticesSlicedMode();
    /// Return sprite texture coords.
    void GetSpriteTextureCoords(float& left, float& right, float& top, float& bottom) const;
    /// Add quad.
    void AddQuad(float left, float right, float top, float bottom, float uLeft, float uRight, float vTop, float vBottom);
    /// handle rect changed.
    void HandleRectDirtied(StringHash eventType, VariantMap& eventData);

    /// UIRect
    WeakPtr<UIRect> uiRect_;
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Color.
    Color color_;
    /// Draw mode.
    UIImageDrawMode drawMode_;
    /// X slice size.
    int xSliceSize_;
    /// Y slice size.
    int ySliceSize_;
};

}
