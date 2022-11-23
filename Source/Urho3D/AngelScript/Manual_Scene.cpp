// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Scene.h"

#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif

#ifdef URHO3D_PHYSICS2D
#include "../Physics2D/PhysicsWorld2D.h"
#endif

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Scene(asIScriptEngine* engine)
{
}

// ========================================================================================

#ifdef URHO3D_PHYSICS
// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
static PhysicsWorld* SceneGetPhysicsWorld(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld>();
}
#endif

#ifdef URHO3D_PHYSICS2D
// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
static PhysicsWorld2D* SceneGetPhysicsWorld2D(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld2D>();
}
#endif

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Scene(asIScriptEngine* engine)
{
#ifdef URHO3D_PHYSICS
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "PhysicsWorld@+ get_physicsWorld() const", AS_FUNCTION_OBJLAST(SceneGetPhysicsWorld), AS_CALL_CDECL_OBJLAST);
#endif

#ifdef URHO3D_PHYSICS2D
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "PhysicsWorld2D@+ get_physicsWorld2D() const", AS_FUNCTION_OBJLAST(SceneGetPhysicsWorld2D), AS_CALL_CDECL_OBJLAST);
#endif
}

}
