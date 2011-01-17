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

#ifndef UI_CURSOR_H
#define UI_CURSOR_H

#include "BorderImage.h"

//! An image with hotspot coordinates
class Cursor : public BorderImage
{
    DEFINE_TYPE(Cursor);
    
public:
    //! Construct with name
    Cursor(const std::string& name = std::string());
    //! Destruct
    virtual ~Cursor();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Return UI element screen position
    virtual IntVector2 getScreenPosition();
    
    //! Set hotspot coordinates
    void setHotspot(const IntVector2& hotspot);
    //! Set hotspot coordinates
    void setHotspot(int x, int y);
    
    //! Return hotspot coordinates
    const IntVector2& getHotspot() const { return mHotspot; }
    
protected:
    //! Hotspot coordinates
    IntVector2 mHotspot;
};

#endif // UI_CURSOR_H
