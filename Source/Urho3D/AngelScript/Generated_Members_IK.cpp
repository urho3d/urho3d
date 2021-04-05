// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

#ifdef URHO3D_IK

// class IKConstraint | File: ../IK/IKConstraint.h
void CollectMembers_IKConstraint(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class IKEffector | File: ../IK/IKEffector.h
void CollectMembers_IKEffector(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // bool IKEffector::GetFeature(Feature feature) const
    // Not registered because have @nobind mark
    // void IKEffector::SetFeature(Feature feature, bool enable)
    // Not registered because have @nobind mark

}

// class IKSolver | File: ../IK/IKSolver.h
void CollectMembers_IKSolver(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // Algorithm IKSolver::GetAlgorithm() const
    // Not registered because have @manualbind mark
    // bool IKSolver::GetFeature(Feature feature) const
    // Not registered because have @nobind mark
    // void IKSolver::SetAlgorithm(Algorithm algorithm)
    // Not registered because have @manualbind mark
    // void IKSolver::SetFeature(Feature feature, bool enable)
    // Not registered because have @nobind mark

}

#endif // def URHO3D_IK

} // namespace Urho3D
