// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Mutex.h"
#include "../Core/Profiler.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Model.h"
#include "../IO/Log.h"
#include "../Math/Ray.h"
#include "../Physics/CollisionShape.h"
#include "../Physics/Constraint.h"
#include "../Physics/PhysicsEvents.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RaycastVehicle.h"
#include "../Physics/RigidBody.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include <Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>
#include <Bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <Bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

extern ContactAddedCallback gContactAddedCallback;

using namespace std;

namespace Urho3D
{

const char* PHYSICS_CATEGORY = "Physics";
extern const char* SUBSYSTEM_CATEGORY;

static const int MAX_SOLVER_ITERATIONS = 256;
static const Vector3 DEFAULT_GRAVITY = Vector3(0.0f, -9.81f, 0.0f);

PhysicsWorldConfig PhysicsWorld::config;

static bool CompareRaycastResults(const PhysicsRaycastResult& lhs, const PhysicsRaycastResult& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

void InternalPreTickCallback(btDynamicsWorld* world, btScalar timeStep)
{
    static_cast<PhysicsWorld*>(world->getWorldUserInfo())->PreStep(timeStep);
}

void InternalTickCallback(btDynamicsWorld* world, btScalar timeStep)
{
    static_cast<PhysicsWorld*>(world->getWorldUserInfo())->PostStep(timeStep);
}

static bool CustomMaterialCombinerCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0,
    int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
    // Ensure that shape type of colObj1Wrap is either btScaledBvhTriangleMeshShape or btBvhTriangleMeshShape
    // because btAdjustInternalEdgeContacts doesn't check types properly. Bug in the Bullet?
    const int shapeType = colObj1Wrap->getCollisionObject()->getCollisionShape()->getShapeType();
    if (shapeType == SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE || shapeType == TRIANGLE_SHAPE_PROXYTYPE
        || shapeType == MULTIMATERIAL_TRIANGLE_MESH_PROXYTYPE)
    {
        btAdjustInternalEdgeContacts(cp, colObj1Wrap, colObj0Wrap, partId1, index1);
    }

    cp.m_combinedFriction = colObj0Wrap->getCollisionObject()->getFriction() * colObj1Wrap->getCollisionObject()->getFriction();
    cp.m_combinedRestitution =
        colObj0Wrap->getCollisionObject()->getRestitution() * colObj1Wrap->getCollisionObject()->getRestitution();

    return true;
}

void RemoveCachedGeometryImpl(CollisionGeometryDataCache& cache, Model* model)
{
    for (auto i = cache.Begin(); i != cache.End();)
    {
        auto current = i++;
        if (current->first_.first_ == model)
            cache.Erase(current);
    }
}

void CleanupGeometryCacheImpl(CollisionGeometryDataCache& cache)
{
    for (auto i = cache.Begin(); i != cache.End();)
    {
        auto current = i++;
        if (current->second_.Refs() == 1)
            cache.Erase(current);
    }
}

/// Callback for physics world queries.
struct PhysicsQueryCallback : public btCollisionWorld::ContactResultCallback
{
    /// Construct.
    PhysicsQueryCallback(PODVector<RigidBody*>& result, unsigned collisionMask) :
        result_(result),
        collisionMask_(collisionMask)
    {
    }

    /// Add a contact result.
    btScalar addSingleResult(btManifoldPoint&, const btCollisionObjectWrapper* colObj0Wrap, int, int,
        const btCollisionObjectWrapper* colObj1Wrap, int, int) override
    {
        auto* body = reinterpret_cast<RigidBody*>(colObj0Wrap->getCollisionObject()->getUserPointer());
        if (body && !result_.Contains(body) && (body->GetCollisionLayer() & collisionMask_))
            result_.Push(body);
        body = reinterpret_cast<RigidBody*>(colObj1Wrap->getCollisionObject()->getUserPointer());
        if (body && !result_.Contains(body) && (body->GetCollisionLayer() & collisionMask_))
            result_.Push(body);
        return 0.0f;
    }

    /// Found rigid bodies.
    PODVector<RigidBody*>& result_;
    /// Collision mask for the query.
    unsigned collisionMask_;
};

PhysicsWorld::PhysicsWorld(Context* context) :
    Component(context),
    fps_(DEFAULT_FPS),
    debugMode_(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawConstraints | btIDebugDraw::DBG_DrawConstraintLimits)
{
    gContactAddedCallback = CustomMaterialCombinerCallback;

    if (PhysicsWorld::config.collisionConfig_)
        collisionConfiguration_ = PhysicsWorld::config.collisionConfig_;
    else
        collisionConfiguration_ = new btDefaultCollisionConfiguration();

    collisionDispatcher_ = make_unique<btCollisionDispatcher>(collisionConfiguration_);
    btGImpactCollisionAlgorithm::registerAlgorithm(static_cast<btCollisionDispatcher*>(collisionDispatcher_.get()));

    broadphase_ = make_unique<btDbvtBroadphase>();
    solver_ = make_unique<btSequentialImpulseConstraintSolver>();
    world_ = make_unique<btDiscreteDynamicsWorld>(collisionDispatcher_.get(), broadphase_.get(), solver_.get(), collisionConfiguration_);

    world_->setGravity(ToBtVector3(DEFAULT_GRAVITY));
    world_->getDispatchInfo().m_useContinuous = true;
    world_->getSolverInfo().m_splitImpulse = false; // Disable by default for performance
    world_->setDebugDrawer(this);
    world_->setInternalTickCallback(InternalPreTickCallback, static_cast<void*>(this), true);
    world_->setInternalTickCallback(InternalTickCallback, static_cast<void*>(this), false);
    world_->setSynchronizeAllMotionStates(true);
}

PhysicsWorld::~PhysicsWorld()
{
    if (scene_)
    {
        // Force all remaining constraints, rigid bodies and collision shapes to release themselves
        for (PODVector<Constraint*>::Iterator i = constraints_.Begin(); i != constraints_.End(); ++i)
            (*i)->ReleaseConstraint();

        for (PODVector<RigidBody*>::Iterator i = rigidBodies_.Begin(); i != rigidBodies_.End(); ++i)
            (*i)->ReleaseBody();

        for (PODVector<CollisionShape*>::Iterator i = collisionShapes_.Begin(); i != collisionShapes_.End(); ++i)
            (*i)->ReleaseShape();
    }

    world_.reset();
    solver_.reset();
    broadphase_.reset();
    collisionDispatcher_.reset();

    // Delete configuration only if it was the default created by PhysicsWorld
    if (!PhysicsWorld::config.collisionConfig_)
        delete collisionConfiguration_;
    collisionConfiguration_ = nullptr;
}

void PhysicsWorld::RegisterObject(Context* context)
{
    context->RegisterFactory<PhysicsWorld>(SUBSYSTEM_CATEGORY);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Gravity", GetGravity, SetGravity, Vector3, DEFAULT_GRAVITY, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Physics FPS", int, fps_, DEFAULT_FPS, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Max Substeps", int, maxSubSteps_, 0, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Solver Iterations", GetNumIterations, SetNumIterations, int, 10, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Net Max Angular Vel.", float, maxNetworkAngularVelocity_, DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Interpolation", bool, interpolation_, true, AM_FILE);
    URHO3D_ATTRIBUTE("Internal Edge Utility", bool, internalEdge_, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Split Impulse", GetSplitImpulse, SetSplitImpulse, bool, false, AM_DEFAULT);
}

bool PhysicsWorld::isVisible(const btVector3& aabbMin, const btVector3& aabbMax)
{
    if (debugRenderer_)
        return debugRenderer_->IsInside(BoundingBox(ToVector3(aabbMin), ToVector3(aabbMax)));
    else
        return false;
}

void PhysicsWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    if (debugRenderer_)
        debugRenderer_->AddLine(ToVector3(from), ToVector3(to), Color(color.x(), color.y(), color.z()), debugDepthTest_);
}

void PhysicsWorld::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug)
    {
        URHO3D_PROFILE(PhysicsDrawDebug);

        debugRenderer_ = debug;
        debugDepthTest_ = depthTest;
        world_->debugDrawWorld();
        debugRenderer_ = nullptr;
    }
}

void PhysicsWorld::reportErrorWarning(const char* warningString)
{
    URHO3D_LOGWARNING("Physics: " + String(warningString));
}

void PhysicsWorld::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
    const btVector3& color)
{
}

void PhysicsWorld::draw3dText(const btVector3& location, const char* textString)
{
}

void PhysicsWorld::Update(float timeStep)
{
    URHO3D_PROFILE(UpdatePhysics);

    float internalTimeStep = 1.0f / fps_;
    int maxSubSteps = (int)(timeStep * fps_) + 1;
    if (maxSubSteps_ < 0)
    {
        internalTimeStep = timeStep;
        maxSubSteps = 1;
    }
    else if (maxSubSteps_ > 0)
        maxSubSteps = Min(maxSubSteps, maxSubSteps_);

    delayedWorldTransforms_.Clear();
    simulating_ = true;

    if (interpolation_)
        world_->stepSimulation(timeStep, maxSubSteps, internalTimeStep);
    else
    {
        timeAcc_ += timeStep;
        while (timeAcc_ >= internalTimeStep && maxSubSteps > 0)
        {
            world_->stepSimulation(internalTimeStep, 0, internalTimeStep);
            timeAcc_ -= internalTimeStep;
            --maxSubSteps;
        }
    }

    simulating_ = false;

    // Apply delayed (parented) world transforms now
    while (!delayedWorldTransforms_.Empty())
    {
        for (HashMap<RigidBody*, DelayedWorldTransform>::Iterator i = delayedWorldTransforms_.Begin();
             i != delayedWorldTransforms_.End();)
        {
            const DelayedWorldTransform& transform = i->second_;

            // If parent's transform has already been assigned, can proceed
            if (!delayedWorldTransforms_.Contains(transform.parentRigidBody_))
            {
                transform.rigidBody_->ApplyWorldTransform(transform.worldPosition_, transform.worldRotation_);
                i = delayedWorldTransforms_.Erase(i);
            }
            else
                ++i;
        }
    }
}

void PhysicsWorld::UpdateCollisions()
{
    world_->performDiscreteCollisionDetection();
}

void PhysicsWorld::SetFps(int fps)
{
    fps_ = (unsigned)Clamp(fps, 1, 1000);

    MarkNetworkUpdate();
}

void PhysicsWorld::SetGravity(const Vector3& gravity)
{
    world_->setGravity(ToBtVector3(gravity));

    MarkNetworkUpdate();
}

void PhysicsWorld::SetMaxSubSteps(int num)
{
    maxSubSteps_ = num;
    MarkNetworkUpdate();
}

void PhysicsWorld::SetNumIterations(int num)
{
    num = Clamp(num, 1, MAX_SOLVER_ITERATIONS);
    world_->getSolverInfo().m_numIterations = num;

    MarkNetworkUpdate();
}

void PhysicsWorld::SetUpdateEnabled(bool enable)
{
    updateEnabled_ = enable;
}

void PhysicsWorld::SetInterpolation(bool enable)
{
    interpolation_ = enable;
}

void PhysicsWorld::SetInternalEdge(bool enable)
{
    internalEdge_ = enable;

    MarkNetworkUpdate();
}

void PhysicsWorld::SetSplitImpulse(bool enable)
{
    world_->getSolverInfo().m_splitImpulse = enable;

    MarkNetworkUpdate();
}

void PhysicsWorld::SetMaxNetworkAngularVelocity(float velocity)
{
    maxNetworkAngularVelocity_ = Clamp(velocity, 1.0f, 32767.0f);

    MarkNetworkUpdate();
}

void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask)
{
    URHO3D_PROFILE(PhysicsRaycast);

    if (maxDistance >= M_INFINITY)
        URHO3D_LOGWARNING("Infinite maxDistance in physics raycast is not supported");

    btCollisionWorld::AllHitsRayResultCallback
        rayCallback(ToBtVector3(ray.origin_), ToBtVector3(ray.origin_ + maxDistance * ray.direction_));
    rayCallback.m_collisionFilterGroup = (short)0xffff;
    rayCallback.m_collisionFilterMask = (short)collisionMask;

    world_->rayTest(rayCallback.m_rayFromWorld, rayCallback.m_rayToWorld, rayCallback);

    for (int i = 0; i < rayCallback.m_collisionObjects.size(); ++i)
    {
        PhysicsRaycastResult newResult;
        newResult.body_ = static_cast<RigidBody*>(rayCallback.m_collisionObjects[i]->getUserPointer());
        newResult.position_ = ToVector3(rayCallback.m_hitPointWorld[i]);
        newResult.normal_ = ToVector3(rayCallback.m_hitNormalWorld[i]);
        newResult.distance_ = (newResult.position_ - ray.origin_).Length();
        newResult.hitFraction_ = rayCallback.m_closestHitFraction;
        result.Push(newResult);
    }

    Sort(result.Begin(), result.End(), CompareRaycastResults);
}

void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask)
{
    URHO3D_PROFILE(PhysicsRaycastSingle);

    if (maxDistance >= M_INFINITY)
        URHO3D_LOGWARNING("Infinite maxDistance in physics raycast is not supported");

    btCollisionWorld::ClosestRayResultCallback
        rayCallback(ToBtVector3(ray.origin_), ToBtVector3(ray.origin_ + maxDistance * ray.direction_));
    rayCallback.m_collisionFilterGroup = (short)0xffff;
    rayCallback.m_collisionFilterMask = (short)collisionMask;

    world_->rayTest(rayCallback.m_rayFromWorld, rayCallback.m_rayToWorld, rayCallback);

    if (rayCallback.hasHit())
    {
        result.position_ = ToVector3(rayCallback.m_hitPointWorld);
        result.normal_ = ToVector3(rayCallback.m_hitNormalWorld);
        result.distance_ = (result.position_ - ray.origin_).Length();
        result.hitFraction_ = rayCallback.m_closestHitFraction;
        result.body_ = static_cast<RigidBody*>(rayCallback.m_collisionObject->getUserPointer());
    }
    else
    {
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
        result.hitFraction_ = 0.0f;
        result.body_ = nullptr;
    }
}

void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask, float overlapDistance)
{
    URHO3D_PROFILE(PhysicsRaycastSingleSegmented);

    assert(overlapDistance < segmentDistance);

    if (maxDistance >= M_INFINITY)
        URHO3D_LOGWARNING("Infinite maxDistance in physics raycast is not supported");

    const btVector3 direction = ToBtVector3(ray.direction_);
    const auto count = CeilToInt(maxDistance / segmentDistance);

    btVector3 start = ToBtVector3(ray.origin_);
    // overlap a bit with the previous segment for better precision, to avoid missing hits
    const btVector3 overlap = direction * overlapDistance;
    float remainingDistance = maxDistance;

    for (auto i = 0; i < count; ++i)
    {
        const float distance = Min(remainingDistance, segmentDistance); // The last segment may be shorter
        const btVector3 end = start + distance * direction;

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        rayCallback.m_collisionFilterGroup = (short)0xffff;
        rayCallback.m_collisionFilterMask = (short)collisionMask;

        world_->rayTest(rayCallback.m_rayFromWorld, rayCallback.m_rayToWorld, rayCallback);

        if (rayCallback.hasHit())
        {
            result.position_ = ToVector3(rayCallback.m_hitPointWorld);
            result.normal_ = ToVector3(rayCallback.m_hitNormalWorld);
            result.distance_ = (result.position_ - ray.origin_).Length();
            result.hitFraction_ = rayCallback.m_closestHitFraction;
            result.body_ = static_cast<RigidBody*>(rayCallback.m_collisionObject->getUserPointer());
            // No need to cast the rest of the segments
            return;
        }

        // Use the end position as the new start position
        start = end - overlap;
        remainingDistance -= segmentDistance;
    }

    // Didn't hit anything
    result.position_ = Vector3::ZERO;
    result.normal_ = Vector3::ZERO;
    result.distance_ = M_INFINITY;
    result.hitFraction_ = 0.0f;
    result.body_ = nullptr;
}

void PhysicsWorld::SphereCast(PhysicsRaycastResult& result, const Ray& ray, float radius, float maxDistance, unsigned collisionMask)
{
    URHO3D_PROFILE(PhysicsSphereCast);

    if (maxDistance >= M_INFINITY)
        URHO3D_LOGWARNING("Infinite maxDistance in physics sphere cast is not supported");

    btSphereShape shape(radius);
    Vector3 endPos = ray.origin_ + maxDistance * ray.direction_;

    btCollisionWorld::ClosestConvexResultCallback
        convexCallback(ToBtVector3(ray.origin_), ToBtVector3(endPos));
    convexCallback.m_collisionFilterGroup = (short)0xffff;
    convexCallback.m_collisionFilterMask = (short)collisionMask;

    world_->convexSweepTest(&shape, btTransform(btQuaternion::getIdentity(), convexCallback.m_convexFromWorld),
        btTransform(btQuaternion::getIdentity(), convexCallback.m_convexToWorld), convexCallback);

    if (convexCallback.hasHit())
    {
        result.body_ = static_cast<RigidBody*>(convexCallback.m_hitCollisionObject->getUserPointer());
        result.position_ = ToVector3(convexCallback.m_hitPointWorld);
        result.normal_ = ToVector3(convexCallback.m_hitNormalWorld);
        result.distance_ = convexCallback.m_closestHitFraction * (endPos - ray.origin_).Length();
        result.hitFraction_ = convexCallback.m_closestHitFraction;
    }
    else
    {
        result.body_ = nullptr;
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
        result.hitFraction_ = 0.0f;
    }
}

void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, CollisionShape* shape, const Vector3& startPos,
    const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask)
{
    if (!shape || !shape->GetCollisionShape())
    {
        URHO3D_LOGERROR("Null collision shape for convex cast");
        result.body_ = nullptr;
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
        result.hitFraction_ = 0.0f;
        return;
    }

    // If shape is attached in a rigidbody, set its collision group temporarily to 0 to make sure it is not returned in the sweep result
    auto* bodyComp = shape->GetComponent<RigidBody>();
    btRigidBody* body = bodyComp ? bodyComp->GetBody() : nullptr;
    btBroadphaseProxy* proxy = body ? body->getBroadphaseProxy() : nullptr;
    short group = 0;
    if (proxy)
    {
        group = proxy->m_collisionFilterGroup;
        proxy->m_collisionFilterGroup = 0;
    }

    // Take the shape's offset position & rotation into account
    Node* shapeNode = shape->GetNode();
    Matrix3x4 startTransform(startPos, startRot, shapeNode ? shapeNode->GetWorldScale() : Vector3::ONE);
    Matrix3x4 endTransform(endPos, endRot, shapeNode ? shapeNode->GetWorldScale() : Vector3::ONE);
    Vector3 effectiveStartPos = startTransform * shape->GetPosition();
    Vector3 effectiveEndPos = endTransform * shape->GetPosition();
    Quaternion effectiveStartRot = startRot * shape->GetRotation();
    Quaternion effectiveEndRot = endRot * shape->GetRotation();

    ConvexCast(result, shape->GetCollisionShape(), effectiveStartPos, effectiveStartRot, effectiveEndPos, effectiveEndRot, collisionMask);

    // Restore the collision group
    if (proxy)
        proxy->m_collisionFilterGroup = group;
}

void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, btCollisionShape* shape, const Vector3& startPos,
    const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask)
{
    if (!shape)
    {
        URHO3D_LOGERROR("Null collision shape for convex cast");
        result.body_ = nullptr;
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
        result.hitFraction_ = 0.0f;
        return;
    }

    if (!shape->isConvex())
    {
        URHO3D_LOGERROR("Can not use non-convex collision shape for convex cast");
        result.body_ = nullptr;
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
        result.hitFraction_ = 0.0f;
        return;
    }

    URHO3D_PROFILE(PhysicsConvexCast);

    btCollisionWorld::ClosestConvexResultCallback convexCallback(ToBtVector3(startPos), ToBtVector3(endPos));
    convexCallback.m_collisionFilterGroup = (short)0xffff;
    convexCallback.m_collisionFilterMask = (short)collisionMask;

    world_->convexSweepTest(static_cast<btConvexShape*>(shape), btTransform(ToBtQuaternion(startRot),
            convexCallback.m_convexFromWorld), btTransform(ToBtQuaternion(endRot), convexCallback.m_convexToWorld),
        convexCallback);

    if (convexCallback.hasHit())
    {
        result.body_ = static_cast<RigidBody*>(convexCallback.m_hitCollisionObject->getUserPointer());
        result.position_ = ToVector3(convexCallback.m_hitPointWorld);
        result.normal_ = ToVector3(convexCallback.m_hitNormalWorld);
        result.distance_ = convexCallback.m_closestHitFraction * (endPos - startPos).Length();
        result.hitFraction_ = convexCallback.m_closestHitFraction;
    }
    else
    {
        result.body_ = nullptr;
        result.position_ = Vector3::ZERO;
        result.normal_ = Vector3::ZERO;
        result.distance_ = M_INFINITY;
        result.hitFraction_ = 0.0f;
    }
}

void PhysicsWorld::RemoveCachedGeometry(Model* model)
{
    RemoveCachedGeometryImpl(triMeshCache_, model);
    RemoveCachedGeometryImpl(convexCache_, model);
    RemoveCachedGeometryImpl(gimpactTrimeshCache_, model);
}

void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const Sphere& sphere, unsigned collisionMask)
{
    URHO3D_PROFILE(PhysicsSphereQuery);

    result.Clear();

    btSphereShape sphereShape(sphere.radius_);
    unique_ptr<btRigidBody> tempRigidBody(new btRigidBody(1.0f, nullptr, &sphereShape));
    tempRigidBody->setWorldTransform(btTransform(btQuaternion::getIdentity(), ToBtVector3(sphere.center_)));
    // Need to activate the temporary rigid body to get reliable results from static, sleeping objects
    tempRigidBody->activate();
    world_->addRigidBody(tempRigidBody.get());

    PhysicsQueryCallback callback(result, collisionMask);
    world_->contactTest(tempRigidBody.get(), callback);

    world_->removeRigidBody(tempRigidBody.get());
}

void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const BoundingBox& box, unsigned collisionMask)
{
    URHO3D_PROFILE(PhysicsBoxQuery);

    result.Clear();

    btBoxShape boxShape(ToBtVector3(box.HalfSize()));
    unique_ptr<btRigidBody> tempRigidBody(new btRigidBody(1.0f, nullptr, &boxShape));
    tempRigidBody->setWorldTransform(btTransform(btQuaternion::getIdentity(), ToBtVector3(box.Center())));
    tempRigidBody->activate();
    world_->addRigidBody(tempRigidBody.get());

    PhysicsQueryCallback callback(result, collisionMask);
    world_->contactTest(tempRigidBody.get(), callback);

    world_->removeRigidBody(tempRigidBody.get());
}

void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const RigidBody* body)
{
    URHO3D_PROFILE(PhysicsBodyQuery);

    result.Clear();

    if (!body || !body->GetBody())
        return;

    PhysicsQueryCallback callback(result, body->GetCollisionMask());
    world_->contactTest(body->GetBody(), callback);

    // Remove the body itself from the returned list
    for (unsigned i = 0; i < result.Size(); i++)
    {
        if (result[i] == body)
        {
            result.Erase(i);
            break;
        }
    }
}

void PhysicsWorld::GetCollidingBodies(PODVector<RigidBody*>& result, const RigidBody* body)
{
    URHO3D_PROFILE(GetCollidingBodies);

    result.Clear();

    for (HashMap<Pair<WeakPtr<RigidBody>, WeakPtr<RigidBody> >, ManifoldPair>::Iterator i = currentCollisions_.Begin();
         i != currentCollisions_.End(); ++i)
    {
        if (i->first_.first_ == body)
        {
            if (i->first_.second_)
                result.Push(i->first_.second_);
        }
        else if (i->first_.second_ == body)
        {
            if (i->first_.first_)
                result.Push(i->first_.first_);
        }
    }
}

Vector3 PhysicsWorld::GetGravity() const
{
    return ToVector3(world_->getGravity());
}

int PhysicsWorld::GetNumIterations() const
{
    return world_->getSolverInfo().m_numIterations;
}

bool PhysicsWorld::GetSplitImpulse() const
{
    return world_->getSolverInfo().m_splitImpulse != 0;
}

void PhysicsWorld::AddRigidBody(RigidBody* body)
{
    rigidBodies_.Push(body);
}

void PhysicsWorld::RemoveRigidBody(RigidBody* body)
{
    rigidBodies_.Remove(body);
    // Remove possible dangling pointer from the delayedWorldTransforms structure
    delayedWorldTransforms_.Erase(body);
}

void PhysicsWorld::AddCollisionShape(CollisionShape* shape)
{
    collisionShapes_.Push(shape);
}

void PhysicsWorld::RemoveCollisionShape(CollisionShape* shape)
{
    collisionShapes_.Remove(shape);
}

void PhysicsWorld::AddConstraint(Constraint* constraint)
{
    constraints_.Push(constraint);
}

void PhysicsWorld::RemoveConstraint(Constraint* constraint)
{
    constraints_.Remove(constraint);
}

void PhysicsWorld::AddDelayedWorldTransform(const DelayedWorldTransform& transform)
{
    delayedWorldTransforms_[transform.rigidBody_] = transform;
}

void PhysicsWorld::DrawDebugGeometry(bool depthTest)
{
    auto* debug = GetComponent<DebugRenderer>();
    DrawDebugGeometry(debug, depthTest);
}

void PhysicsWorld::SetDebugRenderer(DebugRenderer* debug)
{
    debugRenderer_ = debug;
}

void PhysicsWorld::SetDebugDepthTest(bool enable)
{
    debugDepthTest_ = enable;
}

void PhysicsWorld::CleanupGeometryCache()
{
    // Remove cached shapes whose only reference is the cache itself
    CleanupGeometryCacheImpl(triMeshCache_);
    CleanupGeometryCacheImpl(convexCache_);
    CleanupGeometryCacheImpl(gimpactTrimeshCache_);
}

void PhysicsWorld::OnSceneSet(Scene* scene)
{
    // Subscribe to the scene subsystem update, which will trigger the physics simulation step
    if (scene)
    {
        scene_ = GetScene();
        SubscribeToEvent(scene_, E_SCENESUBSYSTEMUPDATE, URHO3D_HANDLER(PhysicsWorld, HandleSceneSubsystemUpdate));
    }
    else
        UnsubscribeFromEvent(E_SCENESUBSYSTEMUPDATE);
}

void PhysicsWorld::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!updateEnabled_)
        return;

    using namespace SceneSubsystemUpdate;
    Update(eventData[P_TIMESTEP].GetFloat());
}

void PhysicsWorld::PreStep(float timeStep)
{
    // Send pre-step event
    using namespace PhysicsPreStep;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WORLD] = this;
    eventData[P_TIMESTEP] = timeStep;
    SendEvent(E_PHYSICSPRESTEP, eventData);

    // Start profiling block for the actual simulation step
#ifdef URHO3D_PROFILING
    auto* profiler = GetSubsystem<Profiler>();
    if (profiler)
        profiler->BeginBlock("StepSimulation");
#endif
}

void PhysicsWorld::PostStep(float timeStep)
{
#ifdef URHO3D_PROFILING
    auto* profiler = GetSubsystem<Profiler>();
    if (profiler)
        profiler->EndBlock();
#endif

    SendCollisionEvents();

    // Send post-step event
    using namespace PhysicsPostStep;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WORLD] = this;
    eventData[P_TIMESTEP] = timeStep;
    SendEvent(E_PHYSICSPOSTSTEP, eventData);
}

void PhysicsWorld::SendCollisionEvents()
{
    URHO3D_PROFILE(SendCollisionEvents);

    currentCollisions_.Clear();
    physicsCollisionData_.Clear();
    nodeCollisionData_.Clear();

    int numManifolds = collisionDispatcher_->getNumManifolds();

    if (numManifolds)
    {
        physicsCollisionData_[PhysicsCollision::P_WORLD] = this;

        for (int i = 0; i < numManifolds; ++i)
        {
            btPersistentManifold* contactManifold = collisionDispatcher_->getManifoldByIndexInternal(i);
            // First check that there are actual contacts, as the manifold exists also when objects are close but not touching
            if (!contactManifold->getNumContacts())
                continue;

            const btCollisionObject* objectA = contactManifold->getBody0();
            const btCollisionObject* objectB = contactManifold->getBody1();

            auto* bodyA = static_cast<RigidBody*>(objectA->getUserPointer());
            auto* bodyB = static_cast<RigidBody*>(objectB->getUserPointer());
            // If it's not a rigidbody, maybe a ghost object
            if (!bodyA || !bodyB)
                continue;

            // Skip collision event signaling if both objects are static, or if collision event mode does not match
            if (bodyA->GetMass() == 0.0f && bodyB->GetMass() == 0.0f)
                continue;
            if (bodyA->GetCollisionEventMode() == COLLISION_NEVER || bodyB->GetCollisionEventMode() == COLLISION_NEVER)
                continue;
            if (bodyA->GetCollisionEventMode() == COLLISION_ACTIVE && bodyB->GetCollisionEventMode() == COLLISION_ACTIVE &&
                !bodyA->IsActive() && !bodyB->IsActive())
                continue;

            WeakPtr<RigidBody> bodyWeakA(bodyA);
            WeakPtr<RigidBody> bodyWeakB(bodyB);

            // First only store the collision pair as weak pointers and the manifold pointer, so user code can safely destroy
            // objects during collision event handling
            Pair<WeakPtr<RigidBody>, WeakPtr<RigidBody> > bodyPair;
            if (bodyA < bodyB)
            {
                bodyPair = MakePair(bodyWeakA, bodyWeakB);
                currentCollisions_[bodyPair].manifold_ = contactManifold;
            }
            else
            {
                bodyPair = MakePair(bodyWeakB, bodyWeakA);
                currentCollisions_[bodyPair].flippedManifold_ = contactManifold;
            }
        }

        for (HashMap<Pair<WeakPtr<RigidBody>, WeakPtr<RigidBody> >, ManifoldPair>::Iterator i = currentCollisions_.Begin();
             i != currentCollisions_.End(); ++i)
        {
            RigidBody* bodyA = i->first_.first_;
            RigidBody* bodyB = i->first_.second_;
            if (!bodyA || !bodyB)
                continue;

            Node* nodeA = bodyA->GetNode();
            Node* nodeB = bodyB->GetNode();
            WeakPtr<Node> nodeWeakA(nodeA);
            WeakPtr<Node> nodeWeakB(nodeB);

            bool trigger = bodyA->IsTrigger() || bodyB->IsTrigger();
            bool newCollision = !previousCollisions_.Contains(i->first_);

            physicsCollisionData_[PhysicsCollision::P_NODEA] = nodeA;
            physicsCollisionData_[PhysicsCollision::P_NODEB] = nodeB;
            physicsCollisionData_[PhysicsCollision::P_BODYA] = bodyA;
            physicsCollisionData_[PhysicsCollision::P_BODYB] = bodyB;
            physicsCollisionData_[PhysicsCollision::P_TRIGGER] = trigger;

            contacts_.Clear();

            // "Pointers not flipped"-manifold, send unmodified normals
            btPersistentManifold* contactManifold = i->second_.manifold_;
            if (contactManifold)
            {
                for (int j = 0; j < contactManifold->getNumContacts(); ++j)
                {
                    btManifoldPoint& point = contactManifold->getContactPoint(j);
                    contacts_.WriteVector3(ToVector3(point.m_positionWorldOnB));
                    contacts_.WriteVector3(ToVector3(point.m_normalWorldOnB));
                    contacts_.WriteFloat(point.m_distance1);
                    contacts_.WriteFloat(point.m_appliedImpulse);
                }
            }
            // "Pointers flipped"-manifold, flip normals also
            contactManifold = i->second_.flippedManifold_;
            if (contactManifold)
            {
                for (int j = 0; j < contactManifold->getNumContacts(); ++j)
                {
                    btManifoldPoint& point = contactManifold->getContactPoint(j);
                    contacts_.WriteVector3(ToVector3(point.m_positionWorldOnB));
                    contacts_.WriteVector3(-ToVector3(point.m_normalWorldOnB));
                    contacts_.WriteFloat(point.m_distance1);
                    contacts_.WriteFloat(point.m_appliedImpulse);
                }
            }

            physicsCollisionData_[PhysicsCollision::P_CONTACTS] = contacts_.GetBuffer();

            // Send separate collision start event if collision is new
            if (newCollision)
            {
                SendEvent(E_PHYSICSCOLLISIONSTART, physicsCollisionData_);
                // Skip rest of processing if either of the nodes or bodies is removed as a response to the event
                if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                    continue;
            }

            // Then send the ongoing collision event
            SendEvent(E_PHYSICSCOLLISION, physicsCollisionData_);
            if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                continue;

            nodeCollisionData_[NodeCollision::P_BODY] = bodyA;
            nodeCollisionData_[NodeCollision::P_OTHERNODE] = nodeB;
            nodeCollisionData_[NodeCollision::P_OTHERBODY] = bodyB;
            nodeCollisionData_[NodeCollision::P_TRIGGER] = trigger;
            nodeCollisionData_[NodeCollision::P_CONTACTS] = contacts_.GetBuffer();

            if (newCollision)
            {
                nodeA->SendEvent(E_NODECOLLISIONSTART, nodeCollisionData_);
                if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                    continue;
            }

            nodeA->SendEvent(E_NODECOLLISION, nodeCollisionData_);
            if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                continue;

            // Flip perspective to body B
            contacts_.Clear();
            contactManifold = i->second_.manifold_;
            if (contactManifold)
            {
                for (int j = 0; j < contactManifold->getNumContacts(); ++j)
                {
                    btManifoldPoint& point = contactManifold->getContactPoint(j);
                    contacts_.WriteVector3(ToVector3(point.m_positionWorldOnB));
                    contacts_.WriteVector3(-ToVector3(point.m_normalWorldOnB));
                    contacts_.WriteFloat(point.m_distance1);
                    contacts_.WriteFloat(point.m_appliedImpulse);
                }
            }
            contactManifold = i->second_.flippedManifold_;
            if (contactManifold)
            {
                for (int j = 0; j < contactManifold->getNumContacts(); ++j)
                {
                    btManifoldPoint& point = contactManifold->getContactPoint(j);
                    contacts_.WriteVector3(ToVector3(point.m_positionWorldOnB));
                    contacts_.WriteVector3(ToVector3(point.m_normalWorldOnB));
                    contacts_.WriteFloat(point.m_distance1);
                    contacts_.WriteFloat(point.m_appliedImpulse);
                }
            }

            nodeCollisionData_[NodeCollision::P_BODY] = bodyB;
            nodeCollisionData_[NodeCollision::P_OTHERNODE] = nodeA;
            nodeCollisionData_[NodeCollision::P_OTHERBODY] = bodyA;
            nodeCollisionData_[NodeCollision::P_CONTACTS] = contacts_.GetBuffer();

            if (newCollision)
            {
                nodeB->SendEvent(E_NODECOLLISIONSTART, nodeCollisionData_);
                if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                    continue;
            }

            nodeB->SendEvent(E_NODECOLLISION, nodeCollisionData_);
        }
    }

    // Send collision end events as applicable
    {
        physicsCollisionData_[PhysicsCollisionEnd::P_WORLD] = this;

        for (HashMap<Pair<WeakPtr<RigidBody>, WeakPtr<RigidBody> >, ManifoldPair>::Iterator
                 i = previousCollisions_.Begin(); i != previousCollisions_.End(); ++i)
        {
            if (!currentCollisions_.Contains(i->first_))
            {
                RigidBody* bodyA = i->first_.first_;
                RigidBody* bodyB = i->first_.second_;
                if (!bodyA || !bodyB)
                    continue;

                bool trigger = bodyA->IsTrigger() || bodyB->IsTrigger();

                // Skip collision event signaling if both objects are static, or if collision event mode does not match
                if (bodyA->GetMass() == 0.0f && bodyB->GetMass() == 0.0f)
                    continue;
                if (bodyA->GetCollisionEventMode() == COLLISION_NEVER || bodyB->GetCollisionEventMode() == COLLISION_NEVER)
                    continue;
                if (bodyA->GetCollisionEventMode() == COLLISION_ACTIVE && bodyB->GetCollisionEventMode() == COLLISION_ACTIVE &&
                    !bodyA->IsActive() && !bodyB->IsActive())
                    continue;

                Node* nodeA = bodyA->GetNode();
                Node* nodeB = bodyB->GetNode();
                WeakPtr<Node> nodeWeakA(nodeA);
                WeakPtr<Node> nodeWeakB(nodeB);

                physicsCollisionData_[PhysicsCollisionEnd::P_BODYA] = bodyA;
                physicsCollisionData_[PhysicsCollisionEnd::P_BODYB] = bodyB;
                physicsCollisionData_[PhysicsCollisionEnd::P_NODEA] = nodeA;
                physicsCollisionData_[PhysicsCollisionEnd::P_NODEB] = nodeB;
                physicsCollisionData_[PhysicsCollisionEnd::P_TRIGGER] = trigger;

                SendEvent(E_PHYSICSCOLLISIONEND, physicsCollisionData_);
                // Skip rest of processing if either of the nodes or bodies is removed as a response to the event
                if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                    continue;

                nodeCollisionData_[NodeCollisionEnd::P_BODY] = bodyA;
                nodeCollisionData_[NodeCollisionEnd::P_OTHERNODE] = nodeB;
                nodeCollisionData_[NodeCollisionEnd::P_OTHERBODY] = bodyB;
                nodeCollisionData_[NodeCollisionEnd::P_TRIGGER] = trigger;

                nodeA->SendEvent(E_NODECOLLISIONEND, nodeCollisionData_);
                if (!nodeWeakA || !nodeWeakB || !i->first_.first_ || !i->first_.second_)
                    continue;

                nodeCollisionData_[NodeCollisionEnd::P_BODY] = bodyB;
                nodeCollisionData_[NodeCollisionEnd::P_OTHERNODE] = nodeA;
                nodeCollisionData_[NodeCollisionEnd::P_OTHERBODY] = bodyA;

                nodeB->SendEvent(E_NODECOLLISIONEND, nodeCollisionData_);
            }
        }
    }

    previousCollisions_ = currentCollisions_;
}

void RegisterPhysicsLibrary(Context* context)
{
    CollisionShape::RegisterObject(context);
    RigidBody::RegisterObject(context);
    Constraint::RegisterObject(context);
    PhysicsWorld::RegisterObject(context);
    RaycastVehicle::RegisterObject(context);
}

}
