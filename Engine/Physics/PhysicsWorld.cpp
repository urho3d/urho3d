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
#include "DebugRenderer.h"
#include "Entity.h"
#include "Log.h"
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "Ray.h"
#include "RigidBody.h"
#include "StringUtils.h"
#include "VectorBuffer.h"
#include "XMLElement.h"

#include <ode/ode.h>
#include <algorithm>

#include "DebugNew.h"

unsigned numWorlds = 0;

static bool compareRaycastResults(const PhysicsRaycastResult& lhs, const PhysicsRaycastResult& rhs)
{
    return lhs.mDistance < rhs.mDistance;
}

PhysicsWorld::PhysicsWorld(Scene* scene) :
    mScene(scene),
    mWorld(0),
    mSpace(0),
    mRayGeometry(0),
    mContactJoints(0),
    mFps(60),
    mMaxContacts(20),
    mBounceThreshold(0.1f),
    mAngularMaxNetVelocity(256.0f),
    mTimeAcc(0.0f),
    mDebugDraw(false)
{
    if (!numWorlds)
        dInitODE();
    
    mWorld = dWorldCreate();
    mSpace = dHashSpaceCreate(0);
    mContactJoints = dJointGroupCreate(0);
    ++numWorlds;
    
    // Create ray geometry for physics world raycasts
    mRayGeometry = dCreateRay(mSpace, 0.0f);
    
    // Enable automatic resting of rigid bodies
    dWorldSetAutoDisableFlag(mWorld, 1);
}

PhysicsWorld::~PhysicsWorld()
{
    if (mContactJoints)
    {
        dJointGroupDestroy(mContactJoints);
        mContactJoints = 0;
    }
    if (mRayGeometry)
    {
        dGeomDestroy(mRayGeometry);
        mRayGeometry = 0;
    }
    if (mSpace)
    {
        dSpaceDestroy(mSpace);
        mSpace = 0;
    }
    if (mWorld)
    {
        dWorldDestroy(mWorld);
        mWorld = 0;
        --numWorlds;
        
        if (!numWorlds)
            dCloseODE();
    }
}

void PhysicsWorld::save(Serializer& dest)
{
    writeExtensionType(dest);
    dest.writeVector3(getGravity());
    dest.writeUInt(getFps());
    dest.writeUInt(getMaxContacts());
    dest.writeFloat(getBounceThreshold());
    dest.writeFloat(getLinearRestThreshold());
    dest.writeFloat(getLinearDampingThreshold());
    dest.writeFloat(getLinearDampingScale());
    dest.writeFloat(getAngularRestThreshold());
    dest.writeFloat(getAngularDampingThreshold());
    dest.writeFloat(getAngularDampingScale());
    dest.writeFloat(getAngularMaxNetVelocity());
    dest.writeFloat(getERP());
    dest.writeFloat(getCFM());
    dest.writeFloat(getContactSurfaceLayer());
    dest.writeFloat(getTimeAccumulator());
    dest.writeUInt(getRandomSeed());
}

void PhysicsWorld::load(Deserializer& source)
{
    checkExtensionType(source);
    setGravity(source.readVector3());
    setFps(source.readUInt());
    setMaxContacts(source.readUInt());
    setBounceThreshold(source.readFloat());
    setLinearRestThreshold(source.readFloat());
    float threshold = source.readFloat();
    float scale = source.readFloat();
    setLinearDamping(threshold, scale);
    setAngularRestThreshold(source.readFloat());
    threshold = source.readFloat();
    scale = source.readFloat();
    setAngularDamping(threshold, scale);
    setAngularMaxNetVelocity(source.readFloat());
    setERP(source.readFloat());
    setCFM(source.readFloat());
    setContactSurfaceLayer(source.readFloat());
    setTimeAccumulator(source.readFloat());
    setRandomSeed(source.readUInt());
}

void PhysicsWorld::saveXML(XMLElement& dest)
{
    XMLElement physicsElem = dest.createChildElement("physics");
    
    physicsElem.setVector3("gravity", getGravity());
    physicsElem.setInt("fps", getFps());
    physicsElem.setFloat("timeacc", getTimeAccumulator());
    physicsElem.setInt("randomseed", getRandomSeed());
    
    XMLElement contactsElem = physicsElem.createChildElement("contacts");
    contactsElem.setInt("max", getMaxContacts());
    contactsElem.setFloat("bouncethreshold", getBounceThreshold());
    contactsElem.setFloat("erp", getERP());
    contactsElem.setFloat("cfm", getCFM());
    contactsElem.setFloat("surfacelayer", getContactSurfaceLayer());
    
    XMLElement linearElem = physicsElem.createChildElement("linear");
    XMLElement angularElem = physicsElem.createChildElement("angular");
    linearElem.setFloat("restthreshold", getLinearRestThreshold());
    linearElem.setFloat("dampingthreshold", getLinearDampingThreshold());
    linearElem.setFloat("dampingscale", getLinearDampingScale());
    angularElem.setFloat("restthreshold", getAngularRestThreshold());
    angularElem.setFloat("dampingthreshold", getAngularDampingThreshold());
    angularElem.setFloat("dampingscale", getAngularDampingScale());
    angularElem.setFloat("maxnetvelocity", getAngularMaxNetVelocity());
}

void PhysicsWorld::loadXML(const XMLElement& source)
{
    XMLElement physicsElem = source.getChildElement("physics");
    
    setGravity(physicsElem.getVector3("gravity"));
    setFps(physicsElem.getInt("fps"));
    if (physicsElem.hasAttribute("timeacc"))
        setTimeAccumulator(physicsElem.getFloat("timeacc"));
    if (physicsElem.hasAttribute("randomseed"))
        setRandomSeed(physicsElem.getInt("randomseed"));
    
    if (physicsElem.hasChildElement("contacts"))
    {
        XMLElement contactsElem = physicsElem.getChildElement("contacts");
        setMaxContacts(contactsElem.getInt("max"));
        setBounceThreshold(contactsElem.getFloat("bouncethreshold"));
        setERP(contactsElem.getFloat("erp"));
        setCFM(contactsElem.getFloat("cfm"));
        setContactSurfaceLayer(contactsElem.getFloat("surfacelayer"));
    }
    
    if (physicsElem.hasChildElement("linear"))
    {
        XMLElement linearElem = physicsElem.getChildElement("linear");
        setLinearRestThreshold(linearElem.getFloat("restthreshold"));
        setLinearDamping(linearElem.getFloat("dampingthreshold"), linearElem.getFloat("dampingscale"));
    }
    
    if (physicsElem.hasChildElement("angular"))
    {
        XMLElement angularElem = physicsElem.getChildElement("angular");
        setAngularRestThreshold(angularElem.getFloat("restthreshold"));
        setAngularDamping(angularElem.getFloat("dampingthreshold"), angularElem.getFloat("dampingscale"));
        setAngularMaxNetVelocity(angularElem.getFloat("maxnetvelocity"));
    }
}

void PhysicsWorld::update(float timeStep)
{
    PROFILE(Physics_Update);
    
    float internalTimeStep = 1.0f / mFps;
    
    while (timeStep > 0.0f)
    {
        float currentStep = min(timeStep, internalTimeStep);
        mTimeAcc += currentStep;
        timeStep -= currentStep;
        
        if (mTimeAcc >= internalTimeStep)
        {
            mTimeAcc -= internalTimeStep;
            
            // Send pre-step event
            using namespace PhysicsPreStep;
            
            VariantMap eventData;
            eventData[P_WORLD] = (void*)this;
            eventData[P_SCENE] = (void*)mScene;
            eventData[P_TIMESTEP] = internalTimeStep;
            sendEvent(EVENT_PHYSICSPRESTEP, eventData);
            
            // Store the previous transforms of the physics objects
            for (std::vector<RigidBody*>::iterator i = mRigidBodies.begin(); i != mRigidBodies.end(); ++i)
                (*i)->preStep();
            
            // Collide, step the world, and clear contact joints
            {
                PROFILE(Physics_Collide);
                dSpaceCollide(mSpace, this, nearCallback);
            }
            {
                PROFILE(Physics_Step);
                dWorldQuickStep(mWorld, internalTimeStep);
                dJointGroupEmpty(mContactJoints);
                mPreviousCollisions = mCollisions;
                mCollisions.clear();
            }
            
            // Interpolate transforms of physics objects
            float t = clamp(mTimeAcc / internalTimeStep, 0.0f, 1.0f);
            for (std::vector<RigidBody*>::iterator i = mRigidBodies.begin(); i != mRigidBodies.end(); ++i)
                (*i)->postStep(t);
            
            // Send post-step event
            sendEvent(EVENT_PHYSICSPOSTSTEP, eventData);
        }
    }
}

void PhysicsWorld::setPlayback(bool enable)
{
    // During scene rewind/replay all non-predicted dynamic & kinematic bodies are temporarily disabled
    if (enable)
    {
        for (std::vector<RigidBody*>::iterator i = mRigidBodies.begin(); i != mRigidBodies.end(); ++i)
        {
            RigidBody* body = *i;
            if ((body->getMode() != PHYS_STATIC) && (!body->checkPrediction()))
                body->setTempDisabled(true);
        }
    }
    else
    {
        for (std::vector<RigidBody*>::iterator i = mRigidBodies.begin(); i != mRigidBodies.end(); ++i)
        {
            RigidBody* body = *i;
            body->setTempDisabled(false);
        }
    }
}

void PhysicsWorld::setGravity(const Vector3& gravity)
{
    dWorldSetGravity(mWorld, gravity.mX, gravity.mY, gravity.mZ);;
}

void PhysicsWorld::setFps(int fps)
{
    mFps = max(fps, 1);
}

void PhysicsWorld::setMaxContacts(unsigned contacts)
{
    mMaxContacts = max(contacts, 1);
}

void PhysicsWorld::setLinearRestThreshold(float threshold)
{
    dWorldSetAutoDisableLinearThreshold(mWorld, max(threshold, 0.0f));
}

void PhysicsWorld::setLinearDamping(float threshold, float scale)
{
    dWorldSetLinearDampingThreshold(mWorld, max(threshold, 0.0f));
    dWorldSetLinearDamping(mWorld, clamp(scale, 0.0f, 1.0f));
}

void PhysicsWorld::setAngularRestThreshold(float threshold)
{
    dWorldSetAutoDisableAngularThreshold(mWorld, threshold);
}

void PhysicsWorld::setAngularDamping(float threshold, float scale)
{
    dWorldSetAngularDampingThreshold(mWorld, max(threshold, 0.0f));
    dWorldSetAngularDamping(mWorld, clamp(scale, 0.0f, 1.0f));
}

void PhysicsWorld::setAngularMaxNetVelocity(float velocity)
{
    mAngularMaxNetVelocity = max(velocity, 0.0f);
}

void PhysicsWorld::setBounceThreshold(float threshold)
{
    mBounceThreshold = max(threshold, 0.0f);
}

void PhysicsWorld::setERP(float erp)
{
    dWorldSetERP(mWorld, erp);
}

void PhysicsWorld::setCFM(float cfm)
{
    dWorldSetCFM(mWorld, cfm);
}

void PhysicsWorld::setContactSurfaceLayer(float depth)
{
    dWorldSetContactSurfaceLayer(mWorld, depth);
}

void PhysicsWorld::setTimeAccumulator(float time)
{
    mTimeAcc = time;
}

void PhysicsWorld::setRandomSeed(unsigned seed)
{
    dRandSetSeed(seed);
}

void PhysicsWorld::raycast(const Ray& ray, std::vector<PhysicsRaycastResult>& result, float maxDistance, unsigned collisionMask)
{
    PROFILE(Physics_Raycast);
    
    result.clear();
    dGeomRaySetLength(mRayGeometry, maxDistance);
    dGeomRaySet(mRayGeometry, ray.mOrigin.mX, ray.mOrigin.mY, ray.mOrigin.mZ, ray.mDirection.mX, ray.mDirection.mY, ray.mDirection.mZ);
    dGeomSetCollideBits(mRayGeometry, collisionMask);
    dSpaceCollide2(mRayGeometry, (dGeomID)mSpace, &result, raycastCallback);
    
    std::sort(result.begin(), result.end(), compareRaycastResults);
}

unsigned PhysicsWorld::getRandomSeed() const
{
    return dRandGetSeed();
}

Vector3 PhysicsWorld::getGravity() const
{
    dVector3 g;
    dWorldGetGravity(mWorld, g);
    return Vector3(g[0], g[1], g[2]);
}

float PhysicsWorld::getLinearRestThreshold() const
{
    return dWorldGetAutoDisableLinearThreshold(mWorld);
}

float PhysicsWorld::getLinearDampingThreshold() const
{
    return dWorldGetLinearDampingThreshold(mWorld);
}

float PhysicsWorld::getLinearDampingScale() const
{
    return dWorldGetLinearDamping(mWorld);
}

float PhysicsWorld::getAngularRestThreshold() const
{
    return dWorldGetAutoDisableAngularThreshold(mWorld);
}

float PhysicsWorld::getAngularDampingThreshold() const
{
    return dWorldGetAngularDampingThreshold(mWorld);
}

float PhysicsWorld::getAngularDampingScale() const
{
    return dWorldGetAngularDamping(mWorld);
}

float PhysicsWorld::getERP() const
{
    return dWorldGetERP(mWorld);
}

float PhysicsWorld::getCFM() const
{
    return dWorldGetCFM(mWorld);
}

float PhysicsWorld::getContactSurfaceLayer() const
{
    return dWorldGetContactSurfaceLayer(mWorld);
}

void PhysicsWorld::drawDebugGeometry(DebugRenderer* debug)
{
    PROFILE(Physics_DrawDebugGeometry);
    
    for (std::vector<RigidBody*>::iterator i = mRigidBodies.begin(); i != mRigidBodies.end(); ++i)
        (*i)->drawDebugGeometry(debug);
}

void PhysicsWorld::addRigidBody(RigidBody* body)
{
    mRigidBodies.push_back(body);
}

void PhysicsWorld::removeRigidBody(RigidBody* body)
{
    for (std::vector<RigidBody*>::iterator i = mRigidBodies.begin(); i != mRigidBodies.end(); ++i)
    {
        if ((*i) == body)
        {
            mRigidBodies.erase(i);
            return;
        }
    }
}

void PhysicsWorld::nearCallback(void *userData, dGeomID geomA, dGeomID geomB)
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
    
    RigidBody* rigidBodyA = static_cast<RigidBody*>(dGeomGetData(geomA));
    RigidBody* rigidBodyB = static_cast<RigidBody*>(dGeomGetData(geomB));
    
    if ((!rigidBodyA) || (!rigidBodyB))
        return;
    
    Entity* entityA = rigidBodyA->getEntity();
    Entity* entityB = rigidBodyB->getEntity();
    
    // If both bodies are inactive, no collision (note also that no events will be generated)
    if ((!rigidBodyA->isActive()) && (!rigidBodyB->isActive()))
        return;
    
    PhysicsWorld* world = static_cast<PhysicsWorld*>(userData);
    
    // Calculate average friction & bounce (physically incorrect)
    float friction = (rigidBodyA->getFriction() + rigidBodyB->getFriction()) * 0.5f;
    float bounce = (rigidBodyA->getBounce() + rigidBodyB->getBounce()) * 0.5f;
    
    static std::vector<dContact> contacts;
    if (contacts.size() < world->mMaxContacts)
        contacts.resize(world->mMaxContacts);
    
    for (unsigned i = 0; i < world->mMaxContacts; ++i)
    {
        contacts[i].surface.mode = dContactApprox1;
        contacts[i].surface.mu = friction;
        if (bounce > 0.0f)
        {
            contacts[i].surface.mode |= dContactBounce;
            contacts[i].surface.bounce = bounce;
            contacts[i].surface.bounce_vel = world->mBounceThreshold;
        }
    }
    
    unsigned numContacts = dCollide(geomA, geomB, world->mMaxContacts, &contacts[0].geom, sizeof(dContact));
    if (!numContacts)
        return;
    
    std::pair<RigidBody*, RigidBody*> bodyPair;
    if (rigidBodyA < rigidBodyB)
        bodyPair = std::make_pair(rigidBodyA, rigidBodyB);
    else
        bodyPair = std::make_pair(rigidBodyB, rigidBodyA);
    
    static VariantMap collisionData;
    static VariantMap entityCollisionData;
    static VectorBuffer contactsA;
    static VectorBuffer contactsB;
    
    collisionData[PhysicsCollision::P_WORLD] = (void*)world;
    collisionData[PhysicsCollision::P_SCENE] = (void*)world->mScene;
    collisionData[PhysicsCollision::P_BODYA] = (void*)rigidBodyA;
    collisionData[PhysicsCollision::P_BODYB] = (void*)rigidBodyB;
    
    // Check if the same pair already collided on the last step
    entityCollisionData[EntityCollision::P_NEWCOLLISION] = collisionData[PhysicsCollision::P_NEWCOLLISION] =
        world->mPreviousCollisions.find(bodyPair) == world->mPreviousCollisions.end();
    world->mCollisions.insert(bodyPair);
    
    contactsA.clear();
    contactsB.clear();
    
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
        dJointID contact = dJointCreateContact(world->mWorld, world->mContactJoints, &contacts[i]);
        dJointAttach(contact, bodyA, bodyB);
        
        // Write contact data to the contact buffers: position, normal, depth, velocity
        Vector3 position(contacts[i].geom.pos[0], contacts[i].geom.pos[1], contacts[i].geom.pos[2]);
        Vector3 normal(contacts[i].geom.normal[0], contacts[i].geom.normal[1], contacts[i].geom.normal[2]);
        contactsA.writeVector3(position);
        contactsA.writeVector3(normal);
        contactsA.writeFloat(contacts[i].geom.depth);
        contactsA.writeFloat(length);
        if (entityB)
        {
            contactsB.writeVector3(position);
            contactsB.writeVector3(-normal);
            contactsB.writeFloat(contacts[i].geom.depth);
            contactsB.writeFloat(length);
        }
    }
    
    // Send collision events
    collisionData[PhysicsCollision::P_CONTACTS] = contactsA.getBuffer();
    world->sendEvent(EVENT_PHYSICSCOLLISION, collisionData);
    
    if (entityA)
    {
        entityCollisionData[EntityCollision::P_BODY] = (void*)rigidBodyA;
        entityCollisionData[EntityCollision::P_OTHERBODY] = (void*)rigidBodyB;
        entityCollisionData[EntityCollision::P_OTHERENTITY] = (void*)entityB;
        entityCollisionData[EntityCollision::P_CONTACTS] = contactsA.getBuffer();
        world->sendEvent(entityA, EVENT_ENTITYCOLLISION, entityCollisionData);
    }
    if (entityB)
    {
        entityCollisionData[EntityCollision::P_BODY] = (void*)rigidBodyB;
        entityCollisionData[EntityCollision::P_OTHERBODY] = (void*)rigidBodyA;
        entityCollisionData[EntityCollision::P_OTHERENTITY] = (void*)entityA;
        entityCollisionData[EntityCollision::P_CONTACTS] = contactsB.getBuffer();
        world->sendEvent(entityB, EVENT_ENTITYCOLLISION, entityCollisionData);
    }
    
    // Propagate transient prediction based on physics interactions
    // Note: during the actual rewind/replay phase this works poorly, because most bodies are disabled and
    // no new collisions can be detected. However, the transient prediction timers are also not decremented
    // during replay. An alternative would be to use simple bounding box/sphere checks for propagation
    if ((entityA) && (entityB) && (entityA->isProxy()) && (entityB->isProxy()))
    {
        entityA->setPredictionFrom(entityB);
        entityB->setPredictionFrom(entityA);
    }
}

void PhysicsWorld::raycastCallback(void *userData, dGeomID geomA, dGeomID geomB)
{
    RigidBody* rigidBodyA = static_cast<RigidBody*>(dGeomGetData(geomA));
    RigidBody* rigidBodyB = static_cast<RigidBody*>(dGeomGetData(geomB));
    if ((!rigidBodyA) && (!rigidBodyB))
        return;
    
    dContact contact;
    unsigned numContacts = dCollide(geomA, geomB, 1, &contact.geom, sizeof(dContact));
    
    if (numContacts > 0)
    {
        std::vector<PhysicsRaycastResult>* result = static_cast<std::vector<PhysicsRaycastResult>*>(userData);
        PhysicsRaycastResult newResult;
        if (rigidBodyA)
            newResult.mBody = rigidBodyA;
        else
            newResult.mBody = rigidBodyB;
        newResult.mDistance = contact.geom.depth;
        newResult.mPosition = Vector3(contact.geom.pos[0], contact.geom.pos[1], contact.geom.pos[2]);
        newResult.mNormal = Vector3(contact.geom.normal[0], contact.geom.normal[1], contact.geom.normal[2]);
        result->push_back(newResult);
    }
}
