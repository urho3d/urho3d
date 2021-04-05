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

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_IK(asIScriptEngine* engine)
{
    // enum IKSolver::Algorithm | File: ../IK/IKSolver.h
    engine->RegisterEnum("IKAlgorithm");
    engine->RegisterEnumValue("IKAlgorithm", "ONE_BONE", IKSolver::ONE_BONE);
    engine->RegisterEnumValue("IKAlgorithm", "TWO_BONE", IKSolver::TWO_BONE);
    engine->RegisterEnumValue("IKAlgorithm", "FABRIK", IKSolver::FABRIK);

    // enum IKSolver::Feature | File: ../IK/IKSolver.h
    engine->RegisterEnum("IKFeature");
    engine->RegisterEnumValue("IKFeature", "JOINT_ROTATIONS", IKSolver::JOINT_ROTATIONS);
    engine->RegisterEnumValue("IKFeature", "TARGET_ROTATIONS", IKSolver::TARGET_ROTATIONS);
    engine->RegisterEnumValue("IKFeature", "UPDATE_ORIGINAL_POSE", IKSolver::UPDATE_ORIGINAL_POSE);
    engine->RegisterEnumValue("IKFeature", "UPDATE_ACTIVE_POSE", IKSolver::UPDATE_ACTIVE_POSE);
    engine->RegisterEnumValue("IKFeature", "USE_ORIGINAL_POSE", IKSolver::USE_ORIGINAL_POSE);
    engine->RegisterEnumValue("IKFeature", "CONSTRAINTS", IKSolver::CONSTRAINTS);
    engine->RegisterEnumValue("IKFeature", "AUTO_SOLVE", IKSolver::AUTO_SOLVE);
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_IK(asIScriptEngine* engine)
{
    // Algorithm IKSolver::GetAlgorithm() const | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "IKAlgorithm get_algorithm() const", AS_METHOD(IKSolver, GetAlgorithm), AS_CALL_THISCALL);
    
    // void IKSolver::SetAlgorithm(Algorithm algorithm) | File: ../IK/IKSolver.h
    engine->RegisterObjectMethod("IKSolver", "void set_algorithm(IKAlgorithm)", AS_METHOD(IKSolver, SetAlgorithm), AS_CALL_THISCALL);
}

}

#endif // def URHO3D_IK
