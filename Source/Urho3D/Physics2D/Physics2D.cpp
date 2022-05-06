// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    ConstraintWeld2D::RegisterObject(context);
    ConstraintWheel2D::RegisterObject(context);
}

}
