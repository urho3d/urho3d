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

/// Static sprite component.
class URHO3D_API StaticSprite2D : public Drawable2D
{
    OBJECT(StaticSprite2D);

public:
    /// Construct.
    StaticSprite2D(Context* context);
    /// Destruct.
    ~StaticSprite2D();
    /// Register object factory. Drawable2D must be registered first.
    static void RegisterObject(Context* context);

    /// Set flip.
    void SetFlip(bool flipX, bool flipY);
    /// Set flip X.
    void SetFlipX(bool flipX);
    /// Set flip Y.
    void SetFlipY(bool flipY);
    /// Set color.
    void SetColor(const Color& color);

    /// Return flip X.
    bool GetFlipX() const { return flipX_; }
    /// Return flip Y.
    bool GetFlipY() const { return flipY_; }
    /// Return color.
    const Color& GetColor() const { return color_; }

protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Update vertices.
    virtual void UpdateVertices();

    /// Flip X.
    bool flipX_;
    /// Flip Y.
    bool flipY_;
    /// Color.
    Color color_;
};

}
