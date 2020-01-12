//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Math/Color.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

class URHO3D_API UISelectable : public UIElement
{
public:
    URHO3D_OBJECT(UISelectable, UIElement);

    /// Construct.
    using UIElement::UIElement;
    /// Destruct.
    ~UISelectable() override = default;

    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

    /// Set selection background color. Color with 0 alpha (default) disables.
    void SetSelectionColor(const Color& color);
    /// Set hover background color. Color with 0 alpha (default) disables.
    void SetHoverColor(const Color& color);

    /// Return selection background color.
    const Color& GetSelectionColor() const { return selectionColor_; }
    /// Return hover background color.
    const Color& GetHoverColor() const { return hoverColor_; }

protected:
    /// Selection background color.
    Color selectionColor_{Color::TRANSPARENT_BLACK};
    /// Hover background color.
    Color hoverColor_{Color::TRANSPARENT_BLACK};
};

}
