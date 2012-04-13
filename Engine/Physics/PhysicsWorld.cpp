//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "Precompiled.h"
#include "CollisionShape.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "Joint.h"
#include "Log.h"
#include "Mutex.h"
#include "PhysicsEvents.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "Ray.h"
#include "RigidBody.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Sort.h"

#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include "DebugNew.h"

static const int DEFAULT_FPS = 60;
static const Vector3 DEFAULT_GRAVITY = Vector3(0.0f, -9.81f, 0.0f);
static const float MAX_PHYSICS_TIMESTEP = 0.1f;

static bool CompareRaycastResults(const PhysicsRaycastResult& lhs, const PhysicsRaycastResult& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

void InternalPreTickCallback(btDynamicsWorld *world, btScalar timeStep)
{
    static_cast<PhysicsWorld*>(world->getWorldUserInfo())->PreStep(timeStep);
}

void InternalTickCallback(btDynamicsWorld *world, btScalar timeStep)
{
    static_cast<PhysicsWorld*>(world->getWorldUserInfo())->PostStep(timeStep);
}

OBJECTTYPESTATIC(PhysicsWorld);

PhysicsWorld::PhysicsWorld(Context* context) :
    Component(context),
    collisionConfiguration_(0),
    collisionDispatcher_(0),
    broadphase_(0),
    solver_(0),
    world_(0),
    fps_(DEFAULT_FPS),
    timeAcc_(0.0f),
    maxNetworkAngularVelocity_(DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY),
    interpolation_(true),
    debugRenderer_(0),
    debugMode_(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawConstraints)
{
    collisionConfiguration_ = new btDefaultCollisionConfiguration();
    collisionDispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
    broadphase_ = new btDbvtBroadphase();
    solver_ = new btSequentialImpulseConstraintSolver();
    world_ = new btDiscreteDynamicsWorld(collisionDispatcher_, broadphase_, solver_, collisionConfiguration_);
    
    world_->setGravity(ToBtVector3(DEFAULT_GRAVITY));
    world_->setDebugDrawer(this);
    world_->setInternalTickCallback(InternalPreTickCallback, static_cast<void*>(this), true);
    world_->setInternalTickCallback(InternalTickCallback, static_cast<void*>(this), false);
}

PhysicsWorld::~PhysicsWorld()
{
    if (scene_)
    {
        // Force all remaining joints, rigid bodies and collision shapes to release themselves
        for (PODVector<Joint*>::Iterator i = joints_.Begin(); i != joints_.End(); ++i)
            (*i)->Clear();
        
        for (PODVector<RigidBody*>::Iterator i = rigidBodies_.Begin(); i != rigidBodies_.End(); ++i)
            (*i)->ReleaseBody();
    }
    
    // Remove any cached geometries that still remain
    geometryCache_.Clear();
    
    delete world_;
    world_ = 0;
    
    delete solver_;
    solver_ = 0;
    
    delete broadphase_;
    broadphase_ = 0;
    
    delete collisionDispatcher_;
    collisionDispatcher_ = 0;
    
    delete collisionConfiguration_;
    collisionConfiguration_ = 0;
}

void PhysicsWorld::RegisterObject(Context* context)
{
    context->RegisterFactory<PhysicsWorld>();
    
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_VECTOR3, "Gravity", GetGravity, SetGravity, Vector3, DEFAULT_GRAVITY, AM_DEFAULT);
    ATTRIBUTE(PhysicsWorld, VAR_INT, "Physics FPS", fps_, DEFAULT_FPS, AM_DEFAULT);
    ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Net Max Angular Vel.", maxNetworkAngularVelocity_, DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY, AM_DEFAULT);
    ATTRIBUTE(PhysicsWorld, VAR_BOOL, "Interpolation", interpolation_, true, AM_FILE);
}

void PhysicsWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    if (debugRenderer_)
        debugRenderer_->AddLine(ToVector3(from), ToVector3(to), Color(color.x(), color.y(), color.z()), debugDepthTest_);
}

void PhysicsWorld::reportErrorWarning(const char* warningString)
{
    LOGWARNING("Physics: " + String(warningString));
}

void PhysicsWorld::Update(float timeStep)
{
    PROFILE(UpdatePhysics);
    
    // Clamp elapsed time to a maximum to prevent CPU usage spiralling out of control
    if (timeStep > MAX_PHYSICS_TIMESTEP)
        timeStep = MAX_PHYSICS_TIMESTEP;
    
    float internalTimeStep = 1.0f / fps_;
    
    if (interpolation_)
    {
        int maxSubSteps = (int)(MAX_PHYSICS_TIMESTEP * fps_);
        world_->stepSimulation(timeStep, maxSubSteps, internalTimeStep);
    }
    else
    {
        timeAcc_ += timeStep;
        while (timeAcc_ >= internalTimeStep)
        {
            world_->stepSimulation(internalTimeStep, 0, internalTimeStep);
            timeAcc_ -= internalTimeStep;
        }
    }
}

void PhysicsWorld::UpdateCollisions()
{
    world_->performDiscreteCollisionDetection();
}

void PhysicsWorld::SetFps(int fps)
{
    fps_ = Clamp(fps, 1, 1000);
}

void PhysicsWorld::SetGravity(Vector3 gravity)
{
    world_->setGravity(ToBtVector3(gravity));
}

void PhysicsWorld::SetInterpolation(bool enable)
{
    interpolation_ = enable;
}

void PhysicsWorld::SetMaxNetworkAngularVelocity(float velocity)
{
    maxNetworkAngularVelocity_ = Clamp(velocity, 1.0f, 32767.0f);
}

void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask)
{
    PROFILE(PhysicsRaycast);
    
    btCollisionWorld::AllHitsRayResultCallback rayCallback(ToBtVector3(ray.origin_), ToBtVector3(ray.origin_ + maxDistance * ray.direction_));
    rayCallback.m_collisionFilterGroup = (short)0xffff;
    rayCallback.m_collisionFilterMask = collisionMask;
    
    world_->rayTest(rayCallback.m_rayFromWorld, rayCallback.m_rayToWorld, rayCallback);
    
    for (int i = 0; i < rayCallback.m_collisionObjects.size(); ++i)
    {
        PhysicsRaycastResult newResult;
        newResult.body_ = static_cast<RigidBody*>(rayCallback.m_collisionObjects[i]->getUserPointer());
        newResult.position_ = ToVector3(rayCallback.m_hitPointWorld[i]);
        newResult.normal_ = ToVector3(rayCallback.m_hitNormalWorld[i]);
        newResult.distance_ = (newResult.position_ - ray.origin_).Length();
        result.Push(newResult);
    }
    
    Sort(result.Begin(), result.End(), CompareRaycastResults);
}

void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask)
{
    PROFILE(PhysicsRaycastSingle);
    
    btCollisionWorld::ClosestRayResultCallback rayCallback(ToBtVector3(ray.origin_), ToBtVector3(ray.origin_ + maxDistance * ray.direction_));
    rayCallback.m_collisionFilterGroup = (short)0xffff;
    rayCallback.m_collisionFilterMask = collisionMask;
    
    world_->rayTest(rayCallback.m_rayFromWorld, rayCallback.m_rayToWorld, rayCallback);
    
    if (rayCallback.hasHit())
    {
        result.body_ = static_cast<RigidBody*>(rayCallback.m_collisionObject->getUserPointer());
        result.position_ = ToVector3(rayCallback.m_hitPointWorld);
        result.normal_ = ToVector3(rayCallback.m_hitNormalWorld);
        result.distance_ = (result.position_ - ray.origin_).Length();
    }
    else
    {
        result.body_ = 0;
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
    }
}

Vector3 PhysicsWorld::GetGravity() const
{
    return ToVector3(world_->getGravity());
}

void PhysicsWorld::AddRigidBody(RigidBody* body)
{
    rigidBodies_.Push(body);
}

void PhysicsWorld::RemoveRigidBody(RigidBody* body)
{
    PODVector<RigidBody*>::Iterator i = rigidBodies_.Find(body);
    if (i != rigidBodies_.End())
        rigidBodies_.Erase(i);
}

void PhysicsWorld::AddCollisionShape(CollisionShape* shape)
{
    collisionShapes_.Push(shape);
}

void PhysicsWorld::RemoveCollisionShape(CollisionShape* shape)
{
    PODVector<CollisionShape*>::Iterator i = collisionShapes_.Find(shape);
    if (i != collisionShapes_.End())
        collisionShapes_.Erase(i);
}

void PhysicsWorld::AddJoint(Joint* joint)
{
    joints_.Push(joint);
}

void PhysicsWorld::RemoveJoint(Joint* joint)
{
    PODVector<Joint*>::Iterator i = joints_.Find(joint);
    if (i != joints_.End())
        joints_.Erase(i);
}

void PhysicsWorld::DrawDebugGeometry(bool depthTest)
{
    debugDepthTest_ = depthTest;
    debugRenderer_ = GetComponent<DebugRenderer>();
    world_->debugDrawWorld();
    debugRenderer_ = 0;
}

void PhysicsWorld::CleanupGeometryCache()
{
    // Remove cached shapes whose only reference is the cache itself
    for (Map<String, SharedPtr<CollisionGeometryData> >::Iterator i = geometryCache_.Begin();
        i != geometryCache_.End();)
    {
        Map<String, SharedPtr<CollisionGeometryData> >::Iterator current = i++;
        if (current->second_.Refs() == 1)
            geometryCache_.Erase(current);
    }
}

void PhysicsWorld::OnNodeSet(Node* node)
{
    // Subscribe to the scene subsystem update, which will trigger the physics simulation step
    if (node)
    {
        scene_ = node->GetScene();
        SubscribeToEvent(node, E_SCENESUBSYSTEMUPDATE, HANDLER(PhysicsWorld, HandleSceneSubsystemUpdate));
    }
}

void PhysicsWorld::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneSubsystemUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void PhysicsWorld::PreStep(float timeStep)
{
    // Send pre-step event
    using namespace PhysicsPreStep;
    
    VariantMap eventData;
    eventData[P_WORLD] = (void*)this;
    eventData[P_TIMESTEP] = timeStep;
    SendEvent(E_PHYSICSPRESTEP, eventData);
}

void PhysicsWorld::PostStep(float timeStep)
{
    SendCollisionEvents();
    
    // Send post-step event
    using namespace PhysicsPreStep;
    
    VariantMap eventData;
    eventData[P_WORLD] = (void*)this;
    eventData[P_TIMESTEP] = timeStep;
    SendEvent(E_PHYSICSPOSTSTEP, eventData);
}

void PhysicsWorld::SendCollisionEvents()
{
    PROFILE(SendCollisionEvents);
    
    currentCollisions_.Clear();
    int numManifolds = collisionDispatcher_->getNumManifolds();
    
    if (numManifolds)
    {
        VariantMap physicsCollisionData;
        VariantMap nodeCollisionData;
        VectorBuffer contacts;
        
        physicsCollisionData[PhysicsCollision::P_WORLD] = (void*)this;
        
        for (int i = 0; i < numManifolds; ++i)
        {
            btPersistentManifold* contactManifold = collisionDispatcher_->getManifoldByIndexInternal(i);
            btCollisionObject* objectA = static_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* objectB = static_cast<btCollisionObject*>(contactManifold->getBody1());
            
            RigidBody* bodyA = static_cast<RigidBody*>(objectA->getUserPointer());
            RigidBody* bodyB = static_cast<RigidBody*>(objectB->getUserPointer());
            
            // Skip collision event signaling if both objects are static, or if collision event mode does not match
            if (bodyA->GetMass() == 0.0f && bodyB->GetMass() == 0.0f)
                continue;
            if (bodyA->GetCollisionEventMode() == COLLISION_NEVER || bodyB->GetCollisionEventMode() == COLLISION_NEVER)
                return;
            if (bodyA->GetCollisionEventMode() == COLLISION_ACTIVE && bodyB->GetCollisionEventMode() == COLLISION_ACTIVE &&
                !bodyA->IsActive() && !bodyB->IsActive())
                return;
            
            Node* nodeA = bodyA->GetNode();
            Node* nodeB = bodyB->GetNode();
            WeakPtr<Node> nodeWeakA(nodeA);
            WeakPtr<Node> nodeWeakB(nodeB);
            
            Pair<RigidBody*, RigidBody*> bodyPair;
            if (bodyA < bodyB)
                bodyPair = MakePair(bodyA, bodyB);
            else
                bodyPair = MakePair(bodyB, bodyA);
            currentCollisions_.Insert(bodyPair);
            bool newCollision = !previousCollisions_.Contains(bodyPair);
            
            physicsCollisionData[PhysicsCollision::P_NODEA] = (void*)nodeA;
            physicsCollisionData[PhysicsCollision::P_NODEB] = (void*)nodeB;
            physicsCollisionData[PhysicsCollision::P_BODYA] = (void*)bodyA;
            physicsCollisionData[PhysicsCollision::P_BODYB] = (void*)bodyB;
            physicsCollisionData[PhysicsCollision::P_NEWCOLLISION] = !previousCollisions_.Contains(bodyPair);
            
            contacts.Clear();
            
            int numContacts = contactManifold->getNumContacts();
            for (int j = 0; j < numContacts; ++j)
            {
                btManifoldPoint& point = contactManifold->getContactPoint(j);
                contacts.WriteVector3(ToVector3(point.m_positionWorldOnB));
                contacts.WriteVector3(ToVector3(point.m_normalWorldOnB));
                contacts.WriteFloat(point.m_distance1);
                contacts.WriteFloat(point.m_appliedImpulse);
            }
            
            physicsCollisionData[PhysicsCollision::P_CONTACTS] = contacts.GetBuffer();
            
            SendEvent(E_PHYSICSCOLLISION, physicsCollisionData);
            
            // Skip if either of the nodes has been removed as a response to the event
            if (!nodeWeakA || !nodeWeakB)
                continue;
            
            nodeCollisionData[NodeCollision::P_BODY] = (void*)bodyA;
            nodeCollisionData[NodeCollision::P_OTHERNODE] = (void*)nodeB;
            nodeCollisionData[NodeCollision::P_OTHERBODY] = (void*)bodyB;
            nodeCollisionData[NodeCollision::P_NEWCOLLISION] = newCollision;
            nodeCollisionData[NodeCollision::P_CONTACTS] = contacts.GetBuffer();
            
            SendEvent(nodeA, E_NODECOLLISION, nodeCollisionData);
            
            // Skip if either of the nodes has been removed as a response to the event
            if (!nodeWeakA || !nodeWeakB)
                continue;
            
            contacts.Clear();
            for (int j = 0; j < numContacts; ++j)
            {
                btManifoldPoint& point = contactManifold->getContactPoint(j);
                contacts.WriteVector3(ToVector3(point.m_positionWorldOnB));
                contacts.WriteVector3(-ToVector3(point.m_normalWorldOnB));
                contacts.WriteFloat(point.m_distance1);
                contacts.WriteFloat(point.m_appliedImpulse);
            }
            
            nodeCollisionData[NodeCollision::P_BODY] = (void*)bodyB;
            nodeCollisionData[NodeCollision::P_OTHERNODE] = (void*)nodeA;
            nodeCollisionData[NodeCollision::P_OTHERBODY] = (void*)bodyA;
            nodeCollisionData[NodeCollision::P_CONTACTS] = contacts.GetBuffer();
            
            SendEvent(nodeB, E_NODECOLLISION, nodeCollisionData);
        }
    }
    
    previousCollisions_ = currentCollisions_;
}

void RegisterPhysicsLibrary(Context* context)
{
    Joint::RegisterObject(context);
    RigidBody::RegisterObject(context);
    CollisionShape::RegisterObject(context);
    PhysicsWorld::RegisterObject(context);
}
