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
enum UIDrawMode
{
    UIDM_SIMPLE = 0,
    UIDM_TILED,
    UIDM_SLICED,
    UIDM_FILLED,
};

/// UI image fill type.
enum UIFillType
{
    UIFT_HORIZONTAL = 0,
    UIFT_VERTICAL,
    UIFT_RADIAL,
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
    void SetDrawMode(UIDrawMode mode);
    /// Set horizontal slice size (for sliced mode).
    void SetHorizontalSliceSize(int size);
    /// Set vertical slice size (for sliced mode).
    void SetVerticalSliceSize(int size);
    /// Set fill type (for fill mode).
    void SetFillType(UIFillType fillType);
    /// Set fill amount (for fill mode).
    void SetFillAmount(float amount);
    /// Set Fill inverse (for fill mode).
    void SetFillInverse(bool inverse);

    /// Return sprite.
    Sprite2D* GetSprite() const;
    /// Return color.
    const Color& GetColor() const { return color_; }
    /// Return draw mode.
    UIDrawMode GetDrawMode() const { return drawMode_; }
    /// Return horizontal slice size (for sliced mode).
    int GetHorizontalSliceSize() const { return horizontalSliceSize_;}
    /// Return vertical slice size (for sliced mode).
    int GetVerticalSliceSize() const { return verticalSliceSize_;}
    /// Return fill type (for filled mode).
    UIFillType GetFillType() const { return fillType_; }
    /// Return fill amount (for fill mode).
    float GetFillAmount() const { return fillAmount_; }
    /// Return is fill inverse (for fill mode).
    bool IsFillInverse() const { return fillInverse_; }

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
    /// Update vertices filled mode.
    void UpdateVerticesFilledMode();
    /// Update vertices filled mode radial.
    void UpdateVerticesFilledModeRadial();
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
    UIDrawMode drawMode_;
    /// X slice size.
    int horizontalSliceSize_;
    /// Y slice size.
    int verticalSliceSize_;
    /// Fill type.
    UIFillType fillType_;
    /// Fill amount.
    float fillAmount_;
    /// Fill inverse.
    bool fillInverse_;
};

}
