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
#include "Cursor.h"
#include "ResourceCache.h"
#include "Texture.h"

#include "DebugNew.h"

Cursor::Cursor(const std::string& name) :
    BorderImage(name),
    mHotspot(IntVector2::sZero)
{
    // Show on top of all other UI elements
    mPriority = M_MAX_INT;
}

Cursor::~Cursor()
{
}

void Cursor::setStyle(const XMLElement& element, ResourceCache* cache)
{
    if (!cache)
        EXCEPTION("Null resource cache for UI element");
    
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("hotspot"))
        setHotspot(element.getChildElement("hotspot").getIntVector2("value"));
}

IntVector2 Cursor::getScreenPosition()
{
    IntVector2 pos = UIElement::getScreenPosition();
    pos -= mHotspot;
    return pos;
}

void Cursor::setHotspot(const IntVector2& hotspot)
{
    mHotspot = hotspot;
}

void Cursor::setHotspot(int x, int y)
{
    setHotspot(IntVector2(x, y));
}
