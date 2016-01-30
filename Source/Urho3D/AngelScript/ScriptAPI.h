//
// Copyright (c) 2008-2016 the Urho3D project.
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

class asIScriptEngine;

namespace Urho3D
{

class Context;

/// Register the Math library to script.
void RegisterMathAPI(asIScriptEngine* engine);
/// Register the Core library to script.
void RegisterCoreAPI(asIScriptEngine* engine);
/// Register the IO library to script.
void RegisterIOAPI(asIScriptEngine* engine);
/// Register the Resource library to script.
void RegisterResourceAPI(asIScriptEngine* engine);
/// Register the Scene library to script.
void RegisterSceneAPI(asIScriptEngine* engine);
/// Register the Graphics library to script.
void RegisterGraphicsAPI(asIScriptEngine* engine);
/// Register the Input library to script.
void RegisterInputAPI(asIScriptEngine* engine);
/// Register the Audio library to script.
void RegisterAudioAPI(asIScriptEngine* engine);
/// Register the UI library to script.
void RegisterUIAPI(asIScriptEngine* engine);
#ifdef URHO3D_NETWORK
/// Register the Network library to script.
void RegisterNetworkAPI(asIScriptEngine* engine);
#endif
#ifdef URHO3D_DATABASE
/// Register the Database library to script.
void RegisterDatabaseAPI(asIScriptEngine* engine);
#endif
#ifdef URHO3D_PHYSICS
/// Register the Physics library to script.
void RegisterPhysicsAPI(asIScriptEngine* engine);
#endif
#ifdef URHO3D_NAVIGATION
/// Register the Navigation library to script.
void RegisterNavigationAPI(asIScriptEngine* engine);
#endif
#ifdef URHO3D_URHO2D
/// Register the Urho2D library to script.
void RegisterUrho2DAPI(asIScriptEngine* engine);
#endif
/// Register the Script interfaces to script.
void RegisterScriptInterfaceAPI(asIScriptEngine* engine);
/// Register the Script library to script.
void RegisterScriptAPI(asIScriptEngine* engine);
/// Register the Engine library to script.
void RegisterEngineAPI(asIScriptEngine* engine);

}
