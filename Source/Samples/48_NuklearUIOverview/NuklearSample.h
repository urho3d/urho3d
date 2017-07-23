//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include "../Precompiled.h"
#include "Sample.h"

#include "../NuklearUI/NuklearUI.h"

class NuklearSample : public Sample
{
    URHO3D_OBJECT(NuklearSample, Sample);

public:
    /// Construct.
    NuklearSample(Context* context);

    virtual void Start();

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    virtual String GetScreenJoystickPatchString() const
    {
        return "<patch>"
               "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
               "        <attribute name=\"Is Visible\" value=\"false\" />"
               "    </add>"
               "</patch>";
    }

private:
    void LoadImages();
    /// Construct a new Text instance, containing the 'Hello World' String, and add it to the UI root element.
    void CreateText();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    int overview(Nuklear::nk_context* ctx);
    /// Nuklear context.
    NuklearUI* Nuklear;
    struct Nuklear::nk_image logo;
};

// https://stackoverflow.com/questions/1500363/compile-time-sizeof-array-without-using-a-macro
template < typename T, size_t N >
char (&_ArraySizeHelper(T (&array)[N]))[N];
#define LEN(array) (sizeof(_ArraySizeHelper(array)))

// https://stackoverflow.com/questions/3437404/min-and-max-in-c
template < class T >
T MAX(T const& a, T const& b)
{
    return a > b ? a : b;
}