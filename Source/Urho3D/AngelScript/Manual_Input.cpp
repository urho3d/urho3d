// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Input.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Input(asIScriptEngine* engine)
{
}

// ========================================================================================

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Input* GetInput()
{
    return GetScriptContext()->GetSubsystem<Input>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Input(asIScriptEngine* engine)
{
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Input@+ get_input()", AS_FUNCTION(GetInput), AS_CALL_CDECL);
}

}
