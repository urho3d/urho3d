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

#include "../Core/Object.h"

namespace Urho3D
{

/// Resource reloading started.
URHO3D_EVENT(E_RELOADSTARTED, ReloadStarted)
{
}

/// Resource reloading finished successfully.
URHO3D_EVENT(E_RELOADFINISHED, ReloadFinished)
{
}

/// Resource reloading failed.
URHO3D_EVENT(E_RELOADFAILED, ReloadFailed)
{
}

/// Tracked file changed in the resource directories.
URHO3D_EVENT(E_FILECHANGED, FileChanged)
{
    URHO3D_PARAM(P_FILENAME, FileName);                    // String
    URHO3D_PARAM(P_RESOURCENAME, ResourceName);            // String
}

/// Resource loading failed.
URHO3D_EVENT(E_LOADFAILED, LoadFailed)
{
    URHO3D_PARAM(P_RESOURCENAME, ResourceName);            // String
}

/// Resource not found.
URHO3D_EVENT(E_RESOURCENOTFOUND, ResourceNotFound)
{
    URHO3D_PARAM(P_RESOURCENAME, ResourceName);            // String
}

/// Unknown resource type.
URHO3D_EVENT(E_UNKNOWNRESOURCETYPE, UnknownResourceType)
{
    URHO3D_PARAM(P_RESOURCETYPE, ResourceType);            // StringHash
}

/// Resource background loading finished.
URHO3D_EVENT(E_RESOURCEBACKGROUNDLOADED, ResourceBackgroundLoaded)
{
    URHO3D_PARAM(P_RESOURCENAME, ResourceName);            // String
    URHO3D_PARAM(P_SUCCESS, Success);                      // bool
    URHO3D_PARAM(P_RESOURCE, Resource);                    // Resource pointer
}

/// Language changed.
URHO3D_EVENT(E_CHANGELANGUAGE, ChangeLanguage)
{
}

}
