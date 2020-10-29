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

#ifdef URHO3D_URHO2D

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Urho2D.h"

#include "../Scene/Scene.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Urho2D(asIScriptEngine* engine)
{
}

// ========================================================================================

// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
static PhysicsWorld2D* GetPhysicsWorld2D()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld2D>() : nullptr;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Urho2D(asIScriptEngine* engine)
{
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterGlobalFunction("PhysicsWorld2D@+ get_physicsWorld2D()", asFUNCTION(GetPhysicsWorld2D), asCALL_CDECL);
}

// ========================================================================================

// RigidBody2D* PhysicsRaycastResult2D::body_ | File: ../Urho2D/PhysicsWorld2D.h
RigidBody2D* PhysicsRaycastResultGetRigidBody2D(PhysicsRaycastResult2D* ptr)
{
    return ptr->body_;
}

// ========================================================================================

// void PhysicsWorld2D::Raycast(PODVector< PhysicsRaycastResult2D > &results, const Vector2 &startPoint, const Vector2 &endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
CScriptArray* PhysicsWorld2DRaycast(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PODVector<PhysicsRaycastResult2D> result;
    ptr->Raycast(result, startPoint, endPoint, collisionMask);
    return VectorToArray<PhysicsRaycastResult2D>(result, "Array<PhysicsRaycastResult2D>");
}

// void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D &result, const Vector2 &startPoint, const Vector2 &endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
PhysicsRaycastResult2D PhysicsWorld2DRaycastSingle(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PhysicsRaycastResult2D result;
    ptr->RaycastSingle(result, startPoint, endPoint, collisionMask);
    return result;
}

// void PhysicsWorld2D::GetRigidBodies(PODVector< RigidBody2D * > &results, const Rect &aabb, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
CScriptArray* PhysicsWorld2DGetRigidBodies(const Rect& aabb, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PODVector<RigidBody2D*> results;
    ptr->GetRigidBodies(results, aabb, collisionMask);
    return VectorToHandleArray<RigidBody2D>(results, "Array<RigidBody2D@>");
}

}

#endif // def URHO3D_URHO2D
