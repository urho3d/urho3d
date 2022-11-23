// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../IK/IK.h"
#include "../IK/IKConstraint.h"
#include "../IK/IKEffector.h"
#include "../IK/IKSolver.h"

namespace Urho3D
{

const char* IK_CATEGORY = "Inverse Kinematics";

// ----------------------------------------------------------------------------
void RegisterIKLibrary(Context* context)
{
    //IKConstraint::RegisterObject(context);
    IKEffector::RegisterObject(context);
    IKSolver::RegisterObject(context);
}

} // namespace Urho3D
