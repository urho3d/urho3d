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

#include "Precompiled.h"
#include "CheckBox.h"
#include "InputEvents.h"
#include "UIEvents.h"

#include "DebugNew.h"

CheckBox::CheckBox(const std::string& name) :
    BorderImage(name),
    mUncheckedRect(IntRect::sZero),
    mCheckedRect(IntRect::sZero),
    mChecked(false)
{
    mEnabled = true;
}

CheckBox::~CheckBox()
{
}

void CheckBox::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("uncheckedrect"))
        setUncheckedRect(element.getChildElement("uncheckedrect").getIntRect("value"));
    if (element.hasChildElement("checkedrect"))
        setCheckedRect(element.getChildElement("checkedrect").getIntRect("value"));
}

void CheckBox::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    if (mChecked)
        mImageRect = mCheckedRect;
    else
        mImageRect = mUncheckedRect;
    
    BorderImage::getBatches(batches, quads, currentScissor);
}

void CheckBox::onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
    if (buttons & MOUSEB_LEFT)
    {
        mChecked = !mChecked;
        
        using namespace Toggled;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_STATE] = mChecked;
        sendEvent(EVENT_TOGGLED, eventData);
    }
}

void CheckBox::setChecked(bool enable)
{
    // Note: event is intentionally not sent when manually set
    mChecked = enable;
}

void CheckBox::setUncheckedRect(const IntRect& rect)
{
    mUncheckedRect = rect;
}

void CheckBox::setUncheckedRect(int left, int top, int right, int bottom)
{
    mUncheckedRect = IntRect(left, top, right, bottom);
}

void CheckBox::setCheckedRect(const IntRect& rect)
{
    mCheckedRect = rect;
}

void CheckBox::setCheckedRect(int left, int top, int right, int bottom)
{
    mCheckedRect = IntRect(left, top, right, bottom);
}
