// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Math.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Math(asIScriptEngine* engine)
{
}

// ========================================================================================

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Math(asIScriptEngine* engine)
{
    // template <class T, typename std::enable_if...> inline T Mod(T x, T y) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Mod(float, float)", AS_FUNCTION(Mod<float>), AS_CALL_CDECL);
}

}
