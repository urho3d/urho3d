//
// Copyright (c) 2008-2022 the Urho3D project.
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
