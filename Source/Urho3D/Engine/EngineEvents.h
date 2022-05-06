// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// A command has been entered on the console.
URHO3D_EVENT(E_CONSOLECOMMAND, ConsoleCommand)
{
    URHO3D_PARAM(P_COMMAND, Command);              // String
    URHO3D_PARAM(P_ID, Id);                        // String
}

}
