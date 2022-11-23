// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#ifdef URHO3D_PHYSICS

#include "../AngelScript/Manual_Physics.h"

#include "../Scene/Scene.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Physics(asIScriptEngine* engine)
{
}

// ========================================================================================

// template <class T> T* Node::GetComponent(bool recursive = false) const | File: ../Scene/Node.h
static PhysicsWorld* GetPhysicsWorld()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld>() : nullptr;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Physics(asIScriptEngine* engine)
{
    // template <class T> T* Node::GetComponent(bool recursive = false) const | File: ../Scene/Node.h
    engine->RegisterGlobalFunction("PhysicsWorld@+ get_physicsWorld()", AS_FUNCTION(GetPhysicsWorld), AS_CALL_CDECL);
}

}

#endif // def URHO3D_PHYSICS
