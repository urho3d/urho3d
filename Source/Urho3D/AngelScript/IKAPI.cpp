//
// Copyright (c) 2008-2017 the Urho3D project.
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

static void RegisterIKSolver(asIScriptEngine* engine)
{
    engine->RegisterEnum("IKAlgorithm");
    engine->RegisterEnumValue("IKAlgorithm", "FABRIK", IKSolver::FABRIK);

    RegisterComponent<IKSolver>(engine, "IKSolver");
    engine->RegisterObjectMethod("IKSolver", "IKAlgorithm get_algorithm() const", asMETHOD(IKSolver, GetAlgorithm), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_algorithm(IKAlgorithm)", asMETHOD(IKSolver, SetAlgorithm), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "uint get_maximumIterations() const", asMETHOD(IKSolver, GetMaximumIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_maximumIterations(uint)", asMETHOD(IKSolver, SetMaximumIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "float get_tolerance() const", asMETHOD(IKSolver, GetTolerance), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_tolerance(float)", asMETHOD(IKSolver, SetTolerance), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_boneRotations() const", asMETHOD(IKSolver, BoneRotationsEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_boneRotations(bool)", asMETHOD(IKSolver, EnableBoneRotations), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_targetRotation() const", asMETHOD(IKSolver, TargetRotationEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_targetRotation(bool)", asMETHOD(IKSolver, EnableTargetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_continuousSolving() const", asMETHOD(IKSolver, ContinuousSolvingEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_continuousSolving(bool)", asMETHOD(IKSolver, EnableContinuousSolving), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_updatePose() const", asMETHOD(IKSolver, UpdatePoseEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_updatePose(bool)", asMETHOD(IKSolver, EnableUpdatePose), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "bool get_autoSolve() const", asMETHOD(IKSolver, AutoSolveEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void set_autoSolve(bool)", asMETHOD(IKSolver, EnableAutoSolve), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void Solve()", asMETHOD(IKSolver, Solve), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void ResetToInitialPose()", asMETHOD(IKSolver, ResetToInitialPose), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKSolver", "void UpdateInitialPose()", asMETHOD(IKSolver, UpdateInitialPose), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("IKEffector", "bool get_weightedNlerp() const", asMETHOD(IKEffector, WeightedNlerpEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_weightedNlerp(bool)", asMETHOD(IKEffector, EnableWeightedNlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "bool get_inheritParentRotation() const", asMETHOD(IKEffector, InheritParentRotationEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void set_inheritParentRotation(bool)", asMETHOD(IKEffector, EnableInheritParentRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("IKEffector", "void DrawDebugGeometry(bool)", asMETHODPR(IKEffector, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
}

static void RegisterIKConstraint(asIScriptEngine* engine)
{
    RegisterComponent<IKConstraint>(engine, "IKConstraint");
}

void RegisterIKAPI(asIScriptEngine* engine)
{
    RegisterIKSolver(engine);
    RegisterIKEffector(engine);
    RegisterIKConstraint(engine);
}

}

#endif
