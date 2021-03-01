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

#include "../AngelScript/Manual_Scene.h"

#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif

#ifdef URHO3D_URHO2D
#include "../Urho2D/PhysicsWorld2D.h"
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

#ifdef URHO3D_URHO2D
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

#ifdef URHO3D_URHO2D
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "PhysicsWorld2D@+ get_physicsWorld2D() const", AS_FUNCTION_OBJLAST(SceneGetPhysicsWorld2D), AS_CALL_CDECL_OBJLAST);
#endif
}

}
