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
#include "BoxShape.h"
#include "CapsuleShape.h"
#include "ConeShape.h"
#include "Context.h"
#include "CylinderShape.h"
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
#include "SphereShape.h"
#include "TriangleMeshShape.h"

#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include "DebugNew.h"

static const int DEFAULT_FPS = 60;
static const Vector3 DEFAULT_GRAVITY = Vector3(0.0f, -9.81f, 0.0f);

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
    debugMode_(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawNormals | btIDebugDraw::DBG_DrawConstraints)
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
    triangleMeshCache_.Clear();
    heightfieldCache_.Clear();
    
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
    
    // Allow max. 0.1s update at a time
    if (timeStep > 0.1f)
        timeStep = 0.1f;
    
    float internalTimeStep = 1.0f / fps_;
    
    if (interpolation_)
    {
        int maxSubSteps = (int)(0.1f * fps_);
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
    /// \todo Implement
}

void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask)
{
    /// \todo Implement
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
    for (Map<String, SharedPtr<TriangleMeshData> >::Iterator i = triangleMeshCache_.Begin();
        i != triangleMeshCache_.End();)
    {
        Map<String, SharedPtr<TriangleMeshData> >::Iterator current = i++;
        if (current->second_.Refs() == 1)
            triangleMeshCache_.Erase(current);
    }
    
    for (Map<String, SharedPtr<ConvexHullData> >::Iterator i = convexHullCache_.Begin();
        i != convexHullCache_.End();)
    {
        Map<String, SharedPtr<ConvexHullData> >::Iterator current = i++;
        if (current->second_.Refs() == 1)
            convexHullCache_.Erase(current);
    }
    for (Map<String, SharedPtr<HeightfieldData> >::Iterator i = heightfieldCache_.Begin();
        i != heightfieldCache_.End();)
    {
        Map<String, SharedPtr<HeightfieldData> >::Iterator current = i++;
        if (current->second_.Refs() == 1)
            heightfieldCache_.Erase(current);
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
    /// \todo Implement
}

void RegisterPhysicsLibrary(Context* context)
{
    Joint::RegisterObject(context);
    RigidBody::RegisterObject(context);
    BoxShape::RegisterObject(context);
    CapsuleShape::RegisterObject(context);
    ConeShape::RegisterObject(context);
    CylinderShape::RegisterObject(context);
    SphereShape::RegisterObject(context);
    TriangleMeshShape::RegisterObject(context);
    PhysicsWorld::RegisterObject(context);
}
