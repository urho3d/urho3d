//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

namespace Urho3D
{

void ASRegisterManualFirst_Addons(asIScriptEngine* engine);
void ASRegisterManualLast_Addons(asIScriptEngine* engine);

void ASRegisterManualFirst_Graphics(asIScriptEngine* engine);
void ASRegisterManualLast_Graphics(asIScriptEngine* engine);

void ASRegisterManualFirst_Core(asIScriptEngine* engine);
void ASRegisterManualLast_Core(asIScriptEngine* engine);

void ASRegisterManualFirst_Math(asIScriptEngine* engine);
void ASRegisterManualLast_Math(asIScriptEngine* engine);

void ASRegisterManualFirst_IO(asIScriptEngine* engine);
void ASRegisterManualLast_IO(asIScriptEngine* engine);

void ASRegisterManualFirst_Scene(asIScriptEngine* engine);
void ASRegisterManualLast_Scene(asIScriptEngine* engine);

void ASRegisterManualFirst_UI(asIScriptEngine* engine);
void ASRegisterManualLast_UI(asIScriptEngine* engine);

void ASRegisterManualFirst_Input(asIScriptEngine* engine);
void ASRegisterManualLast_Input(asIScriptEngine* engine);

void ASRegisterManualFirst_Engine(asIScriptEngine* engine);
void ASRegisterManualLast_Engine(asIScriptEngine* engine);

void ASRegisterManualFirst_Audio(asIScriptEngine* engine);
void ASRegisterManualLast_Audio(asIScriptEngine* engine);

void ASRegisterManualFirst_Container(asIScriptEngine* engine);
void ASRegisterManualLast_Container(asIScriptEngine* engine);

void ASRegisterManualFirst_Resource(asIScriptEngine* engine);
void ASRegisterManualLast_Resource(asIScriptEngine* engine);

#ifdef URHO3D_PHYSICS
void ASRegisterManualFirst_Physics(asIScriptEngine* engine);
void ASRegisterManualLast_Physics(asIScriptEngine* engine);
#endif

#ifdef URHO3D_NETWORK
void ASRegisterManualFirst_Network(asIScriptEngine* engine);
void ASRegisterManualLast_Network(asIScriptEngine* engine);
#endif

#ifdef URHO3D_IK
void ASRegisterManualFirst_IK(asIScriptEngine* engine);
void ASRegisterManualLast_IK(asIScriptEngine* engine);
#endif

#ifdef URHO3D_DATABASE
void ASRegisterManualFirst_Database(asIScriptEngine* engine);
void ASRegisterManualLast_Database(asIScriptEngine* engine);
#endif

#ifdef URHO3D_URHO2D
void ASRegisterManualFirst_Urho2D(asIScriptEngine* engine);
void ASRegisterManualLast_Urho2D(asIScriptEngine* engine);
#endif


// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst(asIScriptEngine* engine)
{
    if (sizeof(long) == 4)
    {
        engine->RegisterTypedef("long", "int");
        engine->RegisterTypedef("ulong", "uint");
    }
    else
    {
        engine->RegisterTypedef("long", "int64");
        engine->RegisterTypedef("ulong", "uint64");
    }

    if (sizeof(size_t) == 4)
        engine->RegisterTypedef("size_t", "uint");
    else
        engine->RegisterTypedef("size_t", "uint64");

    engine->RegisterTypedef("SDL_JoystickID", "int");

    ASRegisterManualFirst_Addons(engine);
    ASRegisterManualFirst_Graphics(engine);
    ASRegisterManualFirst_Core(engine);
    ASRegisterManualFirst_Math(engine);
    ASRegisterManualFirst_IO(engine);
    ASRegisterManualFirst_Scene(engine);
    ASRegisterManualFirst_UI(engine);
    ASRegisterManualFirst_Input(engine);
    ASRegisterManualFirst_Engine(engine);
    ASRegisterManualFirst_Audio(engine);
    ASRegisterManualFirst_Container(engine);
    ASRegisterManualFirst_Resource(engine);

#ifdef URHO3D_PHYSICS
    ASRegisterManualFirst_Physics(engine);
#endif

#ifdef URHO3D_NETWORK
    ASRegisterManualFirst_Network(engine);
#endif

#ifdef URHO3D_IK
    ASRegisterManualFirst_IK(engine);
#endif

#ifdef URHO3D_DATABASE
    ASRegisterManualFirst_Database(engine);
#endif

#ifdef URHO3D_URHO2D
    ASRegisterManualFirst_Urho2D(engine);
#endif
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast(asIScriptEngine* engine)
{
    ASRegisterManualLast_Addons(engine);
    ASRegisterManualLast_Graphics(engine);
    ASRegisterManualLast_Core(engine);
    ASRegisterManualLast_Math(engine);
    ASRegisterManualLast_IO(engine);
    ASRegisterManualLast_Scene(engine);
    ASRegisterManualLast_UI(engine);
    ASRegisterManualLast_Input(engine);
    ASRegisterManualLast_Engine(engine);
    ASRegisterManualLast_Audio(engine);
    ASRegisterManualLast_Container(engine);
    ASRegisterManualLast_Resource(engine);

#ifdef URHO3D_PHYSICS
    ASRegisterManualLast_Physics(engine);
#endif

#ifdef URHO3D_NETWORK
    ASRegisterManualLast_Network(engine);
#endif

#ifdef URHO3D_IK
    ASRegisterManualLast_IK(engine);
#endif

#ifdef URHO3D_DATABASE
    ASRegisterManualLast_Database(engine);
#endif

#ifdef URHO3D_URHO2D
    ASRegisterManualLast_Urho2D(engine);
#endif
}

} // namespace Urho3D
