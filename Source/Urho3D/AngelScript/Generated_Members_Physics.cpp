// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

#ifdef URHO3D_PHYSICS

// struct DelayedWorldTransform | File: ../Physics/PhysicsWorld.h
void CollectMembers_DelayedWorldTransform(MemberCollection& members)
{
    // RigidBody* DelayedWorldTransform::rigidBody_
    // Not registered because pointer
    // RigidBody* DelayedWorldTransform::parentRigidBody_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DelayedWorldTransform::worldPosition_", "Vector3 worldPosition", offsetof(DelayedWorldTransform, worldPosition_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Quaternion DelayedWorldTransform::worldRotation_", "Quaternion worldRotation", offsetof(DelayedWorldTransform, worldRotation_)));

}

// struct ManifoldPair | File: ../Physics/PhysicsWorld.h
void CollectMembers_ManifoldPair(MemberCollection& members)
{
    // btPersistentManifold* ManifoldPair::manifold_
    // Not registered because pointer
    // btPersistentManifold* ManifoldPair::flippedManifold_
    // Not registered because pointer

}

// struct PhysicsRaycastResult | File: ../Physics/PhysicsWorld.h
void CollectMembers_PhysicsRaycastResult(MemberCollection& members)
{
    // bool PhysicsRaycastResult::operator !=(const PhysicsRaycastResult& rhs) const
    // Only operator == is needed

    // RigidBody* PhysicsRaycastResult::body_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 PhysicsRaycastResult::position_", "Vector3 position", offsetof(PhysicsRaycastResult, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 PhysicsRaycastResult::normal_", "Vector3 normal", offsetof(PhysicsRaycastResult, normal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float PhysicsRaycastResult::distance_", "float distance", offsetof(PhysicsRaycastResult, distance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float PhysicsRaycastResult::hitFraction_", "float hitFraction", offsetof(PhysicsRaycastResult, hitFraction_)));

}

// struct PhysicsWorldConfig | File: ../Physics/PhysicsWorld.h
void CollectMembers_PhysicsWorldConfig(MemberCollection& members)
{
    // btCollisionConfiguration* PhysicsWorldConfig::collisionConfig_
    // Not registered because pointer

}

// struct CollisionGeometryData | File: ../Physics/CollisionShape.h
void CollectMembers_CollisionGeometryData(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// struct ConvexData | File: ../Physics/CollisionShape.h
void CollectMembers_ConvexData(MemberCollection& members)
{
    CollectMembers_CollisionGeometryData(members);

    // SharedArrayPtr<Vector3> ConvexData::vertexData_
    // Error: type "SharedArrayPtr<Vector3>" can not automatically bind
    // SharedArrayPtr<unsigned> ConvexData::indexData_
    // Error: type "SharedArrayPtr<unsigned>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ConvexData::vertexCount_", "uint vertexCount", offsetof(ConvexData, vertexCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ConvexData::indexCount_", "uint indexCount", offsetof(ConvexData, indexCount_)));

}

// struct GImpactMeshData | File: ../Physics/CollisionShape.h
void CollectMembers_GImpactMeshData(MemberCollection& members)
{
    CollectMembers_CollisionGeometryData(members);

    // UniquePtr<TriangleMeshInterface> GImpactMeshData::meshInterface_
    // Error: type "UniquePtr<TriangleMeshInterface>" can not automatically bind

}

// struct HeightfieldData | File: ../Physics/CollisionShape.h
void CollectMembers_HeightfieldData(MemberCollection& members)
{
    CollectMembers_CollisionGeometryData(members);

    // SharedArrayPtr<float> HeightfieldData::heightData_
    // Error: type "SharedArrayPtr<float>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 HeightfieldData::spacing_", "Vector3 spacing", offsetof(HeightfieldData, spacing_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntVector2 HeightfieldData::size_", "IntVector2 size", offsetof(HeightfieldData, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float HeightfieldData::minHeight_", "float minHeight", offsetof(HeightfieldData, minHeight_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float HeightfieldData::maxHeight_", "float maxHeight", offsetof(HeightfieldData, maxHeight_)));

}

// struct TriangleMeshData | File: ../Physics/CollisionShape.h
void CollectMembers_TriangleMeshData(MemberCollection& members)
{
    CollectMembers_CollisionGeometryData(members);

    // UniquePtr<TriangleMeshInterface> TriangleMeshData::meshInterface_
    // Error: type "UniquePtr<TriangleMeshInterface>" can not automatically bind
    // UniquePtr<btBvhTriangleMeshShape> TriangleMeshData::shape_
    // Error: type "UniquePtr<btBvhTriangleMeshShape>" can not automatically bind
    // UniquePtr<btTriangleInfoMap> TriangleMeshData::infoMap_
    // Error: type "UniquePtr<btTriangleInfoMap>" can not automatically bind

}

// class CollisionShape | File: ../Physics/CollisionShape.h
void CollectMembers_CollisionShape(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Component::OnSetEnabled()");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // btCollisionShape* CollisionShape::GetCollisionShape() const
    // Error: type "btCollisionShape*" can not automatically bind

}

// class Constraint | File: ../Physics/Constraint.h
void CollectMembers_Constraint(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Component::GetDependencyNodes(PODVector<Node*>& dest)");
    Remove(members.methods_, "virtual void Component::OnSetEnabled()");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // btTypedConstraint* Constraint::GetConstraint() const
    // Error: type "btTypedConstraint*" can not automatically bind

}

// class PhysicsWorld | File: ../Physics/PhysicsWorld.h
void CollectMembers_PhysicsWorld(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, btCollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask = M_MAX_UNSIGNED)
    // Error: type "btCollisionShape*" can not automatically bind
    // void PhysicsWorld::GetCollidingBodies(PODVector<RigidBody*>& result, const RigidBody* body)
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // CollisionGeometryDataCache& PhysicsWorld::GetConvexCache()
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // CollisionGeometryDataCache& PhysicsWorld::GetGImpactTrimeshCache()
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const BoundingBox& box, unsigned collisionMask = M_MAX_UNSIGNED)
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const RigidBody* body)
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const Sphere& sphere, unsigned collisionMask = M_MAX_UNSIGNED)
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // CollisionGeometryDataCache& PhysicsWorld::GetTriMeshCache()
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // btDiscreteDynamicsWorld* PhysicsWorld::GetWorld()
    // Error: type "btDiscreteDynamicsWorld*" can not automatically bind
    // void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED)
    // Error: type "PODVector<PhysicsRaycastResult>&" can not automatically bind
    // void PhysicsWorld::draw3dText(const btVector3& location, const char* textString) override
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override
    // Error: type "const btVector3&" can not automatically bind
    // bool PhysicsWorld::isVisible(const btVector3& aabbMin, const btVector3& aabbMax) override
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::reportErrorWarning(const char* warningString) override
    // Error: type "const char*" can not automatically bind

    // static struct PhysicsWorldConfig PhysicsWorld::config
    // Error: type "struct PhysicsWorldConfig" can not automatically bind

}

// class RigidBody | File: ../Physics/RigidBody.h
void CollectMembers_RigidBody(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Component::OnSetEnabled()");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // btRigidBody* RigidBody::GetBody() const
    // Error: type "btRigidBody*" can not automatically bind
    // void RigidBody::GetCollidingBodies(PODVector<RigidBody*>& result) const
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // btCompoundShape* RigidBody::GetCompoundShape() const
    // Error: type "btCompoundShape*" can not automatically bind
    // const PODVector<unsigned char>& RigidBody::GetNetAngularVelocityAttr() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void RigidBody::SetNetAngularVelocityAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void RigidBody::getWorldTransform(btTransform& worldTrans) const override
    // Not registered because have @nobind mark
    // void RigidBody::setWorldTransform(const btTransform& worldTrans) override
    // Not registered because have @nobind mark

}

// class RaycastVehicle | File: ../Physics/RaycastVehicle.h
void CollectMembers_RaycastVehicle(MemberCollection& members)
{
    CollectMembers_LogicComponent(members);

    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // VariantVector RaycastVehicle::GetWheelDataAttr() const
    // Error: type "VariantVector" can not automatically bind
    // void RaycastVehicle::SetWheelDataAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 RaycastVehicle::RIGHT_UP_FORWARD", "const IntVector3 RIGHT_UP_FORWARD", (void*)&RaycastVehicle::RIGHT_UP_FORWARD));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 RaycastVehicle::RIGHT_FORWARD_UP", "const IntVector3 RIGHT_FORWARD_UP", (void*)&RaycastVehicle::RIGHT_FORWARD_UP));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 RaycastVehicle::UP_FORWARD_RIGHT", "const IntVector3 UP_FORWARD_RIGHT", (void*)&RaycastVehicle::UP_FORWARD_RIGHT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 RaycastVehicle::UP_RIGHT_FORWARD", "const IntVector3 UP_RIGHT_FORWARD", (void*)&RaycastVehicle::UP_RIGHT_FORWARD));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 RaycastVehicle::FORWARD_RIGHT_UP", "const IntVector3 FORWARD_RIGHT_UP", (void*)&RaycastVehicle::FORWARD_RIGHT_UP));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 RaycastVehicle::FORWARD_UP_RIGHT", "const IntVector3 FORWARD_UP_RIGHT", (void*)&RaycastVehicle::FORWARD_UP_RIGHT));

}

#endif // def URHO3D_PHYSICS

} // namespace Urho3D
