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

#include "../Graphics/GraphicsDefs.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

/// Tooltip %UI element.
class URHO3D_API ToolTip : public UIElement
{
    OBJECT(ToolTip)

public:
    /// Construct.
    ToolTip(Context* context);
    /// Destruct.
    virtual ~ToolTip();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Perform UI element update.
    virtual void Update(float timeStep);

    /// Set the delay in seconds until the tooltip shows once hovering. Set zero to use the default from the UI subsystem.
    void SetDelay(float delay);

    /// Return the delay in seconds until the tooltip shows once hovering.
    float GetDelay() const { return delay_; }

private:
    /// The element that is being tracked for hovering. Normally the parent element.
    WeakPtr<UIElement> target_;
    /// Delay from hover start to displaying the tooltip.
    float delay_;
    /// Point at which the parent was hovered.
    bool parentHovered_;
    /// Point at which the tooltip was set visible.
    Timer displayAt_;
    /// Original offset position to the parent.
    IntVector2 originalPosition_;
};

}