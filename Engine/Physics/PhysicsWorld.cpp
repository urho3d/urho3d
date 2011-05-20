//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "PhysicsWorld.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "RigidBody.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "StringUtils.h"
#include "VectorBuffer.h"

#include <ode/ode.h>
#include "Sort.h"

#include "DebugNew.h"

static const int DEFAULT_FPS = 60;
static const int DEFAULT_MAXCONTACTS = 20;
static const float DEFAULT_BOUNCETHRESHOLD = 0.1f;

static unsigned numInstances = 0;

static bool CompareRaycastResults(const PhysicsRaycastResult& lhs, const PhysicsRaycastResult& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

OBJECTTYPESTATIC(PhysicsWorld);

PhysicsWorld::PhysicsWorld(Context* context) :
    Component(context),
    physicsWorld_(0),
    space_(0),
    rayGeometry_(0),
    contactJoints_(0),
    fps_(DEFAULT_FPS),
    maxContacts_(DEFAULT_MAXCONTACTS),
    bounceThreshold_(DEFAULT_BOUNCETHRESHOLD),
    timeAcc_(0.0f),
    randomSeed_(0)
{
    {
        MutexLock Lock(GetStaticMutex());
        
        if (!numInstances)
            dInitODE();
        ++numInstances;
    }
    
    physicsWorld_ = dWorldCreate();
    space_ = dHashSpaceCreate(0);
    contactJoints_ = dJointGroupCreate(0);
    
    // Create ray geometry for physics world raycasts
    rayGeometry_ = dCreateRay(0, 0.0f);
    
    // Enable automatic resting of rigid bodies
    dWorldSetAutoDisableFlag(physicsWorld_, 1);
    
    contacts_ = new PODVector<dContact>(maxContacts_);
}

PhysicsWorld::~PhysicsWorld()
{
    // Forcibly remove any cached geometries that still remain
    triangleMeshCache_.Clear();
    heightfieldCache_.Clear();
    
    if (contactJoints_)
    {
        dJointGroupDestroy(contactJoints_);
        contactJoints_ = 0;
    }
    if (rayGeometry_)
    {
        dGeomDestroy(rayGeometry_);
        rayGeometry_ = 0;
    }
    if (space_)
    {
        dSpaceDestroy(space_);
        space_ = 0;
    }
    if (contacts_)
    {
        PODVector<dContact>* contacts = static_cast<PODVector<dContact>*>(contacts_);
        delete contacts;
        contacts = 0;
    }
    if (physicsWorld_)
    {
        dWorldDestroy(physicsWorld_);
        physicsWorld_ = 0;
    }
    
    {
        MutexLock Lock(GetStaticMutex());
        
        --numInstances;
        if (!numInstances)
            dCloseODE();
    }
}

void PhysicsWorld::RegisterObject(Context* context)
{
    context->RegisterFactory<PhysicsWorld>();
    
    ATTRIBUTE(PhysicsWorld, VAR_INT, "Physics FPS", fps_, DEFAULT_FPS);
    ATTRIBUTE(PhysicsWorld, VAR_INT, "Max Contacts", maxContacts_, DEFAULT_MAXCONTACTS);
    ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Bounce Threshold", bounceThreshold_, DEFAULT_BOUNCETHRESHOLD);
    ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Time Accumulator", timeAcc_, 0.0f);
    ATTRIBUTE(PhysicsWorld, VAR_INT, "Random Seed", randomSeed_, 0);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_VECTOR3, "Gravity", GetGravity, SetGravity, Vector3, Vector3::ZERO);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Linear Rest Threshold", GetLinearRestThreshold, SetLinearRestThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Linear Damping Threshold", GetLinearDampingThreshold, SetLinearDampingThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Linear Damping Scale", GetLinearDampingScale, SetLinearDampingScale, float, 0.0f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Angular Rest Threshold", GetAngularRestThreshold, SetAngularRestThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Angular Damping Threshold", GetAngularDampingThreshold, SetAngularDampingThreshold, float, 0.01f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Angular Damping Scale", GetAngularDampingScale, SetAngularDampingScale, float, 0.0f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "ERP", GetERP, SetERP, float, 0.2f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "CFM", GetCFM, SetCFM, float, 0.00001f);
    ACCESSOR_ATTRIBUTE(PhysicsWorld, VAR_FLOAT, "Contact Surface Layer", GetContactSurfaceLayer, SetContactSurfaceLayer, float, 0.0f);
}

void PhysicsWorld::Update(float timeStep)
{
    PROFILE(UpdatePhysics);
    
    float internalTimeStep = 1.0f / fps_;
    
    while (timeStep > 0.0f)
    {
        float currentStep = Min(timeStep, internalTimeStep);
        timeAcc_ += currentStep;
        timeStep -= currentStep;
        
        if (timeAcc_ >= internalTimeStep)
        {
            timeAcc_ -= internalTimeStep;
            
            // Send pre-step event
            using namespace PhysicsPreStep;
            
            VariantMap eventData;
            eventData[P_WORLD] = (void*)this;
            eventData[P_TIMESTEP] = internalTimeStep;
            SendEvent(E_PHYSICSPRESTEP, eventData);
            
            // Store the previous transforms of the physics objects
            for (Vector<RigidBody*>::Iterator i = rigidBodies_.Begin(); i != rigidBodies_.End(); ++i)
                (*i)->PreStep();
            
            /// \todo ODE random number generation is not threadsafe
            dRandSetSeed(randomSeed_);
            
            // Collide, step the world, and clear contact joints
            {
                PROFILE(CheckCollisions);
                dSpaceCollide(space_, this, NearCallback);
            }
            {
                PROFILE(StepPhysics);
                dWorldQuickStep(physicsWorld_, internalTimeStep);
                dJointGroupEmpty(contactJoints_);
                previousCollisions_ = currentCollisions_;
                currentCollisions_.Clear();
            }
            
            randomSeed_ = dRandGetSeed();
            
            // Send accumulated collision events
            SendCollisionEvents();
            
            // Interpolate transforms of physics objects
            float t = Clamp(timeAcc_ / internalTimeStep, 0.0f, 1.0f);
            for (Vector<RigidBody*>::Iterator i = rigidBodies_.Begin(); i != rigidBodies_.End(); ++i)
                (*i)->PostStep(t);
            
            // Send post-step event
            SendEvent(E_PHYSICSPOSTSTEP, eventData);
        }
    }
}

void PhysicsWorld::SetFps(int fps)
{
    fps_ = Max(fps, 1);
}

void PhysicsWorld::SetMaxContacts(unsigned num)
{
    maxContacts_ = Max(num, 1);
    PODVector<dContact>* contacts = static_cast<PODVector<dContact>*>(contacts_);
    contacts->Resize(maxContacts_);
}

void PhysicsWorld::SetGravity(Vector3 gravity)
{
    dWorldSetGravity(physicsWorld_, gravity.x_, gravity.y_, gravity.z_);
}

void PhysicsWorld::SetLinearRestThreshold(float threshold)
{
    dWorldSetAutoDisableLinearThreshold(physicsWorld_, Max(threshold, 0.0f));
}

void PhysicsWorld::SetLinearDampingThreshold(float threshold)
{
    dWorldSetLinearDampingThreshold(physicsWorld_, Max(threshold, 0.0f));
}

void PhysicsWorld::SetLinearDampingScale(float scale)
{
    dWorldSetLinearDamping(physicsWorld_, Clamp(scale, 0.0f, 1.0f));
}

void PhysicsWorld::SetAngularRestThreshold(float threshold)
{
    dWorldSetAutoDisableAngularThreshold(physicsWorld_, threshold);
}

void PhysicsWorld::SetAngularDampingThreshold(float threshold)
{
    dWorldSetAngularDampingThreshold(physicsWorld_, Max(threshold, 0.0f));
}

void PhysicsWorld::SetAngularDampingScale(float scale)
{
    dWorldSetAngularDamping(physicsWorld_, Clamp(scale, 0.0f, 1.0f));
}

void PhysicsWorld::SetBounceThreshold(float threshold)
{
    bounceThreshold_ = Max(threshold, 0.0f);
}

void PhysicsWorld::SetERP(float erp)
{
    dWorldSetERP(physicsWorld_, erp);
}

void PhysicsWorld::SetCFM(float cfm)
{
    dWorldSetCFM(physicsWorld_, cfm);
}

void PhysicsWorld::SetContactSurfaceLayer(float depth)
{
    dWorldSetContactSurfaceLayer(physicsWorld_, depth);
}

void PhysicsWorld::SetTimeAccumulator(float time)
{
    timeAcc_ = time;
}

void PhysicsWorld::Raycast(Vector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask)
{
    PROFILE(PhysicsRaycast);
    
    result.Clear();
    dGeomRaySetLength(rayGeometry_, maxDistance);
    dGeomRaySet(rayGeometry_, ray.origin_.x_, ray.origin_.y_, ray.origin_.z_, ray.direction_.x_, ray.direction_.y_, ray.direction_.z_);
    dGeomSetCollideBits(rayGeometry_, collisionMask);
    dSpaceCollide2(rayGeometry_, (dGeomID)space_, &result, RaycastCallback);
    
    Sort(result.Begin(), result.End(), CompareRaycastResults);
}

Vector3 PhysicsWorld::GetGravity() const
{
    dVector3 g;
    dWorldGetGravity(physicsWorld_, g);
    return Vector3(g[0], g[1], g[2]);
}

float PhysicsWorld::GetLinearRestThreshold() const
{
    return dWorldGetAutoDisableLinearThreshold(physicsWorld_);
}

float PhysicsWorld::GetLinearDampingThreshold() const
{
    return dWorldGetLinearDampingThreshold(physicsWorld_);
}

float PhysicsWorld::GetLinearDampingScale() const
{
    return dWorldGetLinearDamping(physicsWorld_);
}

float PhysicsWorld::GetAngularRestThreshold() const
{
    return dWorldGetAutoDisableAngularThreshold(physicsWorld_);
}

float PhysicsWorld::GetAngularDampingThreshold() const
{
    return dWorldGetAngularDampingThreshold(physicsWorld_);
}

float PhysicsWorld::GetAngularDampingScale() const
{
    return dWorldGetAngularDamping(physicsWorld_);
}

float PhysicsWorld::GetERP() const
{
    return dWorldGetERP(physicsWorld_);
}

float PhysicsWorld::GetCFM() const
{
    return dWorldGetCFM(physicsWorld_);
}

float PhysicsWorld::GetContactSurfaceLayer() const
{
    return dWorldGetContactSurfaceLayer(physicsWorld_);
}

void PhysicsWorld::AddRigidBody(RigidBody* body)
{
    rigidBodies_.Push(body);
}

void PhysicsWorld::RemoveRigidBody(RigidBody* body)
{
    for (Vector<RigidBody*>::Iterator i = rigidBodies_.Begin(); i != rigidBodies_.End(); ++i)
    {
        if ((*i) == body)
        {
            rigidBodies_.Erase(i);
            return;
        }
    }
}

void PhysicsWorld::SendCollisionEvents()
{
    PROFILE(SendCollisionEvents);
    
    VariantMap physicsCollisionData;
    VariantMap nodeCollisionData;
    VectorBuffer contacts;
    
    physicsCollisionData[PhysicsCollision::P_WORLD] = (void*)this;
    
    for (Vector<PhysicsCollisionInfo>::ConstIterator i = collisionInfos_.Begin(); i != collisionInfos_.End(); ++i)
    {
        // Skip if either of the nodes has been removed
        if ((!i->nodeA_) || (!i->nodeB_))
            continue;
        
        physicsCollisionData[PhysicsCollision::P_NODEA] = (void*)i->nodeA_;
        physicsCollisionData[PhysicsCollision::P_NODEB] = (void*)i->nodeB_;
        physicsCollisionData[PhysicsCollision::P_SHAPEA] = (void*)i->shapeA_;
        physicsCollisionData[PhysicsCollision::P_SHAPEB] = (void*)i->shapeB_;
        physicsCollisionData[PhysicsCollision::P_NEWCOLLISION] = i->newCollision_;
        
        contacts.Clear();
        for (unsigned j = 0; j < i->contacts_.Size(); ++j)
        {
            contacts.WriteVector3(i->contacts_[j].position_);
            contacts.WriteVector3(i->contacts_[j].normal_);
            contacts.WriteFloat(i->contacts_[j].depth_);
            contacts.WriteFloat(i->contacts_[j].velocity_);
        }
        physicsCollisionData[PhysicsCollision::P_CONTACTS] = contacts.GetBuffer();
        
        SendEvent(E_PHYSICSCOLLISION, physicsCollisionData);
        
        // Skip if either of the nodes is null, or has been removed as a response to the event
        if ((!i->nodeA_) || (!i->nodeB_))
            continue;
        
        nodeCollisionData[NodeCollision::P_SHAPE] = (void*)i->shapeA_;
        nodeCollisionData[NodeCollision::P_OTHERNODE] = (void*)i->nodeB_;
        nodeCollisionData[NodeCollision::P_OTHERSHAPE] = (void*)i->shapeB_;
        nodeCollisionData[NodeCollision::P_NEWCOLLISION] = i->newCollision_;
        nodeCollisionData[NodeCollision::P_CONTACTS] = contacts.GetBuffer();
        
        SendEvent(i->nodeA_, E_NODECOLLISION, nodeCollisionData);
        
        // Skip if either of the nodes has been removed as a response to the event
        if ((!i->nodeA_) || (!i->nodeB_))
            continue;
        
        contacts.Clear();
        for (unsigned j = 0; j < i->contacts_.Size(); ++j)
        {
            contacts.WriteVector3(i->contacts_[j].position_);
            contacts.WriteVector3(-i->contacts_[j].normal_);
            contacts.WriteFloat(i->contacts_[j].depth_);
            contacts.WriteFloat(i->contacts_[j].velocity_);
        }
        
        nodeCollisionData[NodeCollision::P_SHAPE] = (void*)i->shapeB_;
        nodeCollisionData[NodeCollision::P_OTHERNODE] = (void*)i->nodeA_;
        nodeCollisionData[NodeCollision::P_OTHERSHAPE] = (void*)i->shapeA_;
        nodeCollisionData[NodeCollision::P_CONTACTS] = contacts.GetBuffer();
        
        SendEvent(i->nodeB_, E_NODECOLLISION, nodeCollisionData);
    }
    
    collisionInfos_.Clear();
}

void PhysicsWorld::DrawDebugGeometry(bool depthTest)
{
    PROFILE(PhysicsDrawDebug);
    
    DebugRenderer* debug = GetComponent<DebugRenderer>();
    if (!debug)
        return;
    
    // Get all geometries, also those that have no rigid bodies
    Vector<Node*> nodes;
    Vector<CollisionShape*> shapes;
    node_->GetChildrenWithComponent<CollisionShape>(nodes, true);
    
    for (Vector<Node*>::Iterator i = nodes.Begin(); i != nodes.End(); ++i)
    {
        (*i)->GetComponents<CollisionShape>(shapes);
        for (Vector<CollisionShape*>::Iterator j = shapes.Begin(); j != shapes.End(); ++j)
            (*j)->DrawDebugGeometry(debug, depthTest);
    }
}

void PhysicsWorld::CleanupGeometryCache()
{
    // Remove cached shapes whose only reference is the cache itself
    for (Map<String, SharedPtr<TriangleMeshData> >::Iterator i = triangleMeshCache_.Begin();
        i != triangleMeshCache_.End();)
    {
        Map<String, SharedPtr<TriangleMeshData> >::Iterator current = i++;
        if (current->second_.GetRefCount() == 1)
            triangleMeshCache_.Erase(current);
    }
    
    for (Map<String, SharedPtr<HeightfieldData> >::Iterator i = heightfieldCache_.Begin();
        i != heightfieldCache_.End();)
    {
        Map<String, SharedPtr<HeightfieldData> >::Iterator current = i++;
        if (current->second_.GetRefCount() == 1)
            heightfieldCache_.Erase(current);
    }
}

void PhysicsWorld::OnNodeSet(Node* node)
{
    // Subscribe to the scene subsystem update, which will trigger the physics simulation step
    if (node)
        SubscribeToEvent(node, E_SCENESUBSYSTEMUPDATE, HANDLER(PhysicsWorld, HandleSceneSubsystemUpdate));
}

void PhysicsWorld::NearCallback(void *userData, dGeomID geomA, dGeomID geomB)
{
    dBodyID bodyA = dGeomGetBody(geomA);
    dBodyID bodyB = dGeomGetBody(geomB);
    
    // If both geometries are static, no collision
    if ((!bodyA) && (!bodyB))
        return;
    
    // If the geometries belong to the same body, no collision
    if (bodyA == bodyB)
        return;
    
    // If the bodies are already connected via other joints, no collision
    if ((bodyA) && (bodyB) && (dAreConnectedExcluding(bodyA, bodyB, dJointTypeContact)))
        return;
    
    // If both bodies are inactive, no collision
    RigidBody* rigidBodyA = bodyA ? static_cast<RigidBody*>(dBodyGetData(bodyA)) : 0;
    RigidBody* rigidBodyB = bodyB ? static_cast<RigidBody*>(dBodyGetData(bodyB)) : 0;
    if ((rigidBodyA) && (!rigidBodyA->IsActive()) && (rigidBodyB) && (!rigidBodyB->IsActive()))
        return;
    
    PhysicsWorld* world = static_cast<PhysicsWorld*>(userData);
    
    CollisionShape* shapeA = static_cast<CollisionShape*>(dGeomGetData(geomA));
    CollisionShape* shapeB = static_cast<CollisionShape*>(dGeomGetData(geomB));
    Node* nodeA = shapeA->GetNode();
    Node* nodeB = shapeB->GetNode();
    
    // Calculate average friction & bounce (physically incorrect)
    float friction = (shapeA->GetFriction() + shapeB->GetFriction()) * 0.5f;
    float bounce = (shapeA->GetBounce() + shapeB->GetBounce()) * 0.5f;
    
    PODVector<dContact>& contacts = *(static_cast<PODVector<dContact>*>(world->contacts_));
    
    for (unsigned i = 0; i < world->maxContacts_; ++i)
    {
        contacts[i].surface.mode = dContactApprox1;
        contacts[i].surface.mu = friction;
        if (bounce > 0.0f)
        {
            contacts[i].surface.mode |= dContactBounce;
            contacts[i].surface.bounce = bounce;
            contacts[i].surface.bounce_vel = world->bounceThreshold_;
        }
    }
    
    unsigned numContacts = dCollide(geomA, geomB, world->maxContacts_, &contacts[0].geom, sizeof(dContact));
    if (!numContacts)
        return;
    
    Pair<RigidBody*, RigidBody*> bodyPair;
    if (rigidBodyA < rigidBodyB)
        bodyPair = MakePair(rigidBodyA, rigidBodyB);
    else
        bodyPair = MakePair(rigidBodyB, rigidBodyA);
    
    PhysicsCollisionInfo collisionInfo;
    collisionInfo.nodeA_ = nodeA;
    collisionInfo.nodeB_ = nodeB;
    collisionInfo.shapeA_ = shapeA;
    collisionInfo.shapeB_ = shapeB;
    collisionInfo.newCollision_ = world->previousCollisions_.Find(bodyPair) == world->previousCollisions_.End();
    collisionInfo.contacts_.Clear();
    world->currentCollisions_.Insert(bodyPair);
    
    for (unsigned i = 0; i < numContacts; ++i)
    {
        // Calculate isotropic friction direction from relative tangent velocity between bodies
        // Adapted from http://www.ode.org/old_list_archives/2005-May/015836.html
        dVector3 velA;
        if (bodyA)
            dBodyGetPointVel(bodyA, contacts[i].geom.pos[0], contacts[i].geom.pos[1], contacts[i].geom.pos[2], velA);
        else
            velA[0] = velA[1] = velA[2] = 0.0f;
        
        if (bodyB)
        {
            dVector3 velB;
            dBodyGetPointVel(bodyB, contacts[i].geom.pos[0], contacts[i].geom.pos[1], contacts[i].geom.pos[2], velB);
            velA[0] -= velB[0];
            velA[1] -= velB[1];
            velA[2] -= velB[2];
        }
        
        // Normalize & only use our calculated friction if it has enough precision
        float length = sqrtf(velA[0] * velA[0] + velA[1] * velA[1] + velA[2] * velA[2]);
        if (length > M_EPSILON)
        {
            float invLen = 1.0f / length;
            velA[0] *= invLen;
            velA[1] *= invLen;
            velA[2] *= invLen;
            
            // Make sure friction is also perpendicular to normal
            dCROSS(contacts[i].fdir1, =, velA, contacts[i].geom.normal);
            contacts[i].surface.mode |= dContactFDir1;
        }
        
        // Create contact joint
        dJointID contact = dJointCreateContact(world->physicsWorld_, world->contactJoints_, &contacts[i]);
        dJointAttach(contact, bodyA, bodyB);
        
        // Store contact info
        PhysicsContactInfo contactInfo;
        contactInfo.position_ =  Vector3(contacts[i].geom.pos[0], contacts[i].geom.pos[1], contacts[i].geom.pos[2]);
        contactInfo.normal_ = Vector3(contacts[i].geom.normal[0], contacts[i].geom.normal[1], contacts[i].geom.normal[2]);
        contactInfo.depth_ = contacts[i].geom.depth;
        contactInfo.velocity_ = length;
        collisionInfo.contacts_.Push(contactInfo);
    }
    
    // Store collision info to be sent later
    world->collisionInfos_.Push(collisionInfo);
}

void PhysicsWorld::RaycastCallback(void *userData, dGeomID geomA, dGeomID geomB)
{
    dContact contact;
    unsigned numContacts = dCollide(geomA, geomB, 1, &contact.geom, sizeof(dContact));
    
    if (numContacts > 0)
    {
        Vector<PhysicsRaycastResult>* result = static_cast<Vector<PhysicsRaycastResult>*>(userData);
        PhysicsRaycastResult newResult;
        
        CollisionShape* shapeA = static_cast<CollisionShape*>(dGeomGetData(geomA));
        CollisionShape* shapeB = static_cast<CollisionShape*>(dGeomGetData(geomB));
        
        // Check which of the geometries is the raycast ray
        if (shapeA)
            newResult.node_ = shapeA->GetNode();
        else
            newResult.node_ = shapeB->GetNode();
        
        newResult.distance_ = contact.geom.depth;
        newResult.position_ = Vector3(contact.geom.pos[0], contact.geom.pos[1], contact.geom.pos[2]);
        newResult.normal_ = Vector3(contact.geom.normal[0], contact.geom.normal[1], contact.geom.normal[2]);
        result->Push(newResult);
    }
}

void PhysicsWorld::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneSubsystemUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void RegisterPhysicsLibrary(Context* context)
{
    CollisionShape::RegisterObject(context);
    Joint::RegisterObject(context);
    RigidBody::RegisterObject(context);
    PhysicsWorld::RegisterObject(context);
}
