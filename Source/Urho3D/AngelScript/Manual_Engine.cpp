// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../Engine/Console.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Engine(asIScriptEngine* engine)
{
}

// ========================================================================================

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Console* GetConsole()
{
    return GetScriptContext()->GetSubsystem<Console>();
}

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static DebugHud* GetDebugHud()
{
    return GetScriptContext()->GetSubsystem<DebugHud>();
}

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Engine* GetEngine()
{
    return GetScriptContext()->GetSubsystem<Engine>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Engine(asIScriptEngine* engine)
{
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Console@+ get_console()", AS_FUNCTION(GetConsole), AS_CALL_CDECL);
    
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("DebugHud@+ get_debugHud()", AS_FUNCTION(GetDebugHud), AS_CALL_CDECL);
    
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Engine@+ get_engine()", AS_FUNCTION(GetEngine), AS_CALL_CDECL);
}

}
