// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Resource.h"

#include "../Resource/ResourceCache.h"
#include "../Resource/Localization.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Resource(asIScriptEngine* engine)
{
}

// ========================================================================================

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static ResourceCache* GetResourceCache()
{
    return GetScriptContext()->GetSubsystem<ResourceCache>();
}

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Localization* GetLocalization()
{
    return GetScriptContext()->GetSubsystem<Localization>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Resource(asIScriptEngine* engine)
{
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Localization@+ get_localization()", AS_FUNCTION(GetLocalization), AS_CALL_CDECL);
    
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("ResourceCache@+ get_resourceCache()", AS_FUNCTION(GetResourceCache), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("ResourceCache@+ get_cache()", AS_FUNCTION(GetResourceCache), AS_CALL_CDECL);
}

}
