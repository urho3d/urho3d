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

#include "../Math/Matrix3x4.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

/// %UI element which allows sub-pixel positioning and size, as well as rotation. Only other Sprites should be added as child elements.
class URHO3D_API Sprite : public UIElement
{
    OBJECT(Sprite);

public:
    /// Construct.
    Sprite(Context* context);
    /// Destruct.
    virtual ~Sprite();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Return whether is visible and inside a scissor rectangle and should be rendered.
    virtual bool IsWithinScissor(const IntRect& currentScissor);
    /// Update and return screen position.
    virtual const IntVector2& GetScreenPosition() const;
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    /// React to position change.
    virtual void OnPositionSet();

    /// Set floating point position.
    void SetPosition(const Vector2& position);
    /// Set floating point position.
    void SetPosition(float x, float y);
    /// Set hotspot for positioning and rotation.
    void SetHotSpot(const IntVector2& hotSpot);
    /// Set hotspot for positioning and rotation.
    void SetHotSpot(int x, int y);
    /// Set scale. Scale also affects child sprites.
    void SetScale(const Vector2& scale);
    /// Set scale. Scale also affects child sprites.
    void SetScale(float x, float y);
    /// Set uniform scale. Scale also affects child sprites.
    void SetScale(float scale);
    /// Set rotation angle.
    void SetRotation(float angle);
    /// Set texture.
    void SetTexture(Texture* texture);
    /// Set part of texture to use as the image.
    void SetImageRect(const IntRect& rect);
    /// Use whole texture as the image.
    void SetFullImageRect();
    /// Set blend mode.
    void SetBlendMode(BlendMode mode);

    /// Return floating point position.
    const Vector2& GetPosition() const { return floatPosition_; }
    /// Return hotspot.
    const IntVector2& GetHotSpot() const { return hotSpot_; }
    /// Return scale.
    const Vector2& GetScale() const { return scale_; }
    /// Return rotation angle.
    float GetRotation() const { return rotation_; }
    /// Return texture.
    Texture* GetTexture() const { return texture_; }
    /// Return image rectangle.
    const IntRect& GetImageRect() const { return imageRect_; }
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Set texture attribute.
    void SetTextureAttr(const ResourceRef& value);
    /// Return texture attribute.
    ResourceRef GetTextureAttr() const;
    /// Update and return rendering transform, also used to transform child sprites.
    const Matrix3x4& GetTransform() const;

protected:
    /// Floating point position.
    Vector2 floatPosition_;
    /// Hotspot for positioning and rotation.
    IntVector2 hotSpot_;
    /// Scale.
    Vector2 scale_;
    /// Rotation angle.
    float rotation_;
    /// Texture.
    SharedPtr<Texture> texture_;
    /// Image rectangle.
    IntRect imageRect_;
    /// Blend mode flag.
    BlendMode blendMode_;
    /// Transform matrix.
    mutable Matrix3x4 transform_;
};

}
