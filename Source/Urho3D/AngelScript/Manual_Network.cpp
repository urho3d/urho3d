// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#ifdef URHO3D_NETWORK

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Network.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Network(asIScriptEngine* engine)
{
}

// ========================================================================================

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Network* GetNetwork()
{
    return GetScriptContext()->GetSubsystem<Network>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Network(asIScriptEngine* engine)
{
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Network@+ get_network()", AS_FUNCTION(GetNetwork), AS_CALL_CDECL);
}

} // namespace Urho3D

#endif // def URHO3D_NETWORK
