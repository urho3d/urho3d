//
// Copyright (c) 2008-2019 the Urho3D project.
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

/// \file

#pragma once

#ifdef __ANDROID__
#include "../Resource/JSONFile.h"

namespace Urho3D
{
    // Commands sended to Android as JSON object. It must have attribute "method",
    // with name of called method. Main activity receive that object in main
    // UI thread and invoke method, send object as argument.
    // For answer method in activity or for notify for some Android events also
    // using JSON object, which posted as string in notification to game's main SDL thread.
    // When object received in main game thread, it sended as "data" in
    // AndroidNotify event whith Input subsytem as sender.
    // JSON object in notification has attribute "source" whith arbitrary name
    // of source of event, and "event" whith name of event.
    void PostCommandToPlatform(const JSONFile& data);

}
#endif
