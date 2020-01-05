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

#ifdef URHO3D_IK

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../IK/IKSolver.h"
#include "../IK/IKEffector.h"
#include "../IK/IKConstraint.h"

namespace Urho3D
{

static void RegisterIKEnumerations(asIScriptEngine* engine)
{
    engine->RegisterEnum("IKAlgorithm");
    engine->RegisterEnumValue("IKAlgorithm", "ONE_BONE", IKSolver::ONE_BONE);
    engine->RegisterEnumValue("IKAlgorithm", "TWO_BONE", IKSolver::TWO_BONE);
    engine->RegisterEnumValue("IKAlgorithm", "FABRIK", IKSolver::FABRIK);
}

void RegisterIKSolver(asIScriptEngine* engine)
{
    RegisterComponent<IKSolver>(engine, "IKSolver");
    engine->RegisterObjectMethod("IKSolver", "IKAlgorithm get_algorithm() const", asMETHOD(IKSolver, GetAlgorithm), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_algorithm(IKAlgorithm)", asMETHOD(IKSolver, SetAlgorithm), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_maximumIterations() const", asMETHOD(IKSolver, GetMaximumIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_maximumIterations(uint)", asMETHOD(IKSolver, SetMaximumIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "float get_tolerance() const", asMETHOD(IKSolver, GetTolerance), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_tolerance(float)", asMETHOD(IKSolver, SetTolerance), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_JOINT_ROTATIONS() const", asMETHOD(IKSolver, GetJOINT_ROTATIONS), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_JOINT_ROTATIONS(bool)", asMETHOD(IKSolver, SetJOINT_ROTATIONS), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_TARGET_ROTATIONS() const", asMETHOD(IKSolver, GetTARGET_ROTATIONS), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_TARGET_ROTATIONS(bool)", asMETHOD(IKSolver, SetTARGET_ROTATIONS), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_UPDATE_ORIGINAL_POSE() const", asMETHOD(IKSolver, GetUPDATE_ORIGINAL_POSE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_UPDATE_ORIGINAL_POSE(bool)", asMETHOD(IKSolver, SetUPDATE_ORIGINAL_POSE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_UPDATE_ACTIVE_POSE() const", asMETHOD(IKSolver, GetUPDATE_ACTIVE_POSE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_UPDATE_ACTIVE_POSE(bool)", asMETHOD(IKSolver, SetUPDATE_ACTIVE_POSE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_USE_ORIGINAL_POSE() const", asMETHOD(IKSolver, GetUSE_ORIGINAL_POSE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_USE_ORIGINAL_POSE(bool)", asMETHOD(IKSolver, SetUSE_ORIGINAL_POSE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_CONSTRAINTS() const", asMETHOD(IKSolver, GetCONSTRAINTS), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_CONSTRAINTS(bool)", asMETHOD(IKSolver, SetCONSTRAINTS), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_AUTO_SOLVE() const", asMETHOD(IKSolver, GetAUTO_SOLVE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_AUTO_SOLVE(bool)", asMETHOD(IKSolver, SetAUTO_SOLVE), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void RebuildChainTrees()", asMETHOD(IKSolver, RebuildChainTrees), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void RecalculateSegmentLengths()", asMETHOD(IKSolver, RecalculateSegmentLengths), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void CalculateJointRotations()", asMETHOD(IKSolver, CalculateJointRotations), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void Solve()", asMETHOD(IKSolver, Solve), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void ApplyOriginalPoseToScene()", asMETHOD(IKSolver, ApplyOriginalPoseToScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void ApplySceneToInitialPose()", asMETHOD(IKSolver, ApplySceneToOriginalPose), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void ApplyActivePoseToScene()", asMETHOD(IKSolver, ApplyActivePoseToScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void ApplySceneToActivePose()", asMETHOD(IKSolver, ApplySceneToActivePose), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void ApplyOriginalPoseToActivePose()", asMETHOD(IKSolver, ApplyOriginalPoseToActivePose), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void DrawDebugGeometry(bool)", asMETHODPR(IKSolver, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
}

static void RegisterIKEffector(asIScriptEngine* engine)
{
    RegisterComponent<IKEffector>(engine, "IKEffector");
    engine->RegisterObjectMethod("IKEffector", "Node@+ get_targetNode() const", asMETHOD(IKEffector, GetTargetNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetNode(Node@+)", asMETHOD(IKEffector, SetTargetNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "String& get_targetName() const", asMETHOD(IKEffector, GetTargetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetName(const String&in)", asMETHOD(IKEffector, SetTargetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Vector3& get_targetPosition() const", asMETHOD(IKEffector, GetTargetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetPosition(Vector3&in)", asMETHOD(IKEffector, SetTargetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "Quaternion& get_targetRotation() const", asMETHOD(IKEffector, GetTargetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_targetRotation(Quaternion&in)", asMETHOD(IKEffector, SetTargetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "uint get_chainLength() const", asMETHOD(IKEffector, GetChainLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_chainLength(uint)", asMETHOD(IKEffector, SetChainLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_weight() const", asMETHOD(IKEffector, GetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_weight(float)", asMETHOD(IKEffector, SetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_rotationWeight() const", asMETHOD(IKEffector, GetRotationWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_rotationWeight(float)", asMETHOD(IKEffector, SetRotationWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "float get_rotationDecay() const", asMETHOD(IKEffector, GetRotationDecay), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_rotationDecay(float)", asMETHOD(IKEffector, SetRotationDecay), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void DrawDebugGeometry(bool)", asMETHODPR(IKEffector, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
}

static void RegisterIKConstraint(asIScriptEngine* engine)
{
    RegisterComponent<IKConstraint>(engine, "IKConstraint");
}

void RegisterIKAPI(asIScriptEngine* engine)
{
    RegisterIKEnumerations(engine);
    RegisterIKSolver(engine);
    RegisterIKEffector(engine);
    //RegisterIKConstraint(engine);
}

}

#endif
