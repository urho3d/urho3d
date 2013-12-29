//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Precompiled.h"
#include "ToolTip.h"
#include "Context.h"
#include "Timer.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

Tooltip::Tooltip(Context* context) :
    UIElement(context),
    delay_(500.f),
    parentHovered_(false)
{
}

Tooltip::~Tooltip()
{
}

void Tooltip::RegisterObject(Context* context)
{
    context->RegisterFactory<Tooltip>(UI_CATEGORY);

    COPY_BASE_ATTRIBUTES(Tooltip, UIElement);
    ACCESSOR_ATTRIBUTE(Tooltip, VAR_FLOAT, "Delay", GetDelay, SetDelay, float, 0.5f, AM_FILE);
}

void Tooltip::Update(float timeStep)
{
    if (parent_->IsHovering())
    {
        if (!parentHovered_)
        {
            parentHovered_ = true;
            displayat_.Reset();
        }
        else if(displayat_.GetMSec(false) >= delay_)
        {
            visible_ = true;
            BringToFront();
        }
    }
    else
    {
        if (visible_)
            visible_ = false;

        parentHovered_ = false;
        displayat_.Reset();
    }
}

void Tooltip::SetDelay(float delay)
{
    delay_ = delay;
}

}