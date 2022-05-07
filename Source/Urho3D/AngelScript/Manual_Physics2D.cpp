// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#ifdef URHO3D_PHYSICS2D

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Physics2D.h"

#include "../Scene/Scene.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Physics2D(asIScriptEngine* engine)
{
}

// ========================================================================================

// template <class T> T* Node::GetComponent(bool recursive = false) const | File: ../Scene/Node.h
static PhysicsWorld2D* GetPhysicsWorld2D()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld2D>() : nullptr;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Physics2D(asIScriptEngine* engine)
{
    // template <class T> T* Node::GetComponent(bool recursive = false) const | File: ../Scene/Node.h
    engine->RegisterGlobalFunction("PhysicsWorld2D@+ get_physicsWorld2D()", AS_FUNCTION(GetPhysicsWorld2D), AS_CALL_CDECL);
}

}

#endif // def URHO3D_PHYSICS2D
