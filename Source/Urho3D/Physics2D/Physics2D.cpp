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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Physics2D/CollisionBox2D.h"
#include "../Physics2D/CollisionChain2D.h"
#include "../Physics2D/CollisionCircle2D.h"
#include "../Physics2D/CollisionEdge2D.h"
#include "../Physics2D/CollisionPolygon2D.h"
#include "../Physics2D/Constraint2D.h"
#include "../Physics2D/ConstraintDistance2D.h"
#include "../Physics2D/ConstraintFriction2D.h"
#include "../Physics2D/ConstraintGear2D.h"
#include "../Physics2D/ConstraintMotor2D.h"
#include "../Physics2D/ConstraintMouse2D.h"
#include "../Physics2D/ConstraintPrismatic2D.h"
#include "../Physics2D/ConstraintPulley2D.h"
#include "../Physics2D/ConstraintRevolute2D.h"
#include "../Physics2D/ConstraintRope2D.h"
#include "../Physics2D/ConstraintWeld2D.h"
#include "../Physics2D/ConstraintWheel2D.h"
#include "../Physics2D/Physics2D.h"
#include "../Physics2D/PhysicsWorld2D.h"
#include "../Physics2D/RigidBody2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* PHYSICS2D_CATEGORY = "Physics2D";

void RegisterPhysics2DLibrary(Context* context)
{
    PhysicsWorld2D::RegisterObject(context);
    RigidBody2D::RegisterObject(context);

    CollisionShape2D::RegisterObject(context);
    CollisionBox2D::RegisterObject(context);
    CollisionChain2D::RegisterObject(context);
    CollisionCircle2D::RegisterObject(context);
    CollisionEdge2D::RegisterObject(context);
    CollisionPolygon2D::RegisterObject(context);

    Constraint2D::RegisterObject(context);
    ConstraintDistance2D::RegisterObject(context);
    ConstraintFriction2D::RegisterObject(context);
    ConstraintGear2D::RegisterObject(context);
    ConstraintMotor2D::RegisterObject(context);
    ConstraintMouse2D::RegisterObject(context);
    ConstraintPrismatic2D::RegisterObject(context);
    ConstraintPulley2D::RegisterObject(context);
    ConstraintRevolute2D::RegisterObject(context);
    ConstraintRope2D::RegisterObject(context);
    ConstraintWeld2D::RegisterObject(context);
    ConstraintWheel2D::RegisterObject(context);
}

}
