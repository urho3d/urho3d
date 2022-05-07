// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

class asIScriptEngine;

namespace Urho3D
{

class Context;

/// Register the Core library to script.
void RegisterCoreAPI(asIScriptEngine* engine);
/// Register the Scene library to script.
void RegisterSceneAPI(asIScriptEngine* engine);
/// Register the Script interfaces to script.
void RegisterScriptInterfaceAPI(asIScriptEngine* engine);
/// Register the Script library to script.
void RegisterScriptAPI(asIScriptEngine* engine);

}
