// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

#ifdef URHO3D_URHO2D

// struct DelayedWorldTransform2D | File: ../Urho2D/PhysicsWorld2D.h
void CollectMembers_DelayedWorldTransform2D(MemberCollection& members)
{
    // RigidBody2D* DelayedWorldTransform2D::rigidBody_
    // Not registered because pointer
    // RigidBody2D* DelayedWorldTransform2D::parentRigidBody_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 DelayedWorldTransform2D::worldPosition_", "Vector3 worldPosition", offsetof(DelayedWorldTransform2D, worldPosition_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Quaternion DelayedWorldTransform2D::worldRotation_", "Quaternion worldRotation", offsetof(DelayedWorldTransform2D, worldRotation_)));

}

// struct Particle2D | File: ../Urho2D/ParticleEmitter2D.h
void CollectMembers_Particle2D(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::timeToLive_", "float timeToLive", offsetof(Particle2D, timeToLive_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Particle2D::position_", "Vector3 position", offsetof(Particle2D, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::size_", "float size", offsetof(Particle2D, size_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::sizeDelta_", "float sizeDelta", offsetof(Particle2D, sizeDelta_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::rotation_", "float rotation", offsetof(Particle2D, rotation_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::rotationDelta_", "float rotationDelta", offsetof(Particle2D, rotationDelta_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Color Particle2D::color_", "Color color", offsetof(Particle2D, color_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Color Particle2D::colorDelta_", "Color colorDelta", offsetof(Particle2D, colorDelta_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Particle2D::startPos_", "Vector2 startPos", offsetof(Particle2D, startPos_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Particle2D::velocity_", "Vector2 velocity", offsetof(Particle2D, velocity_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::radialAcceleration_", "float radialAcceleration", offsetof(Particle2D, radialAcceleration_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::tangentialAcceleration_", "float tangentialAcceleration", offsetof(Particle2D, tangentialAcceleration_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::emitRadius_", "float emitRadius", offsetof(Particle2D, emitRadius_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::emitRadiusDelta_", "float emitRadiusDelta", offsetof(Particle2D, emitRadiusDelta_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::emitRotation_", "float emitRotation", offsetof(Particle2D, emitRotation_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Particle2D::emitRotationDelta_", "float emitRotationDelta", offsetof(Particle2D, emitRotationDelta_)));

}

// struct PhysicsRaycastResult2D | File: ../Urho2D/PhysicsWorld2D.h
void CollectMembers_PhysicsRaycastResult2D(MemberCollection& members)
{
    // bool PhysicsRaycastResult2D::operator !=(const PhysicsRaycastResult2D& rhs) const
    // Only operator == is needed

    // RigidBody2D* PhysicsRaycastResult2D::body_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 PhysicsRaycastResult2D::position_", "Vector2 position", offsetof(PhysicsRaycastResult2D, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 PhysicsRaycastResult2D::normal_", "Vector2 normal", offsetof(PhysicsRaycastResult2D, normal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float PhysicsRaycastResult2D::distance_", "float distance", offsetof(PhysicsRaycastResult2D, distance_)));

}

// struct SourceBatch2D | File: ../Urho2D/Drawable2D.h
void CollectMembers_SourceBatch2D(MemberCollection& members)
{
    // WeakPtr<Drawable2D> SourceBatch2D::owner_
    // Error: type "WeakPtr<Drawable2D>" can not automatically bind
    // SharedPtr<Material> SourceBatch2D::material_
    // Error: type "SharedPtr<Material>" can not automatically bind
    // Vector<Vertex2D> SourceBatch2D::vertices_
    // Error: type "Vector<Vertex2D>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float SourceBatch2D::distance_", "float distance", offsetof(SourceBatch2D, distance_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int SourceBatch2D::drawOrder_", "int drawOrder", offsetof(SourceBatch2D, drawOrder_)));

}

// struct TileMapInfo2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_TileMapInfo2D(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Orientation2D TileMapInfo2D::orientation_", "Orientation2D orientation", offsetof(TileMapInfo2D, orientation_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int TileMapInfo2D::width_", "int width", offsetof(TileMapInfo2D, width_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int TileMapInfo2D::height_", "int height", offsetof(TileMapInfo2D, height_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TileMapInfo2D::tileWidth_", "float tileWidth", offsetof(TileMapInfo2D, tileWidth_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TileMapInfo2D::tileHeight_", "float tileHeight", offsetof(TileMapInfo2D, tileHeight_)));

}

// struct Vertex2D | File: ../Urho2D/Drawable2D.h
void CollectMembers_Vertex2D(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Vertex2D::position_", "Vector3 position", offsetof(Vertex2D, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned Vertex2D::color_", "uint color", offsetof(Vertex2D, color_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Vertex2D::uv_", "Vector2 uv", offsetof(Vertex2D, uv_)));

}

// struct ViewBatchInfo2D | File: ../Urho2D/Renderer2D.h
void CollectMembers_ViewBatchInfo2D(MemberCollection& members)
{
    // SharedPtr<VertexBuffer> ViewBatchInfo2D::vertexBuffer_
    // Error: type "SharedPtr<VertexBuffer>" can not automatically bind
    // PODVector<const SourceBatch2D*> ViewBatchInfo2D::sourceBatches_
    // Error: type "PODVector<const SourceBatch2D*>" can not automatically bind
    // PODVector<float> ViewBatchInfo2D::distances_
    // Error: type "PODVector<float>" can not automatically bind
    // Vector<SharedPtr<Material>> ViewBatchInfo2D::materials_
    // Error: type "Vector<SharedPtr<Material>>" can not automatically bind
    // Vector<SharedPtr<Geometry>> ViewBatchInfo2D::geometries_
    // Error: type "Vector<SharedPtr<Geometry>>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ViewBatchInfo2D::vertexBufferUpdateFrameNumber_", "uint vertexBufferUpdateFrameNumber", offsetof(ViewBatchInfo2D, vertexBufferUpdateFrameNumber_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ViewBatchInfo2D::indexCount_", "uint indexCount", offsetof(ViewBatchInfo2D, indexCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ViewBatchInfo2D::vertexCount_", "uint vertexCount", offsetof(ViewBatchInfo2D, vertexCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ViewBatchInfo2D::batchUpdatedFrameNumber_", "uint batchUpdatedFrameNumber", offsetof(ViewBatchInfo2D, batchUpdatedFrameNumber_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ViewBatchInfo2D::batchCount_", "uint batchCount", offsetof(ViewBatchInfo2D, batchCount_)));

}

// class PropertySet2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_PropertySet2D(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class Tile2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_Tile2D(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class TileMapObject2D | File: ../Urho2D/TileMapDefs2D.h
void CollectMembers_TileMapObject2D(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class TmxLayer2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxLayer2D(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class TmxImageLayer2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxImageLayer2D(MemberCollection& members)
{
    CollectMembers_TmxLayer2D(members);

}

// class TmxObjectGroup2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxObjectGroup2D(MemberCollection& members)
{
    CollectMembers_TmxLayer2D(members);

    // void TmxObjectGroup2D::StoreObject(const XMLElement& objectElem, const SharedPtr<TileMapObject2D>& object, const TileMapInfo2D& info, bool isTile = false)
    // Error: type "const SharedPtr<TileMapObject2D>&" can not automatically bind

}

// class TmxTileLayer2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxTileLayer2D(MemberCollection& members)
{
    CollectMembers_TmxLayer2D(members);

}

// class AnimationSet2D | File: ../Urho2D/AnimationSet2D.h
void CollectMembers_AnimationSet2D(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");

    // Spriter::SpriterData* AnimationSet2D::GetSpriterData() const
    // Error: type "Spriter::SpriterData*" can not automatically bind

    // static void AnimationSet2D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class ParticleEffect2D | File: ../Urho2D/ParticleEffect2D.h
void CollectMembers_ParticleEffect2D(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // static void ParticleEffect2D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Sprite2D | File: ../Urho2D/Sprite2D.h
void CollectMembers_Sprite2D(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");

    // static void Sprite2D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class SpriteSheet2D | File: ../Urho2D/SpriteSheet2D.h
void CollectMembers_SpriteSheet2D(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");

    // const HashMap<String, SharedPtr<Sprite2D>>& SpriteSheet2D::GetSpriteMapping() const
    // Error: type "const HashMap<String, SharedPtr<Sprite2D>>&" can not automatically bind

    // static void SpriteSheet2D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class TmxFile2D | File: ../Urho2D/TmxFile2D.h
void CollectMembers_TmxFile2D(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::EndLoad()");

    // void TmxFile2D::AddLayer(Urho3D::TmxLayer2D* layer)
    // Error: type "Urho3D::TmxLayer2D*" can not automatically bind

    // static void TmxFile2D::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class CollisionShape2D | File: ../Urho2D/CollisionShape2D.h
void CollectMembers_CollisionShape2D(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::OnSetEnabled()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // b2Fixture* CollisionShape2D::GetFixture() const
    // Error: type "b2Fixture*" can not automatically bind

}

// class Constraint2D | File: ../Urho2D/Constraint2D.h
void CollectMembers_Constraint2D(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::OnSetEnabled()");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // b2Joint* Constraint2D::GetJoint() const
    // Error: type "b2Joint*" can not automatically bind

}

// class PhysicsWorld2D | File: ../Urho2D/PhysicsWorld2D.h
void CollectMembers_PhysicsWorld2D(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // void PhysicsWorld2D::BeginContact(b2Contact* contact) override
    // Error: type "b2Contact*" can not automatically bind
    // void PhysicsWorld2D::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
    // Error: type "const b2Vec2*" can not automatically bind
    // void PhysicsWorld2D::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
    // Error: type "const b2Vec2*" can not automatically bind
    // void PhysicsWorld2D::DrawTransform(const b2Transform& xf) override
    // Error: type "const b2Transform&" can not automatically bind
    // void PhysicsWorld2D::EndContact(b2Contact* contact) override
    // Error: type "b2Contact*" can not automatically bind
    // void PhysicsWorld2D::GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask = M_MAX_UNSIGNED)
    // Error: type "PODVector<RigidBody2D*>&" can not automatically bind
    // b2World* PhysicsWorld2D::GetWorld()
    // Error: type "b2World*" can not automatically bind
    // void PhysicsWorld2D::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
    // Error: type "b2Contact*" can not automatically bind
    // void PhysicsWorld2D::Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask = M_MAX_UNSIGNED)
    // Error: type "PODVector<PhysicsRaycastResult2D>&" can not automatically bind

}

// class RigidBody2D | File: ../Urho2D/RigidBody2D.h
void CollectMembers_RigidBody2D(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::OnSetEnabled()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // b2Body* RigidBody2D::GetBody() const
    // Error: type "b2Body*" can not automatically bind

}

// class TileMap2D | File: ../Urho2D/TileMap2D.h
void CollectMembers_TileMap2D(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class TileMapLayer2D | File: ../Urho2D/TileMapLayer2D.h
void CollectMembers_TileMapLayer2D(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class CollisionBox2D | File: ../Urho2D/CollisionBox2D.h
void CollectMembers_CollisionBox2D(MemberCollection& members)
{
    CollectMembers_CollisionShape2D(members);

    Remove(members.staticMethods_, "static void CollisionShape2D::RegisterObject(Context* context)");

}

// class CollisionChain2D | File: ../Urho2D/CollisionChain2D.h
void CollectMembers_CollisionChain2D(MemberCollection& members)
{
    CollectMembers_CollisionShape2D(members);

    Remove(members.staticMethods_, "static void CollisionShape2D::RegisterObject(Context* context)");

    // PODVector<unsigned char> CollisionChain2D::GetVerticesAttr() const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // void CollisionChain2D::SetVerticesAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class CollisionCircle2D | File: ../Urho2D/CollisionCircle2D.h
void CollectMembers_CollisionCircle2D(MemberCollection& members)
{
    CollectMembers_CollisionShape2D(members);

    Remove(members.staticMethods_, "static void CollisionShape2D::RegisterObject(Context* context)");

}

// class CollisionEdge2D | File: ../Urho2D/CollisionEdge2D.h
void CollectMembers_CollisionEdge2D(MemberCollection& members)
{
    CollectMembers_CollisionShape2D(members);

    Remove(members.staticMethods_, "static void CollisionShape2D::RegisterObject(Context* context)");

}

// class CollisionPolygon2D | File: ../Urho2D/CollisionPolygon2D.h
void CollectMembers_CollisionPolygon2D(MemberCollection& members)
{
    CollectMembers_CollisionShape2D(members);

    Remove(members.staticMethods_, "static void CollisionShape2D::RegisterObject(Context* context)");

    // PODVector<unsigned char> CollisionPolygon2D::GetVerticesAttr() const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // void CollisionPolygon2D::SetVerticesAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class ConstraintDistance2D | File: ../Urho2D/ConstraintDistance2D.h
void CollectMembers_ConstraintDistance2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintFriction2D | File: ../Urho2D/ConstraintFriction2D.h
void CollectMembers_ConstraintFriction2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintGear2D | File: ../Urho2D/ConstraintGear2D.h
void CollectMembers_ConstraintGear2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintMotor2D | File: ../Urho2D/ConstraintMotor2D.h
void CollectMembers_ConstraintMotor2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintMouse2D | File: ../Urho2D/ConstraintMouse2D.h
void CollectMembers_ConstraintMouse2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintPrismatic2D | File: ../Urho2D/ConstraintPrismatic2D.h
void CollectMembers_ConstraintPrismatic2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintPulley2D | File: ../Urho2D/ConstraintPulley2D.h
void CollectMembers_ConstraintPulley2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintRevolute2D | File: ../Urho2D/ConstraintRevolute2D.h
void CollectMembers_ConstraintRevolute2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintRope2D | File: ../Urho2D/ConstraintRope2D.h
void CollectMembers_ConstraintRope2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintWeld2D | File: ../Urho2D/ConstraintWeld2D.h
void CollectMembers_ConstraintWeld2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class ConstraintWheel2D | File: ../Urho2D/ConstraintWheel2D.h
void CollectMembers_ConstraintWheel2D(MemberCollection& members)
{
    CollectMembers_Constraint2D(members);

    Remove(members.staticMethods_, "static void Constraint2D::RegisterObject(Context* context)");

}

// class Drawable2D | File: ../Urho2D/Drawable2D.h
void CollectMembers_Drawable2D(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "void Drawable::OnSetEnabled() override");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches()
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind

}

// class Renderer2D | File: ../Urho2D/Renderer2D.h
void CollectMembers_Renderer2D(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

}

// class ParticleEmitter2D | File: ../Urho2D/ParticleEmitter2D.h
void CollectMembers_ParticleEmitter2D(MemberCollection& members)
{
    CollectMembers_Drawable2D(members);

    Remove(members.methods_, "virtual void Drawable::Update(const FrameInfo& frame)");
    Remove(members.methods_, "void Drawable2D::OnSetEnabled() override");

    Remove(members.staticMethods_, "static void Drawable2D::RegisterObject(Context* context)");

}

// class StaticSprite2D | File: ../Urho2D/StaticSprite2D.h
void CollectMembers_StaticSprite2D(MemberCollection& members)
{
    CollectMembers_Drawable2D(members);

    Remove(members.staticMethods_, "static void Drawable2D::RegisterObject(Context* context)");

}

// class AnimatedSprite2D | File: ../Urho2D/AnimatedSprite2D.h
void CollectMembers_AnimatedSprite2D(MemberCollection& members)
{
    CollectMembers_StaticSprite2D(members);

    Remove(members.methods_, "void Drawable2D::OnSetEnabled() override");

    Remove(members.staticMethods_, "static void StaticSprite2D::RegisterObject(Context* context)");

}

// class StretchableSprite2D | File: ../Urho2D/StretchableSprite2D.h
void CollectMembers_StretchableSprite2D(MemberCollection& members)
{
    CollectMembers_StaticSprite2D(members);

    Remove(members.staticMethods_, "static void StaticSprite2D::RegisterObject(Context* context)");

}

#endif // def URHO3D_URHO2D

} // namespace Urho3D
