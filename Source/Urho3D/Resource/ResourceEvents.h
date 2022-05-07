// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
