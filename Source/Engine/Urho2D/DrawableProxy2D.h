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

#include "Drawable.h"

namespace Urho3D
{

class Texture2D;
class Drawable2D;

/// 2D drawable proxy components.
class URHO3D_API DrawableProxy2D : public Component
{
    OBJECT(DrawableProxy2D);

public:
    /// Construct.
    DrawableProxy2D(Context* context);
    /// Destruct.
    ~DrawableProxy2D();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);

    /// Add drawable.
    void AddDrawable(Drawable2D* drawable);
    /// Remove drawable.
    void RemoveDrawable(Drawable2D* drawable);
    /// Return material.
    Material* GetMaterial(Drawable2D* drawable);

protected:
    /// Create material by texture and blend mode.
    Material* CreateMaterial(Texture2D* Texture, BlendMode blendMode) const;

    /// Drawables.
    Vector<WeakPtr<Drawable2D> > drawables_;
    /// Materials.
    HashMap<Texture2D*, HashMap<int, SharedPtr<Material> > > materials_;
};

}
