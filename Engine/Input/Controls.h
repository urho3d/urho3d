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

#ifndef INPUT_CONTROLS_H
#define INPUT_CONTROLS_H

#include "Variant.h"

class Deserializer;
class Serializer;
class XMLElement;

//! Controls sent over network
struct Controls
{
    //! Construct with initial state
    Controls()
    {
        reset();
    }
    
    //! Reset to initial state
    void reset()
    {
        mButtons = 0;
        mYaw = 0.0f;
        mPitch = 0.0f;
        mExtraData.clear();
    }
    
    //! Set or release button(s)
    void set(unsigned buttons, bool down = true)
    {
        if (down)
            mButtons |= buttons;
        else
            mButtons &= ~buttons;
    }
    
    //! Check if a button is held down
    bool isDown(unsigned button) const
    {
        return (mButtons & button) != 0;
    }
    
    //! Check if a button was pressed on this frame. Requires previous frame's controls
    bool isPressed(unsigned button, const Controls& prevControls) const
    {
        return ((mButtons & button) != 0) && ((prevControls.mButtons & button) == 0);
    }
    
    //! Write to a stream
    void write(Serializer& dest) const;
    //! Read from a stream
    void read(Deserializer& source);
    //! Write to an XML element
    void writeXML(XMLElement& dest) const;
    //! Read from an XML element
    void readXML(const XMLElement& source);
    
    //! Button state
    unsigned mButtons;
    //! Mouse yaw
    float mYaw;
    //! Mouse pitch
    float mPitch;
    //! Extra control data
    VariantMap mExtraData;
};

#endif
